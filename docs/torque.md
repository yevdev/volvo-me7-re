# Volvo ME7 (50GPHJ) C166 — Torque structure (pedal → torque → load request → boost)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The torque structure, traced through the C166 disassembly of the stock 50GPHJ firmware
(Infineon C167CR). Disassembly dumped from `<work>\me7_stock_torque.i64` via
`scripts/ida/ida_dump_func.py`. The code is byte-identical across calibration revisions.

This document traces the Bosch ME7 **torque-based structure** ("Momentenstruktur"):

```
pedal angle ──KFPED──► driver torque request (% indicated)
                           │
        (inverse torque model: KFMIOP optimum indicated torque,
         corrected for ignition efficiency / lambda / friction)
                           │
                  ──KFMIRL──► required relative cylinder charge  rlsol  (load %)
                           │
                  rlsol  is the load SETPOINT that LDR boost control targets,
                  clamped against the boost ceiling KFLDRX.
```

Confidence is marked **[CONFIRMED]** (read directly from the listing) or
**[INFERRED]** (standard ME7 semantics applied to the observed arithmetic / A2L names).

---

> **⚠️ Later corrections — read the body with these in mind.** This doc predates three findings that
> refine some cell identities used below (the data-flow/arithmetic stay correct; only the labels change):
> - **`word_F410` is `nmot` (engine speed), NOT `rl_w`** — see [ram-names.md](ram-names.md). Where §3/§4/§5
>   call it the "measured load / `rl_w`" feedback, read **engine speed**. The genuine measured load `rl` is
>   **`loc_F47A`/`byte_F473`** — see [load-rl.md](load-rl.md).
> - **`sub_4F97A` is also the rev limiter**: the `0x15848–0x1585C` "ceiling words" (incl. `0x1584E`) are the
>   **NMAX rev-limiter cals** (rpm), not load ceilings — see [limiters.md](limiters.md). The §3a "gate"
>   comparing `word_F410` vs `word_1584E` is the rev-limit compare (`nmot` vs NMAX = 6500 rpm).
> - The arbitration/conditioning that feeds KFMIRL is the **torque coordinator** (§3b, `sub_4D86C`).

## 0. The map-lookup primitives (how to read CAL accesses)

The torque code does **not** use a single lookup routine. It uses a family of
interpolators, each with a different fixed-point format. Decoded from the listing:

| Routine | Signature (regs in) | Math | Used for |
|---|---|---|---|
| `sub_41A68` | r12=offset, r13=page, r14=input → r4 | 2-D **word** map, byte axes; breakpoint search + `mulu/divu` linear interp | LDR / pressure maps keyed by `word_F410` |
| `sub_419F4` | r12=offset, r13=page, r14=input → rl4 | 1-D **byte** table, byte axis; `mulu/divu` interp (see 0x41A4A–0x41A50) | status/selection byte tables |
| `sub_40B3E` | r12=offset, r13=page(byte), → rl4 | 1-D **byte** table, `mul/divl` signed interp | scalar byte breakpoint tables (e.g. ign-efficiency, cyl count) |
| `sub_43430` | r12=base, r13=ptr-to-cols, r14/r15=fractional X/Y | 2-D **word** map, **two-axis** bilinear, MDH-scaled (`>>8` per axis) | **KFMIOP** optimum-torque model |
| `sub_411F4` | r12=base, r13=col-ptr, r14/r15=frac X/Y | 2-D **word/byte** signed bilinear (`shl #1; mul …; +MDH`) | KFMIOP correction sub-maps |
| `sub_41434` | r12,r13,r14,r15 (reordered) → `sub_40A5A`+`sub_41126` | 1-D interp wrapper | KFMIOP scalar correction |
| `sub_40EB0` | r12=base, r13=input → r4 | **axis search**: returns interpolation index+fraction (`divlu`) | locating the operating point on KFMIOP axes |
| `sub_42DF4` | r12,r13 (signed), r14:r15 accum → r4:r5 | 32-bit signed `mulu` MAC with saturation | KFMIRL torque×factor accumulation |

`sub_41A68` interpolation core (the canonical one), **[CONFIRMED]** 0x41A4A:
```
sub  r3, r4              ; (hi_break - axis_value)
mulu r3, r2              ; × (Δ between cell values)   -> MDH:MDL
divu r5                  ; ÷ (Δ between breakpoints)
add  r4, MDL             ; cell_lo + interpolated step
```
i.e. classic `y = y0 + (y1−y0)·(x−x0)/(x1−x0)` in unsigned fixed point.

---

