# Volvo ME7.0 (50GPHJ) — Ignition timing & knock control algorithm

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

Reverse-engineered from the C167CR firmware in IDA
(DB `<work>\me7_stock_ign.i64`; code byte-identical across calibration revisions).
All addresses are physical (file offset). Calibration band ≈ 0x10000–0x2D000;
RAM = DPP2 page 0xC0 → physical base 0x300000; page 0xC1 → 0x304000.

Timing values in the code are **SBYTE** with scale **0.75°/count** (e.g. 0x7F=+95.25°,
0x80=−96°). Internal blends carry an extra fractional byte (word, /128) before the
final byte clamp.

Legend: **[C]** = confirmed in disassembly, **[I]** = inferred.

---

## 0. Top-level data flow

```
                RPM idx  word_3019B6 ─┐
                LOAD idx word_3019CA ─┤  (axis-prep, shared by all KFZW maps)
                                      ▼
  KFZW1..4 (byte maps) ── sub_411F4 ─► sub_518B8 ──► byte_30132E   (base advance, raw)
                                                       │
            IAT/load corr  sub_7CC7C ─► byte_30157C    │
            warmup/etc.               byte_3014F6      │
            adaptive       byte_30131D ────────────────┤
                                                       ▼
                                   sub_5086A: assemble per-firing advance
                                     out = byte_30132E
                                         + byte_30157C            (IAT/load corr)
                                         + byte_3014F6            (corr)
                                         + byte_12D85 (cal const) (corr)
                                         − byte_F3FA              (GLOBAL knock retard)
                                         + [cyl + 0x309545]       (per-cyl knock offset)
                                     → clamp ±[0x80..0x7F] → byte_F337 / output array
                                                       ▼
                                   sub_50984: per-cylinder dwell/output staging
                                     adds byte_301312, clamps to [rl7=0xE0 .. rl6=0x50]
                                     → output regs 0x309313/0x309317  (= "zwout")
```

The knock path (`sub_7BA8C` accumulator + `sub_7BD04` event handler) maintains
`byte_F3FA` (global retard) and the per-cylinder retard table at **0x30B24C**.

---

## 1. The byte-map lookup routine — `sub_411F4`  **[C]**  ← KEY DELIVERABLE

**Byte-map bilinear interpolation lookup is `sub_411F4` (0x411F4–0x4124A).**
This is the analogue of the word-map `sub_41A68`, but for **SBYTE z-maps with
pre-computed axis index+fraction words** (KFZW family, and several others).

Calling convention (different from `sub_41A68`):
```
r12 = map z-data offset (14-bit, within page)
r13 = pointer to the shared axis descriptor block (e.g. #502Ah)   ; NOT a page number
r14 = packed ROW axis word  : high byte = row index, low byte = row fraction*2
r15 = packed COL axis word  : high byte = col index, low byte = col fraction*2
→ rl4 (sbyte) = bilinearly interpolated map value
```

Disassembly (annotated):
```
411F4 movb rl2,[r13]        ; r13→ axis block: first byte = #columns (row stride)
411F8 mov  r1,r14 ; movbz r1,rh1   ; r1 = ROW index (high byte of r14)
411FC mulu r1,r13           ; row_index * stride
411FE add  r12,MDL          ; r12 = base + row*stride
41202 add  r12,(rh15)       ; + COL index (high byte of r15)  → cell pointer
41208 movb r4 = sbyte[r12]                 ; z00
4120C shl r15,#8 ; shr r15,#1 → col frac   ; jz skip col-interp
41212 z01 = sbyte[r12+1]; r4 += (z01−z00)*colfrac   ; interpolate along columns (low row)
41222 row frac = (r14<<8)>>1
41226 r12 += stride (next row); z10 = sbyte[r12+]
41230 z11 = sbyte[r12]; r2 = z10 + (z11−z10)*colfrac ; interpolate columns (high row)
4123E r4 = z0 + (r2−z0)*rowfrac            ; interpolate along rows
41248 rets                                  ; result in rl4/r4
```
This is standard 4-corner bilinear interpolation. The `(b−a)*frac` products use
`MDH` (the high word of the 16×16 multiply) so the fraction is treated as Q15.

