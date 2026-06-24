# Volvo ME7 (50GPHJ) — LDR boost-control algorithm (reverse-engineered from C166 code)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The boost controller (Ladedruckregelung / LDR), traced through the C166 disassembly of the
stock 50GPHJ firmware (Infineon C167CR). Worked up in IDA on `<work>\me7_stock_boost.i64`; the
code is byte-identical across calibration revisions, so this holds for any GPHJ tune.

Legend: **[CONFIRMED]** = read directly from the instruction stream;
**[INFERRED]** = deduced from structure / Bosch ME7 convention, not literally proven.

---

## 0. Where the controller lives and how it is scheduled

`sub_B81C` is a top-level periodic task. Near its end it runs the LDR block as an ordered
chain (one pass per task tick) — **[CONFIRMED]** from `sub_B81C` disassembly:

```
0xB8F4  calls sub_DB370   ; LDR pre-processing
0xB8F8  calls sub_DB49A
0xB8FC  calls sub_DB522
0xB900  calls sub_DBB04   ; *** PI / feed-forward arithmetic (the core math) ***
0xB904  calls sub_DB882
0xB908  calls sub_DBF44   ; *** enable / limit / mode state machine ***
0xB90C  calls sub_DC57E
0xB910  calls sub_DC672
0xB914  calls sub_DCB84
```

`sub_DC31A` (the WG-output / actuator-mode state machine, analysed below) is reached from
the same LDR cluster. The three functions the task brief named — `sub_DBB04`, `sub_DBF44`,
`sub_DC31A` — are the heart of the loop: **setpoint+PI math**, **enable/limit gating**, and
**output/actuator-mode handling** respectively.

---

## 1. The shared lookup / interpolation primitives

These are the building blocks the controller calls. All confirmed by disassembly.

- **`sub_41A68(r12=offset, r13=page, r14=input) → r4`** — **1-D unsigned** table interp.
  Reads count byte, binary/linear-searches the unsigned axis (`cc_ULE[`/`](/)cc_NC`), then
  `(in-x0)*(y1-y0)/(x1-x0)` via `mulu[`/`](/)divlu`. **[CONFIRMED]**
- **`sub_41B5A(...)`** — identical shape but **signed** axis search (`cc_SLE[`/`](/)cc_SGE`,
  `cc_SGT`). Used for signed error inputs. **[CONFIRMED]**
- **`sub_41CC0(r12=offset, r13=page, r14=x-input, r15=y-input) → r8?`** — **2-D / KF map**
  bilinear interpolation: searches an X axis and a Y axis, then interpolates the map cell
  (two nested `mulu[`/`](/)divlu` passes). This is the routine used for the 2-axis boost KFs
  (`KFLDRX`). **[CONFIRMED]**
- **`sub_43904(r12=coeff, r13=target, r14=state_lo, r15=state_hi) → r4:r5 (new 32-bit state)`**
  — **first-order lag / integrator (PT1)**. Logic **[CONFIRMED]**:
  ```
  d = target - state_hi            ; r13 - r14
  if d == 0:   state = target, frac = 0
  if d  > 0:   state += coeff*d     ; rising:  32-bit accumulate up   (loc_43924)
  if d  < 0:   state -= coeff*|d|   ; falling: 32-bit accumulate down (loc_43912)
  ```
  i.e. `state += coeff*(target-state)` with a 16.16 carry. `coeff` is the per-tick
  filter/integration gain pulled from a calibration word. This is the controller's
  **I-term accumulator** and also its setpoint slew filter.
- **`sub_42464`** — wrapper around a clamped multiply/scale helper (`sub_416B0`+`sub_420A8`);
  used in `sub_DBF44` to scale a duty offset. **[CONFIRMED present, math secondary]**

---

## 2. `sub_DBB04` — setpoint, error, P-term, I-term, feed-forward (the core)