## 1. KFPED — pedal → requested torque  (z @ 0x1E776)

**[INFERRED, with confirmed pieces]** KFPED is the driver-demand map: axes =
(pedal angle %, engine speed rpm), output = requested indicated torque as a
percentage (`mireq[`/`](/)wped` family in ME7). The task brief and the map inventory
place its data block at z=0x1E776 (page 7).

`sub_4E6F6` (0x4E6F6–0x4E774) **[CONFIRMED to be a status/range helper, NOT the
interpolator]**: it selects between two calibration words `word_1E774` /
`word_1E772` based on a mode byte (`byte_31D4DD`), stashes the choice into
`word_304F2A`, then calls `sub_419F4(offset=0x1D1, page=6, input=byte_31D63A)`
and unpacks the result bit-by-bit into the flag word `word_FD1A.6..13`. This is
the pedal-channel **plausibility/selection** logic that feeds the pedal value
used downstream, not the KFPED interpolation itself.

The actual pedal-angle axis value lands in the pedal RAM cell consumed by the
torque request; the KFPED 2-D interpolation (z=0x1E776) is performed by the
word-map path (`sub_41A68`-class) keyed on processed pedal + rpm. The brief's
linkage table (`KFPED → sub_4E6F6`) reflects the map's *reader region*; the raw
z-block read is the data backing the driver-request torque `mizsol/mireq`.

Output of this stage **[INFERRED]**: **driver requested indicated torque**
(`mibas_w` / `milsol_w` family in the A2L — both names present in the ME7 A2L).

---

## 2. KFMIOP — optimum indicated-torque model  (z @ 0x156CC)

`sub_4F4BC` (0x4F4BC–0x4F844) is the **inverse torque model evaluator**
**[CONFIRMED]**. It is the heart of the structure: given the current operating
point it computes the engine's *optimum* (best-case, MBT-timing, stoich) indicated
torque, and the correction terms that scale actual achievable torque against it.

Confirmed sequence:

1. **Axis location** — `sub_40EB0(0x582C, loc_F47A)` → fractional index into the
   KFMIOP axis; result stored to `word_31DAE8` (0x4F4D2). (0x582C is the axis/
   map descriptor base in page region for the torque model.)
2. **KFMIOP main lookup** — `sub_43430(0x56CC, 0x582C, axis_x@31D9B4, axis_y=r4)`
   → optimum torque, stored to `word_31DAEC` (0x4F4E8). **0x56CC = KFMIOP z**.
3. **Two correction maps** via `sub_411F4` at offsets **0x2AA2** and **0x2B52**
   (0x4F4FC, 0x4F514), then **0x2C02** and **0x2CB2** (0x4F59E, 0x4F5B6). Each
   result is blended with the operating-point fractions held in `byte_31D29C` /
   `byte_31D29B` using the standard `mul + ashr #1 + addc` half-LSB-rounded
   fixed-point interpolation (0x4F52A–0x4F58A, repeated). Intermediate products
   land in `word_31DAF0`, `word_31DAF2`, `word_31DAF4`.
4. **Saturation / sign handling** (0x4F6B8–0x4F70E): the combined value is clamped
   to ±0x7FFF and split into a signed byte `byte_31D304` and magnitude used below.
5. **Scalar corrections** — `sub_40B3E(0x2A8D, byte@31D5B9)` → `byte_31D2FF`
   (ignition-efficiency / etazwopt-class byte table), and
   `sub_41434(byte_156B6, 0x56B7, 0x56C1, byte@31D5B9)` → `byte_31D2FE`.
   These are the **ignition-angle efficiency** and related multiplicative
   corrections that convert "optimum" torque to "currently-deliverable" torque.
   **[INFERRED: etazw/efficiency correction]**
6. **Final torque scaling** (0x4F73A–0x4F786): two `mulu … ×0xA4` chains scale the
   torque value by a constant (0xA4 = 164, an Nm-per-% conversion constant) into
   `word_31DAEE` and `word_31DAEA`, with overflow saturated to 0xFFFF.
7. **Sum of byte corrections** (0x4F79C–0x4F7E4): adds the per-cylinder /
   efficiency byte corrections (`byte_304049`, `byte_31D2FD`, `byte_31D2FE`) and
   clamps the signed result to [−0x80, +0x7F] into `byte_31D303`.
8. **Cylinder averaging** (0x4F7F2–0x4F834): loops 5 iterations over a
   per-cylinder array `[r4+0x9306]`, accumulates into `word_31DAF6`, then
   `divu #5` → `byte_31D302` (average over the 5 cylinders — confirms a
   **5-cylinder** application, the Volvo white-block).