**Callers of `sub_411F4`** (confirmed): `sub_4149C, sub_41682, sub_4F4BC, sub_50ED2,
sub_5172C, sub_518B8, sub_7177C, sub_A0000`. The ignition readers are
`sub_518B8` (KFZW base), `sub_50ED2` and `sub_5172C` (KFZW-family secondary maps).

### Shared axes
- `word_3019B6` and `word_3019CA` are the **pre-computed axis index+fraction words**
  (RPM and LOAD respectively) used by every KFZW lookup. They are written by an
  axis-prep step (register-indirect, no direct listing xref) and consumed read-only by
  the KFZW readers. **[C they are read-only in all ignition fns; I that B6=RPM, CA=load
  from the KFZW axes z=0x14FEE (RPM) / 0x1502C (load)]**
- `r13=#502Ah` is the axis-descriptor block pointer shared by all KFZW maps (`502A` page
  resolves to the KFZW axis region). First byte = column count = row stride. **[C]**

---

## 2. Base ignition timing — `sub_518B8` (0x518B8–0x51AF4)  **[C]**

Reads the four base-timing maps and blends them by the two cam-phase (VVT) fractions.

KFZW map z-data offsets (page 4, physical = 0x10000+offset):
| Map   | r12 imm | physical |
|-------|---------|----------|
| KFZW1 | 0x33B1  | 0x133B1  |
| KFZW2 | 0x3471  | 0x13471  |
| KFZW3 | 0x3531  | 0x13531  |
| KFZW4 | 0x35F1  | 0x135F1  |

Each is fetched with `sub_411F4(offset, #502Ah, word_3019B6, word_3019CA)` → sbyte
advance at the current (RPM, load) operating point.