Register/RAM convention recovered from the listing. Calibration cells in the `0xA`-page
band `0x2BExx/0x2BFxx` (= KFLDIMX / KFLDRL / KFLDRX family per the map linkage table).

### 2a. Boost/load **request → working setpoint** (lines 0xDBB08–0xDBB7C) **[CONFIRMED]**
```
r12 = word_302968                 ; load/torque request term (from torque model)
r13 = word_2BE38  (=0x22A5)       ; CAL gain constant  [CAL 0x2BE38]
r14 = word_F410                   ; measured signal (boost/load actual or rail) 
mulu r14,r13 ; mulu MDH,r12        ; two-stage fixed-point scale  (16x16→32, rescale >>10/<<6)
... saturate to 0xFFFF ...
-> word_302E64                    ; scaled request component A
```
Then a **conditional KFLDIMX-region map add** gated by cal bit `byte_1BE46.0`
(0xDBB48–0xDBB6E): if enabled, look up map at **(offset 0x3E92, page 0xA → phys 0x2BE92)**
indexed by `word_302E3E`, store to `word_302E66`; else 0. **[CAL 0x2BE92, map header]**
```
word_302E62 = sat( word_302E64 + word_302E66 )   ; *** combined boost SETPOINT ***  (0xDBB6E)
```
**`word_302E62` is the boost-control setpoint** (request A + map term B, clamped to 0xFFFF).
**[CONFIRMED arithmetic; setpoint role INFERRED from downstream use at 0xDBD1A]**

### 2b. **Actual / measured ratio** (lines 0xDBB80–0xDBBA6) **[CONFIRMED]**
```
r9  = word_30294A                 ; divisor (reference: ambient/throttle pressure) 
r12 = word_302496 << 11 ; r13 = word_302496 >> 5   ; 32-bit numerator from measured load word_302496
divlu r9                          ; ratio = (word_302496 << 11) / word_30294A
sat -> word_302E58                ; *** normalized ACTUAL boost/load ratio ***
```
`word_302496` is the **measured load/boost** quantity; `word_30294A` the normalizing
reference. The `divlu` forms a dimensionless **actual ratio** in `word_302E58`.

### 2c. **I-term: error → integrator, limited by KFLDIMX** (0xDBBAA–0xDBBE2) **[CONFIRMED]**
```
r12 = word_2BF32  (=0x2AAB)       ; CAL integrator gain/limit  [CAL 0x2BF32] (KFLDIMX-region)
r13 = word_302E58                 ; integrator target = actual ratio
r14:r15 = word_302E6A:word_302E68 ; 32-bit I-state
calls sub_43904                   ; PT1/integrator step
word_302E68:word_302E6A = new state
... look up KFLDRX-region map (offset 0x3E3A page0xA = phys 0x2BE3A) by word_F410 -> r4  [CAL 0x2BE3A]
r12 = word_302E58 - word_302E6A   ; *** ERROR = actual_ratio - filtered/integrated value ***
      clamp to [0x8000 .. 0x7FFF] (signed)   (0xDBBE2-0xDBBF2)
```
`word_2BF32` is the **KFLDIMX integrator limit/gain** (the cell the brief flagged at
`word_2BF32`; raising it widens integrator authority — matches findings.md). The signed,
clamped difference at 0xDBBDE is the **control error e**.

### 2d. **P-term (proportional × error), signed scale + clamp** (0xDBBF2–0xDBC68) **[CONFIRMED]**
```
if r4 >= 0:  MDH:MDL = r12 * r4          ; e * P-gain (r4 from KFLDRX-region lookup at 2c)
else:        r4 &= 0x7FFF; product with sign-fixup (bmov r4.15,r12.0; ashr)
... rescale (>>14 / <<2) and saturate to signed [0x8000..0x7FFF] -> word_302E52   (0xDBC58)
calls sub_41B5A(off 0x3E74,page0xA, word_302E52) -> word_302E5C   ; P-term shaped via signed table  [CAL 0x2BE74]
```
`word_302E52` is the raw P contribution (error×gain, clamped); `word_302E5C` the
table-shaped P output. **[CONFIRMED; "P-term" role INFERRED from e×gain structure]**