**Net result of `sub_4F4BC`:** the model-derived torque figures
(`word_31DAEC` = optimum, plus efficiency-corrected products `word_31DAEE` /
`word_31DAEA`) and the byte correction `byte_31D303` that subsequent stages use
to turn a *torque demand* into a *load demand*. **[INFERRED: milsol/miszul]**

---

## 3. KFMIRL — torque ↔ load conversion → rlsol  (z @ 0x158A4)

`sub_4F97A` (0x4F97A–0x4FE7E) is the **load-setpoint generator** **[CONFIRMED]**.
It is the stage that produces the relative-charge setpoint `rlsol` that LDR boost
control then targets. `sub_4F95E` (0x4F95E–0x4F97A) is its small init prologue:
it seeds the load RAM (`word_31E484` from `byte_12D63<<8`, `word_31E486` from
calibration `word_1584E`) — a fallback/default load.

### 3a. Engine-running gate & default load (0x4F97A–0x4FAFE) **[CONFIRMED]**
- Compares the master pressure/flow signal `word_F410` against calibration
  `word_1584E` and maintains a bank of mode flags in `byte_31C1F4` and `word_FD22`
  with debounce down-counters `81FA[`/`](/)81F2` (decrement-to-zero timers).
- Depending on those flags it loads `word_31E486` (the working load value) from
  one of several calibration words: `word_15858` (max-rl), `word_1584E`
  (default-rl), or a slewed value `r7 = 0xA486 − word_15844` clamped between
  `word_1584E` and `word_15858`. These are the **rl limit/ramp calibrations**
  (KFMIRL axis-region constants). `word_31E486` is the running relative-load
  working value. **[INFERRED: rl / rlsol working register]**

### 3b. Boost ceiling clamp (0x4FB40–0x4FBFA) **[CONFIRMED — this is the KFLDRX link]**
- A second load register `word_31C200` is slewed: `r7 = 0xC200 − word_15846`,
  clamped between `word_15852` (lower) and `word_15858` (upper).
- The candidate load `r9` is then **clamped down** against several ceilings:
  - `word_15856` (if `word_FD5C.1` set) — 0x4FBAA,
  - `word_31C200` (the slewed upper, if `word_FD7A.4`) — 0x4FBB8,
  - `word_15854` (a hard max, gated by `word_FD22.3`) — 0x4FBF0.
  - When flag `loc_FD70.9` is set it forces `r8 = word_1585A` (a fixed
    fallback ceiling) — 0x4FB9E.
- **This min-with-ceiling chain is precisely the link to KFLDRX**: `rlsol` may
  request a high load from the driver/torque path, but it is saturated to the
  maximum-permissible relative charge derived from the boost-limit calibration
  set (KFLDRX/KFLDIMX region). Raising those ceiling words is what lets a tune
  request more boost. **[INFERRED that the specific clamp words are the KFLDRX/
  KFLDIMX-derived rlmax; CONFIRMED that they are calibration words acting as an
  upper saturation on the load setpoint.]**

The clamped result is written to **`word_31E48A`** (0x4FC1E) — the gated load
candidate.

### 3c. rlsol assembly & rate limiting (0x4FC22–0x4FE7E) **[CONFIRMED]**
- `word_31E48A + word_15848` (offset cal) → compared to `word_F410`; sets
  `word_FD22.2` (a "load achieved / above-ambient" condition) — 0x4FC22.
- A precontrol/feed-forward term is computed from `0xAB0A` (a torque-reserve word)
  via `ashr #5` × `81FC` (0x4FC4E) and added to `word_F410` into `word_31E488`.
- **Setpoint error** `word_31E480 = word_31E48A − word_31E488` (0x4FC78), clamped
  to ±0x7FFF/±0x8000 — this is the load **deviation** (`drlsol_w` in the A2L).
- Two parallel scalings then form the final relative load:
  - `sub_42DF4(byte_30404A<<8, word_31E480, accum 81F8:81F6)` — a saturating
    32-bit MAC integrator (0x4FCF6) producing `81F6/81F8`, rescaled `>>13`
    into `word_31C202/31C204` and clamped to ±0x7FFF → `word_31E47C` (0x4FD52).
    **[INFERRED: integral/PT1 portion of rlsol]**
  - A direct path: `byte_30404B × 0x29` then `× word_31E480` (`mul`,
    `ashr #1`, `addc`) → `[r0]/[r0+2]`, clamped, `>>7` → `word_31E47E`
    (0x4FDF6). **[INFERRED: proportional portion]**