Blend math (two-stage linear interpolation by two cam fractions):
```
f1 = byte_30129C          ; cam-phase pair #1 fraction (0..0xFF), [I intake-cam phase]
f2 = byte_30129B          ; cam-phase pair #2 fraction,           [I exhaust-cam phase]

A = KFZW1*(1−f1) + KFZW2*f1   → word_3024A8   (saturate +0x7FFF)
B = KFZW3*(1−f1) + KFZW4*f1   → word_3024AA
Z = A*(1−f2)    + B*f2        → word_3024AC   (this is the interpolated base advance,
                                                kept as a Q-fixed word, /256 high byte)
```
(The mul/`ashr #1[`/`](/)bmov .15`/MDH sequences at 0x518F0–0x51A66 implement signed
`a*frac` with rounding; `and #7FFFh`+halving handles the sign of the multiplier — the
firmware's standard signed fixed-point multiply idiom.)

Final byte conversion + clamp (0x51A74–0x51AE8):
```
word_3024AC → take signed, /256, clamp to [0xFF80 .. 0x7E] (≈ ±95°) → r6
sign-correct → byte_30132F           ; base advance, signed byte
rl6  = byte_3012FD                    ; + cal offset (base adder)
     + byte_3012FE                    ; + cal offset
     + byte_304050 (page 0xC1)        ; + RAM correction term (extp #0C1h)
     + byte_30132F                    ; + the interpolated base advance
     (each add saturates at 0x7F)
→ byte_30132E                         ; RAW BASE IGNITION ADVANCE  [C]
```
`byte_30132E` is the master "base timing before knock & per-cyl" value, consumed by
`sub_5086A` (output assembly) and by `sub_877EC` (OBD deviation monitor).

`sub_518B8` is invoked from the engine-position/segment task at 0x0B494
(`calls 5, sub_518B8`, in the synchronous scheduler region). **[C]**

---

## 3. Secondary / corrective KFZW maps — `sub_50ED2`, `sub_5172C`  **[C]**

These run alongside the base lookup and use the **same axes** (word_3019B6/CA, ptr 0x502A).

`sub_5172C` (0x5172C–0x5186A): two more KFZW-family maps
- offset 0x32F1 → `byte_30132B`, offset 0x3231 → `byte_30132C`
- each result is `map * byte_30132D` (a gain from `sub_40B3E`, map 0x5BA2) `>> 6`,
  clamped to ±[0x80..0x7F]. **[I: a load/condition-scaled spark trim, e.g. catalyst-heat
  or transient enrichment timing]**

`sub_50ED2` (0x50ED2–0x5152C): the **operating-mode advance selector / limiter**.
- Picks one of several KFZW-family maps (offsets 0x316B→byte_301326, 0x2FEB or 0x2F2B
  →byte_301324, 0x30AB→byte_301327, depending on mode bits in `byte_12F17` cal and state
  flags FD66/FD1C/FD24).
- Builds an upper/lower advance window and rate-limits the commanded advance toward it
  (the long `[r0]/[r0+2]` 32-bit accumulator blocks at 0x5123E–0x51470 are slew/ramp
  limiters between byte_301325, byte_301326, byte_300231/2 with min/max clamps).
- Adds `byte_3012FD`, then subtracts `byte_30132C` (the sub_5172C trim) and produces
  `byte_301329` / `byte_301322`, used by the per-cylinder output stage.
- Reads a small interpolation table at `[r4+#2A15h]` (cal 0x12A15) for an angle/efficiency
  conversion when |advance| < 0x78. Same table `[r4+#2A15h]` is reused in the knock
  monitor `sub_877EC`. **[I: spark-angle → torque-efficiency factor (ETAZW)]**

These confirm the base advance is post-processed through a **mode-dependent map select +
rate/ window limiter** before the knock subtraction.

---

## 4. IAT / temperature & load corrections — `sub_7CC7C` (0x7CC7C)  **[C]**

Writes `byte_30157C`, the correction term added in `sub_5086A`.
```
t1 = curve(#159F p6 ; #27D1 p4)  via sub_4210C   ; [I temp/IAT axis 2D map]
m  = map(#15E7 p6 ; #2826 p4) via sub_42180       ; second 2D map
prod = (t1 * m) >> 7
final = prod + map3(#1DD4/#1DCC p8 indexed by byte_21DCA/CB, sub_42596)
      using byte_F473 (the **load** byte = rl>>5, **not** a temp sensor — see ram-names.md) and byte_30163A (rpm-class index)
→ clamp ±[0x80..0x7F] → byte_30157C                ; IAT/temperature ignition correction
```
So intake-air-temperature/coolant ignition correction **is present and additive**:
`byte_30157C` enters the spark sum in `sub_5086A` at 0x50874. **[C additive; I that the
159F/15E7 maps are the IAT/temperature correction maps]**

`byte_3014F6` (second additive corr in sub_5086A) and `byte_12D85` (a flat cal byte) are
the remaining correction inputs. `byte_30131D` (from `sub_50C4C`, an adaptive/octane-style
term built from cal 0x15B64/0x15B66 via sub_4149C plus RAM byte_30021E) feeds the
alternate branch when FD24.14 is set. **[C inputs; I their exact physical meaning]**

---

## 5. Knock control — retard path  **[C]**

### 5a. Where knock subtracts from advance — `sub_5086A` (0x5086A–0x50984)
This is the per-firing spark-advance assembler. For each cylinder slot it computes:
```
r9 = byte_30132E            ; base advance (from §2)
   + byte_30157C            ; IAT/temp correction (§4)
   + byte_3014F6            ; correction
   + byte_12D85 (cal)       ; correction
   − byte_F3FA              ; *** GLOBAL KNOCK RETARD ***  (subtracted)  [C]

per cylinder (index r8 = byte_30125D, current firing cyl 0..4):
   advance_cyl = r9 + sbyte[r8 + 0x9545]    ; *** per-cylinder knock offset ***
        (when FD24.14 set, instead uses byte_30131D + byte_3014F6 + cal as the base)
   clamp to [0xFF80 .. 0x7F]                 ; (−96° .. +95.25°)
   store → byte_F337 / paged output, advance r6 (output ptr), advance cyl mod 5
```
- **`byte_F3FA`** = the **global knock retard** (one value, all cylinders), subtracted
  directly from the advance. Larger F3FA ⇒ more retard ⇒ less advance.  **[C]**
- **0x309545** = a **5-entry per-cylinder retard/offset RAM table** (`[cyl+0x9545]`,
  DPP2 page). Added per cylinder so individual cylinders can carry extra retard. **[C]**

### 5b. Knock-retard accumulator — `sub_7BA8C` (0x7BA8C)  **[C]**
Produces `byte_F3FA`:
```
byte_F3FA = byte_301571 + byte_301572       ; (saturate 0xFF)  at 0x7BCB4
```
- `byte_301572` = base/maximum knock retard pulled from a 2D map at offset 0x1572 (page 6)
  via `sub_42046`, indexed by `word_3019AE`. **[I: KFZW2KR-style "knock retard amount" map]**
- `byte_301571` = a per-event retard step looked up from table `[byte_30155C + 0x0B24C]`
  (the per-cylinder retard table base, see 5c) at 0x7BC7E. **[C]**
- Gated by knock-enable state bits in `word_FD44/FD46` and the RPM-class threshold
  `byte_30163A` vs cal `byte_139BD` (0x7BC1C). Below that RPM, knock control is suppressed.

### 5c. Knock-event handler & per-cylinder retard table — `sub_7BD04` (0x7BD04)  **[C]**
Maintains the per-cylinder retard table at **physical 0x30B24C** (`#0B24Ch`, DPP2),
indexed by the knocking cylinder `byte_3006D8`:
```
ON KNOCK (FD46.0):
   tbl[cyl] += byte_139B7        ; KR step per detected knock     (cal 0x139B7)  [C]
   clamp tbl[cyl] ≤ byte_139B6   ; max per-cylinder retard        (cal 0x139B6)
KNOCK-FREE recovery (no knock this window, FD44.15):
   compute ratio = (F400*255)/(F3FE+F400) via mulu/divlu → byte_301574  (advance-restore %)
   if byte_139BC ≤ that ratio:    tbl[cyl] -= 1                   ; step advance back in
   clamp tbl[cyl] ≥ byte_139B9   ; min (cal 0x139B9)
GLOBAL retard recovery (0x7BE48): every byte_301573 ticks,
   byte_F3FA -= byte_139B8 (clamp ≥0); reload counter from byte_139BA   ; recovery rate
```
- It also reads a per-cylinder **knock-intensity / count** table at `[byte_301518 + 0x951C]`
  (0x7BE24) scaled by cal `byte_139BB`, compared against `byte_F3ED`, to decide advance vs.
  retard (FD44.11/.12). **[C]**
- Calibration constants (page 4 cal band, ~0x139B6–0x139BD): step up `0x139B7`, max `0x139B6`,
  min `0x139B9`, recovery step `0x139B8`, recovery period `0x139BA`, enable/ratio thresholds
  `0x139BB/0x139BC`, RPM-enable `0x139BD`. **[C — these are the KR / knock-control calibration
  bytes]**

### 5d. Knock value source
`byte_30131B/byte_30131C` are written by `sub_50984` (0x50BB0/0x50BB8) and `byte_30131C` is
consumed by `sub_D83F4` (knock-evaluation block at 0xD8xxx). The cylinder selector is
`byte_30125D`. **[C linkage; I that sub_D83F4 is the knock-sensor window evaluation]**

---

## 6. Final spark advance output (zwout) — `sub_50984` (0x50984–0x50BC6)  **[C]**
Takes the per-cylinder advances produced by `sub_5086A` (and `byte_301329` from the
mode limiter) and stages them into the ignition output registers:
```
output base pointers: r8=#9313h (input per-cyl advances), r9=#9317h (output array)
for each cylinder:
   v = per_cyl_advance + byte_301312     ; + global dwell/output offset, saturate 0x7F
   clamp HIGH = rl6 = 0x50   (+60°)      ; max advance limit
   clamp LOW  = rl7 = 0xE0   (−48°)      ; min (most-retarded) limit
   store v → output array @0x309317.. ; loc_F33A mirror
final compare vs byte_301313 sets/clears a sync flag (FD22.11) and per-cyl mask byte_F339
byte_30131C = output[cyl]  ; byte_30131B = ~output[cyl]   (the actual emitted advance)
```
`0x309317`-based array and `byte_F337/F338/F339` are the values handed to the ignition
output (timer/coil scheduling) hardware. This is **zwout** — the final, per-cylinder,
clamped spark advance in 0.75°/count. **[C]**

---

## 7. OBD / misfire deviation monitor — `sub_877EC` (0x877EC)  **[I, not in control path]**
Reads `byte_30132E` (0x87B26) only to compute `byte_30479E = byte_301303 − byte_30132E`
(commanded-vs-reference advance deviation), passes it through the same `[r4+#2A15h]`
efficiency table, and accumulates filtered diagnostics (sub_43904/438F6/41A68 with maps
@ page 8). It does **not** feed back into spark; it is the catalyst/efficiency & misfire
diagnostic. Useful as confirmation that `byte_30132E` is the canonical base advance and
`byte_301303` is the reference/target advance.

---

## 8. Summary of confirmed addresses

| Symbol | Phys addr | Role | C/I |
|---|---|---|---|
| **sub_411F4** | 0x411F4 | **byte-map bilinear lookup** (KFZW etc.) | C |
| sub_518B8 | 0x518B8 | KFZW1-4 read + cam-fraction blend → base advance | C |
| sub_50ED2 | 0x50ED2 | mode-select + slew/window limiter | C |
| sub_5172C | 0x5172C | secondary spark trim maps | C |
| sub_7CC7C | 0x7CC7C | IAT/temperature ignition correction → byte_30157C | C/I |
| sub_5086A | 0x5086A | per-firing spark sum, knock subtraction | C |
| sub_50984 | 0x50984 | final per-cyl output staging (zwout) | C |
| sub_7BA8C | 0x7BA8C | knock retard accumulator → byte_F3FA | C |
| sub_7BD04 | 0x7BD04 | knock event handler + per-cyl retard table 0x30B24C | C |
| KFZW1/2/3/4 z | 0x133B1/0x13471/0x13531/0x135F1 | base timing maps (sbyte) | C |
| KFZW axis ptr | 0x502A (block); axes z=0x14FEE/0x1502C | RPM/load axes | C/I |
| word_3019B6 / word_3019CA | RAM | RPM / load axis index+frac words | C / I |
| byte_30129C / byte_30129B | RAM | cam-phase blend fractions f1 / f2 | C/I |
| word_3024A8/AA/AC | RAM | KFZW12 / KFZW34 / final base blends | C |
| byte_30132E | RAM | base advance (pre-knock) | C |
| byte_30157C / 3014F6 / 12D85 | RAM/cal | IAT-temp / corr / cal-const additions | C |
| byte_F3FA | RAM | **global knock retard** (subtracted) | C |
| 0x309545[cyl] | RAM | **per-cylinder knock offset table** | C |
| 0x30B24C[cyl] | RAM | per-cylinder retard accumulator (KR) | C |
| byte_301571/301572 | RAM | knock retard step / map-amount components of F3FA | C |
| cal 0x139B6..0x139BD | ROM | knock-control calibration set (step/max/min/recovery/enable) | C |
| 0x309313/0x309317 | RAM | per-cyl advance in / emitted out (zwout) | C |
| byte_30125D | RAM | current firing cylinder index (0..4) | C |
| sub_877EC | 0x877EC | OBD spark deviation monitor (not control path) | I |

---

## 9. Algorithm in one paragraph

At each engine segment the firmware computes axis index/fraction words for RPM
(`word_3019B6`) and load (`word_3019CA`), then `sub_518B8` reads the four base-timing
maps **KFZW1..4** (sbyte, 0.75°/count) through the byte-map bilinear interpolator
**`sub_411F4`** and blends them with two cam-phase fractions (`byte_30129C`, `byte_30129B`)
to a single interpolated base advance, adds calibration/RAM base offsets, and stores the
raw base advance in **`byte_30132E`**. `sub_50ED2[`/`](/)sub_5172C` apply mode-dependent map
selection, secondary trims and a slew/window limiter. `sub_7CC7C` produces the
IAT/temperature correction `byte_30157C`. `sub_5086A` then forms the per-firing advance =
base + IAT/temp + corrections **− global knock retard `byte_F3FA`** **+ per-cylinder knock
offset `0x309545[cyl]`**, clamps to roughly −96°..+95°. The knock subsystem
(`sub_7BA8C` + `sub_7BD04`) detects per-cylinder knock, increments a per-cylinder retard
accumulator at `0x30B24C[cyl]` by cal `0x139B7` up to `0x139B6`, recovers it one count at a
time and bleeds the global `byte_F3FA` back toward zero at cal rate `0x139B8[`/`](/)0x139BA`,
gated above RPM-class `0x139BD`. Finally `sub_50984` clamps each cylinder's advance to the
output window (−48°..+60°) and writes the emitted spark advance ("zwout") to the ignition
output array at `0x309317`.