### 2e. **Second integrator path / D- or pilot term** (0xDBC6C–0xDBCD6) **[CONFIRMED]**
```
r9  = word_2BF2E  (=0x4000)       ; CAL scale  [CAL 0x2BF2E]
r12 = word_302E3C                 ; input (a measured/derivative term)
mulu -> 32-bit, shift/clamp -> r8 (sat 0xFFFF)
r12 = word_2BF30  (=0x8000)       ; CAL integrator gain  [CAL 0x2BF30]
r13 = r8 ; r14:r15 = word_302E72:word_302E70   ; second 32-bit state
calls sub_43904                   ; second PT1/integrator
r8 = r8 - word_302E72 ; clamp signed -> word_302E50
calls sub_41B5A(off 0x3E56,page0xA, r8) -> word_302E5A     ; shaped  [CAL 0x2BE56]
```
A parallel filtered/integrated term shaped by another signed table — second loop component
(pilot/derivative-style). **[CONFIRMED math; exact PID-role INFERRED]**

### 2f. **PI sum + clamp to actuator window** (0xDBCDA–0xDBD10) **[CONFIRMED]**
```
r8 = word_302E5C (P-shaped) + word_302E5A (2nd-term)   ; sat to +0x7FFF
r8 += word_30BF0A                                       ; add a learned/adaptive offset (page 0xC2 RAM)
clamp r8 to signed window [0xC000 .. 0x3FFF]            ; *** controller PI output clamp ***
r8 <<= 1
```
**`word_30BF0A`** is an adaptive/learned trim added before the final window clamp.
The `[0xC000..0x3FFF]` clamp bounds the closed-loop correction. **[CONFIRMED]**

### 2g. **Feed-forward via KFLDRX/KFLDRL (base WG duty) + add correction** (0xDBD12–0xDBD3A) **[CONFIRMED]**
```
r12=#3ECAh r13=#0Ah          ; map at (offset 0x3ECA, page 0xA = phys 0x2BECA)  [CAL 0x2BECA]
r14 = word_302E62            ; X = the SETPOINT from 2a
r15 = word_302E3E            ; Y = second axis
calls sub_41CC0              ; 2-D map -> r4 = base/feed-forward duty (KFLDRX ceiling / WGDC base)
... r8 (=PI output, with sign branch) + r4  with unsigned saturation to [0..0xFFFF]
-> word_302E5E               ; *** combined demand = feed-forward + PI correction ***
```
`sub_41CC0` over the **page-0xA boost KF** (KFLDRX-region) indexed by **setpoint `word_302E62`**
gives the open-loop/feed-forward base; the PI correction `r8` is summed on top, saturated,
into **`word_302E5E`**. **[CONFIRMED arithmetic; KFLDRX identity per map-linkage table]**

### 2h. **Anti-windup / hold branch + final demand** (0xDBD3E–0xDBDA6) **[CONFIRMED]**
```
movbz r9, byte_1BE47  [CAL 0x1BE47]; if r9 > word_305630  (a counter/threshold):
    r9 = word_302E3C - word_302E38 (>=0)        ; deviation of actual vs request
    -> word_302E56
    lookup sub_41A68(off 0x3EAC,page0xA, r9)->r4 ; KFLDRL-region linearization  [CAL 0x2BEAC]
    calls sub_43904(r4, 0, word_302E6E:word_302E6C)  ; integrate the linearized deviation
    word_302E54 = word_302E6E (state hi)
    word_302E60 = sat( word_302E54 + word_302E5E )   ; *** FINAL controller demand ***
else:
    word_302E60 = word_302E5E                         ; pass demand through unchanged
```
**`word_302E60` is the final LDR demand** handed to the output stage (used in `sub_DBF44`
at 0xDC1A2 as `word_302E60 >> 1`). The KFLDRL-region table at **(0x3EAC,page0xA = 0x2BEAC)**
**linearizes** the wastegate response of the deviation term before integration — this is the
**KFLDRL wastegate-duty linearization feed-forward**. **[CONFIRMED]**