- **Final sum** (0x4FE08): `r6 = word_31E47C + word_31E47E` (saturated), then
  combined with the prior load `word_304F30` (`shr #1 … addc` — a 0.5/0.5 average
  / PT1 smoothing, 0x4FE18), saturated, and clamped to a max of
  `byte_12D63 << 7`. The result is written to **`word_31E482`**, doubled, and
  stored to **`word_31E484`** (0x4FE5C–0x4FE6E).
- If the "load not achieved" flag `word_FD22.2` is set, `word_31E484` is forced
  to 0 (0x4FDFE) — i.e. no positive load demand when below ambient.

**`word_31E484` (offset 0xA484) is the produced relative-load setpoint** — the
ME7 `rlsol_w` — fed forward to LDR boost control. Its smoothed predecessor is
`word_304F30`, its pre-clamp value `word_31E482`, the error term `word_31E480`
(`drlsol_w`), and the two component contributions `word_31E47C` (I) and
`word_31E47E` (P). **[INFERRED variable identity from arithmetic + A2L name set;
CONFIRMED data flow.]**

---

## 3b. Torque coordinator — arbitration & limit conditioning (`sub_4D73A` → `sub_4D86C`)  **[CONFIRMED]**

Between the torque model and KFMIRL sits a coordinator that arbitrates the competing torque/load demands
and conditions them into the setpoint words KFMIRL's region consumes. Two stages, on the `sub_B81C` page-4
torque block (its resolved tail `sub_4E3AE` is called at `0x0B854`, ahead of the load/boost/fuel stages):

- **`sub_4D73A`** (0x4D73A–0x4D84E) — **arbitration**: min-combines the load setpoint `rlsol`
  (`word_31E484`), the VMAX torque ceiling `word_304F3C` ([limiters.md](limiters.md)) and the KFMIOP torque
  words, emitting the **arbitrated target torque `word_31DAB2`**. **[C]**
- **`sub_4D86C`** (0x4D86C–0x4E3AE) — **conditioning**: tracks `word_31DAB2` through PT1 filters
  (`sub_43904`), saturating MAC integrators (`sub_42DF4`) and a KFMIOP-class 2-D torque map (`sub_43430`,
  base `0x51F0`), gated by a dense mode/limit flag machine (`word_FD1A/1C/1E`). It writes the conditioned
  setpoint words **`word_31E43C/3A/40/42`** + status byte `byte_31D2F1`, consumed by the KFMIRL/`rlsol`
  region (`sub_4F0xx`–`sub_4F2xx`). Config cals are the `CDTU*`/`CDTTX2S` coordinator codeword family
  (`0x150EE–0x150FA`) + delta/limit cals `DVFGREU`/`DVIVZMX`. **[C]**

```
0x4DDC8  mov   r12, #51F0h          ; KFMIOP-class 2-D torque map (limit path)
0x4DDD8  calls 4, sub_43430         ; bilinear torque lookup
0x4DF18  calls 4, sub_42DF4         ; saturating MAC integrate (tracks word_31DAB2)
```

**It writes only torque/load words and flag bits — no throttle/DK actuator, PWM, or port** (verified: zero
port/PWM writes). This matches the idle-governor finding that the bin has **no direct throttle servo**: the
torque structure conditions arbitrated torque into the load setpoint (`rlsol`), and the air path realises it. **[C]**

## 4. The link to boost control (KFLDRX / KFLDIMX)

The boost controller analyzed previously (`sub_DBB04` / `sub_DBF44`, findings.md
§"Key discovery #2") consumes a **target relative load** and drives wastegate
duty to make actual charge (`word_F410`-derived) meet it. The torque structure
above is what *produces* that target:

```
KFPED (pedal,rpm) ──► requested torque  [sub_4E6F6 region / word path, z=0x1E776]
        │
KFMIOP inverse torque model  [sub_4F4BC, z=0x156CC]  ──► milsol/efficiency-corrected torque
        │
KFMIRL torque→load + rate-limit  [sub_4F97A, z=0x158A4]
        │   └─ clamped against boost ceiling cals (KFLDRX/KFLDIMX-derived rlmax)  ← §3b
        ▼
   rlsol  =  word_31E484  (0xA484)         ← the load request RAM variable
        │
        ▼
LDR boost control  [sub_DBB04 / sub_DBF44, page 0xA]  ──► wastegate duty
        (uses KFLDRX as the ceiling on the rl it will chase; KFLDRL feed-forward)
```

`word_F410` (the measured load/pressure feedback) appears in **both** the
torque-structure (KFMIRL gate/error, §3) and the boost controller — confirming it
as the shared **actual relative charge `rl_w`** plant variable. The torque
structure sets the setpoint `rlsol`; the boost loop closes on `rl_w` vs `rlsol`,
ceilinged by KFLDRX.

---

## 5. Key addresses (quick reference)

Functions:
- `sub_4E6F6` 0x4E6F6 — pedal-channel selection/plausibility (KFPED region z=0x1E776)
- `sub_4F4BC` 0x4F4BC — KFMIOP optimum-torque model evaluator (z=0x156CC)
- `sub_4F95E` 0x4F95E — KFMIRL/rlsol init prologue
- `sub_4F97A` 0x4F97A — KFMIRL torque→load → **rlsol** generator (z=0x158A4)
- Lookups: `sub_41A68`, `sub_419F4`, `sub_40B3E`, `sub_43430`, `sub_411F4`,
  `sub_41434`, `sub_40EB0`, `sub_42DF4`

Map z-blocks (calibration, file offsets):
- KFPED z=0x1E776 · KFMIOP z=0x156CC · KFMIRL z=0x158A4
- KFMIOP axis/descriptor base 0x582C; correction sub-maps at offsets 0x2AA2,
  0x2B52, 0x2C02, 0x2CB2 (page region per `sub_411F4` base)
- KFMIRL limit/ramp calibration words (page 6, z-region 0x1584x–0x1585x):
  `word_1584E` (default rl), `word_15858` (max rl), `word_15852`, `word_15854`
  (hard max / KFLDRX-derived), `word_15856`, `word_1585A`, `word_15844`,
  `word_15846`, `word_15848` (offset), `word_1584A`, `word_1584C`

RAM (load/torque structure, RAM segment base 0x300000):
- **`word_31E484` (0xA484) = rlsol_w** — relative-load setpoint output (the load request)
- `word_31E482` (0xA482) — pre-clamp rlsol
- `word_304F30` — smoothed previous rlsol (PT1 history)
- `word_31E480` (0xA480) — rlsol error / `drlsol_w`
- `word_31E47C` (0xA47C) — integral component · `word_31E47E` (0xA47E) — proportional component
- `word_31E48A` (0xA48A) — boost-ceiling-clamped load candidate
- `word_31E486` (0xA486) — running rl working value · `word_31E488` (0xA488) — feed-forward load
- `word_31C200`, `word_31C202/04`, `81F6/81F8/81FA/81F2` — slew/timer/accumulator state
- KFMIOP intermediates: `word_31DAE8/EA/EC/EE/F0/F2/F4/F6`, `byte_31D302/03/04`
- `word_F410` — measured relative charge **`rl_w`** (shared plant variable)
- Flag words: `byte_31C1F4`, `word_FD22`, `word_FD7A`, `word_FD5C`, `word_FD70`, `word_FD1A`

---

## 6. Confirmed vs inferred — summary

**Confirmed from listing:**
- The interpolator family and `sub_41A68`'s exact interp formula.
- `sub_4F4BC` is the KFMIOP optimum-torque model (reads z=0x56CC via `sub_43430`),
  performs efficiency/correction blends, ×164 torque scaling, 5-cylinder averaging.
- `sub_4F97A` produces a relative-load setpoint via P + I(MAC) + PT1 smoothing,
  saturated against a stack of calibration ceiling words, output to `word_31E484`,
  zeroed when below-ambient; the error term and component split.
- `word_F410` is the shared measured-load variable across torque + boost code.
- The min-against-ceiling-cals chain (§3b) is the structural link to the boost limit.

**Inferred (standard ME7 semantics + A2L name set rlsol_w/milsol_w/mibas_w/
drlsol_w/rlmax_w, all present in `1xEbvsde.a2l`):**
- Variable *names* (rlsol, drlsol, milsol, rl_w) assigned to the confirmed RAM cells.
- That `sub_4E6F6` region backs the KFPED driver-request path (the raw KFPED
  2-D interp is a word-path lookup; `sub_4E6F6` itself is the channel selection
  helper, not the interpolation).
- That the specific ceiling words in §3b are the KFLDRX/KFLDIMX-derived `rlmax`.

**Open / next:**
- Pin the exact KFPED 2-D interpolation call site (word-map reader keyed on
  processed-pedal + rpm) and the RAM cell holding requested torque `mibas_w`.
- Trace `word_31E484` (rlsol) forward into `sub_DBB04`'s setpoint input to close
  the loop end-to-end in the listing (currently inferred via shared `word_F410`).