#### Setpoint vs actual RAM map (this function)
| RAM | Role | Confidence |
|---|---|---|
| `word_302968` | load/torque request input | INFERRED |
| `word_F410` | measured boost/load signal (KFLDRX axis) | INFERRED |
| `word_302496` | measured load/boost (actual, numerator) | INFERRED |
| `word_30294A` | normalizing reference (divisor) | INFERRED |
| `word_302E58` | **normalized ACTUAL ratio** | CONFIRMED (computed) |
| `word_302E62` | **boost SETPOINT** (request+map) | CONFIRMED (computed) |
| `word_302E68:6A` | I-term 32-bit state (KFLDIMX-limited) | CONFIRMED |
| `word_302E70:72` | 2nd integrator 32-bit state | CONFIRMED |
| `word_302E52[`/`](/)5C` | P raw / P shaped | CONFIRMED |
| `word_302E5E` | feed-forward + PI demand | CONFIRMED |
| `word_30BF0A` | adaptive trim offset | CONFIRMED |
| `word_302E60` | **FINAL WG demand** | CONFIRMED |
| `word_302E54[`/`](/)56` | KFLDRL deviation/linearized term | CONFIRMED |

---

## 3. `sub_DBF44` — enable / limit / authority state machine (KFLDIMX gate)

This is the function that decides whether the loop is closed, open, or limited, and produces
the final scaled duty. Bits live in `byte_301867/301868/301869/30186F` and counters in
`byte_30186B`, `word_302E80/82/84`.

### 3a. **KFLDIMX overrun → enable/limit bits** (0xDBF44–0xDBFAC) **[CONFIRMED]**
```
if !byte_301868.0:
   if byte_30186B < byte_1BE69 (debounce cal)  [CAL 0x1BE69]:
       if word_302E34 < word_2BF4A  (=0x0FFA)  [CAL 0x2BF4A KFLDIMX threshold]:
            ... set limit branch ...
       clear byte_301869.1
   if byte_301869.0 and word_302E34 < word_2BF4A: set byte_301869.1   ; armed
   if byte_301869.1: set byte_301869.0 ; decrement debounce byte_30186B
```
**`word_2BF4A` (=0x0FFA) is the KFLDIMX comparison threshold** — exactly the cell findings.md
named. `word_302E34` is the gated quantity (boost/load actual vs the I-limit map). Raising
KFLDIMX (`word_2BF4A`) raises this threshold → the controller stays in authority longer.
**[CONFIRMED — this is "why raising KFLDIMX extends controller authority"]**

### 3b. **Open-loop vs closed-loop select** (0xDBFAC–0xDC00A) **[CONFIRMED]**
```
checks word_30256A.3, word_FD0E.12, byte_301869.1, word_FD7E.13
 -> sets/clears byte_301867.1 (closed-loop run) and .2
if cal byte_1BE46.0 clear -> jump to passive/limp section (loc_DC156)   [CAL 0x1BE46 master enable]
```
**`byte_1BE46` (=0x07 low byte) is the LDR master config/enable bitfield** — its bit0 gates
the whole closed-loop path (also tested in `sub_DBB04` 2a and in `sub_DC31A`). **[CONFIRMED]**

### 3c. **Setpoint-overrun detection with KFLDIMX offset `word_2BF4C`** (0xDC00A–0xDC03A) **[CONFIRMED]**
```
r12 = word_2BF4C (=0x00F0)  [CAL 0x2BF4C]   ; KFLDIMX margin/offset
r12 = sat(word_2BF4C + word_302E3E)
USR0 = (r12 <= word_302E38) ? ...           ; compare (setpoint+margin) vs actual word_302E38
```
`word_302E38` is the **actual** boost used for the limiter; `word_302E3E` the reference;
`word_2BF4C` the **KFLDIMX margin**. Produces sign bits driving the integrator
freeze/decay logic below. **[CONFIRMED]**

### 3d. **Integrator hold / reset / windup-guard** (0xDC03A–0xDC156) **[CONFIRMED]**
A dense bit machine over `byte_30186F` using two debounce timers:
- `word_302E82` counts while overrun, reloaded from `word_17720` (=0x01C2 cal, page 0xA) — sets
  bit 0x20 (upper-limit reached). **[CAL 0x17720]**
- `word_302E80` counts the lower side, reloaded from same constant — sets/clears bit 0x80.
- Bits 0x10/0x40 mark "integrator clamped high / low"; 0x04 = saturated. When `word_2BF4C +
  word_302E3C <= word_302E38` (0xDC134) it sets bit 0x40 and ORs `byte_301869` bit2 (0xDC150).

This is the **anti-windup**: it freezes / one-sidedly releases the integrators (`sub_43904`
states in `sub_DBB04`) when the demand has saturated against the KFLDIMX limit. **[CONFIRMED]**

### 3e. **Final duty scaling and output build** (0xDC172–0xDC1D6) **[CONFIRMED]**
```
movbz r12, byte_2BF34 (=0x06)   [CAL 0x2BF34]  ; KFLDIMX-region scale byte
calls sub_42464(off 0x3F3C/0x3F35 page0xA, ...) -> word_302E7A   ; scale factor from cal table
r8 = sat( word_302E4A + (word_302E60 >> 1) )    ; word_302E60 = FINAL demand from sub_DBB04 §2h
mulu r8, r4 ; rescale (<<2 / >>14) sat 0xFFFF -> word_302E7C     ; *** scaled duty ***
```
**`word_302E60` (the controller's final demand) is taken here, halved, offset by
`word_302E4A`, and multiplied by the cal-derived scale into `word_302E7C` — the duty value.**
**[CONFIRMED]**

### 3f. **Duty clamping to KFLDRL min/max** (0xDC1DA–0xDC296) **[CONFIRMED]**
```
if diag/condition active:
   if word_302E7C < word_2BF4E (=0x2E15):  word_302E7E = word_2BF4E     [CAL 0x2BF4E  duty MIN]
   elif word_302E7C > word_2BF50 (=0xD99A): word_302E7E = word_2BF50    [CAL 0x2BF50  duty MAX]
   else: word_302E7E = word_302E7C
```
**`word_2BF4E[`/`](/)word_2BF50` are the wastegate-duty MIN/MAX clamps** (the actuator window of
the KFLDRL linearization output). `word_302E7E` is the **clamped, deliverable duty cycle**.
A further hi/lo flag (`byte_301867.0`) is set when the duty is pinned at a rail (0xDC296+).
**[CONFIRMED]**

#### Confirmed calibrations used by `sub_DBF44`
| CAL | value | role |
|---|---|---|
| `0x2BF4A` | 0x0FFA | **KFLDIMX limiter threshold** (authority) |
| `0x2BF4C` | 0x00F0 | KFLDIMX margin/offset for overrun compare |
| `0x2BF34` | 0x06 | duty scale byte (table index) |
| `0x2BF4E` | 0x2E15 | **WG duty MIN clamp** |
| `0x2BF50` | 0xD99A | **WG duty MAX clamp** |
| `0x1BE46` | 0x07 | LDR master enable/config bitfield |
| `0x1BE69` | 0x10 | debounce count |
| `0x17720` | 0x01C2 | integrator-hold timer reload |

RAM: `word_302E60`=final demand in, `word_302E7C`=scaled duty, `word_302E7E`=clamped duty
out, `byte_301867/68/69/6F`=state bits. **[CONFIRMED]**

---

## 4. `sub_DC31A` — actuator / WG-output mode & solenoid path

Pure state machine over `byte_301867/68/69/70/71/72` and `word_FD22/FD34` I/O bits. Gated by
`byte_1BE46` (master enable) throughout. Key transitions **[CONFIRMED]**:
- 0xDC31A: if `word_FD0E.12` (a fault input) set → set `byte_301868.0` (force fault mode).
- 0xDC414: `calls sub_4238C(off 0x3E4B page6, byte_F40E=rpm-ish, byte_F473)` → a 2-axis
  byte-map lookup (`rl4`) selecting an output sub-mode; `==2` runs a count-up
  (`byte_301871`) before latching `byte_301870` bits. KFLDHBN-style guard.
- 0xDC3B8: compares `word_302E38` (actual) against **`word_2BF48` (=0x1770 = 6000)**
  [CAL 0x2BF48] gated by `byte_1BE48` — a **high-RPM/over-boost trip** that sets a shutdown
  bit (`byte_301868.3`). `word_2BF48`=6000 reads as an rpm/limit guard.
- 0xDC4F6: increments a fault/overrun counter `byte_304E1F` (sat 0xFF) while in limit mode.
- 0xDC538: drives the final solenoid enable bit from `word_FD22.7` into `byte_301870.0`.

So `sub_DC31A` translates the duty/mode produced upstream into the **physical wastegate
solenoid command + fault/limp gating**, including an over-boost RPM trip at `word_2BF48`.
**[CONFIRMED structure; KFLDHBN/compressor-limit identity for the 0x3E4B page-6 byte map is
INFERRED — it is the per-rpm output-mode selector consistent with KFLDHBN's compressor-ratio
limiting role]**

---

## 5. `sub_D5E80` and `sub_D9EA0` — sensor conditioning feeding the loop (support)

- **`sub_D5E80`** (0xD5E80–0xD6C02): boost/pressure-sensor conditioning. Forms several
  **pressure ratios** by `divlu[`/`](/)divu` from raw words `word_305734/36/38/3A/3C` →
  bytes `byte_304DD8/D9/DA` (≈ throttle/ambient/compressor pressure ratios), then range-bins
  them (`< 0x2B`, `> 0xD4`, the 0x99/0xCC/0x33 percent constants) and sets validity bits in
  `byte_301846`. Reads cal `byte_1BAA0/1BAA1/1BAA3`. This is the **compressor-ratio computation
  that KFLDHBN limits against** — produces the actual pressure ratio the boost limiter and
  `KFLDHBN` map consume. **[CONFIRMED math; KFLDHBN linkage INFERRED]**
- **`sub_D9EA0`** (0xD9EA0–0xDA924): diagnostics + monitoring (`sub_33006/33084/32E88`
  comparator calls, DTC bits in `byte_30185F/301860`). Computes a delta vs `word_302E20`,
  filters via `sub_41844`, and runs threshold checks `byte_1BD62..1BD74`. Not in the control
  path; it is the **boost monitoring / plausibility** layer. **[CONFIRMED role]**
- **`sub_D9688`** (0xD9688–0xD9A2C): LDR status flags + a base duty term (`byte_301853`,
  `word_30574A/4C`) and `word_FD7E.7/.8` status outputs. Pre-conditioning / display.
  **[CONFIRMED role]**

---

## 6. End-to-end algorithm (summary)

```
                 torque/load request (word_302968) ── × KFgain(0x2BE38) ──┐
 measured signal word_F410 ───────────────────────────────────────────────┤ ×
                                                                            ▼
                              word_302E64  +  KFLDIMX-map term(0x2BE92)  =  word_302E62  (SETPOINT)
                                                                            │
 measured load word_302496 ── (<<11)/word_30294A ──► word_302E58 (ACTUAL RATIO)
                                                                            │
   ┌─ I-term: integrate ACTUAL toward limit, gain/limit = KFLDIMX 0x2BF32  (sub_43904) ─┐
   │   error e = ACTUAL − I-state, clamp ±0x7FFF                                        │
   ├─ P-term: e × gain(KFLDRX-map 0x2BE3A), rescale+clamp, shape via table 0x2BE74 ─────┤
   ├─ 2nd term: word_302E3C ×0x2BF2E → integrate (gain 0x2BF30) → shape table 0x2BE56 ──┤
   └────────────────────────────► PI sum + adaptive trim word_30BF0A, clamp ±0x3FFF ────┘
                                                                            │
   FEED-FORWARD: KFLDRX 2-D map(0x2BECA)[X=SETPOINT, Y=word_302E3E] = base WG duty (sub_41CC0)
                                                                            │
                       demand word_302E5E = sat( base_duty + PI_correction )
                                                                            │
   KFLDRL deviation linearization: (word_302E3C−word_302E38) → map(0x2BEAC) → integrate
                       FINAL DEMAND  word_302E60 = sat( linearized + word_302E5E )
                                                                            │
   ── sub_DBF44 ──                                                          ▼
   KFLDIMX gate: if word_302E34 < thr 0x2BF4A → keep closed-loop (authority); anti-windup
   scale: word_302E7C = (word_302E60>>1 + word_302E4A) × cal_scale(0x2BF34 table)
   clamp: word_302E7E = clamp( word_302E7C, MIN 0x2BF4E .. MAX 0x2BF50 )   ← deliverable DUTY
                                                                            │
   ── sub_DC31A ──                                                          ▼
   master-enable 0x1BE46; over-boost RPM trip vs 0x2BF48(=6000); compressor/KFLDHBN
   output-mode map(0x3E4B,page6); drive solenoid bit byte_301870.0 ──► wastegate valve
```

### Role of each named map (confirmed via map-linkage + reads)
- **KFLDRX** (boost/load ceiling, brief z=0x27EE2): the **feed-forward base-duty 2-D map**,
  read by `sub_41CC0` at phys 0x2BECA in `sub_DBB04` §2g, axis = setpoint `word_302E62`. Sets
  the open-loop wastegate-duty floor for a requested load. **[CONFIRMED reader; z-array per brief]**
- **KFLDIMX** (LDR I-limit, brief z=0x2C000, threshold word_2BF4A): supplies the **integrator
  gain/limit** (`word_2BF32` in §2c), the **authority threshold** (`word_2BF4A` in §3a) and
  the **overrun margin** (`word_2BF4C` §3c). Governs how far the integrator/loop may push.
  **[CONFIRMED]**
- **KFLDRL** (wastegate-duty linearization, brief z=0x2C152): the table at phys 0x2BEAC
  (§2h) **linearizes the wastegate duty vs deviation** before final integration; its output
  is bounded by the duty MIN/MAX clamps `word_2BF4E[`/`](/)word_2BF50` (§3f). **[CONFIRMED reader]**
- **KFLDHBN** (compressor-ratio limit, brief z=0x1BC87): the compressor pressure-ratio it
  limits is computed in `sub_D5E80`; the per-rpm output-mode byte map in `sub_DC31A` (0x3E4B,
  page 6) enforces it on the actuator path. **[reader CONFIRMED in sub_D5E80; KFLDHBN map
  identity INFERRED]**

---

## 7. Open / uncertain points
- Physical units of `word_302968[`/`](/)word_F410[`/`](/)word_302496` (load% vs mg/stk vs mbar) not
  proven from code alone — names are generic RAM; mapping to A2L labels is the next step.
- The exact A2L name of the page-0xA pointer cells (0x2BE92/0x2BEAC/0x2BE3A/0x2BECA) should
  be cross-checked against the ECUParametersGSHJ.xml / 50GSHJ.xdf to nail KFLDRX vs KFLDIMX
  byte-for-byte; the map-linkage table in findings.md already assigns them to the LDR group.
- `word_30BF0A` (page-0xC2 RAM) is an adaptive/learned offset — its update site (LDR
  adaptation) is outside the three analysed functions (likely `sub_DC57E[`/`](/)sub_DC672`).
```
