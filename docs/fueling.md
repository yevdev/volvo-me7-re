# Volvo ME7 (50GPHJ) — Fueling / Lambda algorithm (reversed from code)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The fuelling and lambda path, traced through the C166 disassembly of the stock 50GPHJ firmware
(Infineon C167CR / C166). Code analyzed in IDA on the private DB `<work>\me7_stock_fuel.i64`
(code byte-identical across calibration revisions). Disassembly dumps:
`<work>\dump_fuel.txt` (sub_894C0, sub_8981C, sub_775C8, sub_86318) and
`<work>\dump_fuel2.txt` (sub_41A68, sub_42CF4, sub_419F4, sub_42C1C, sub_43904).

Map identities confirmed against `reference/.../TunerPro/more/50GPHJ.xdf`:
- **LAMFA** "Driver requested Lambda" — z-data @ `0x2383E` (byte), x=RPM @ `0x23822`,
  y=%pedal @ `0x23832`. z scale `×0.0078130` (= 1/128). (XDF table 0x17)
- **KFLBTS** "Lambda target value for component protection" — z-data @ `0x19B5A` (byte),
  scale `×0.001`. (XDF table 0x15 / 0x2EF)
- Lambda word scale used internally ≈ `0.0078125/count` (1/128), 0x8000 = neutral/“1.0” bias.

> Legend: **[C]** = confirmed from disassembly; **[I]** = inferred / interpretation.

---

## 0. The lookup primitives (how a map read works)

**`sub_41A68(r12=offset, r13=page, r14=input) → r4`** — universal **word** 2-D/1-D
interpolating table lookup. **[C]** (0x41A68):
- Reads the descriptor at `(page<<14)|offset`: first byte = column count; walks the
  axis breakpoint array with `cmp r10,[r2]` until it brackets the input; computes the
  fractional numerator `r4 = input − axis[i]` and denominator `r5 = axis[i+1] − axis[i]`.
- Indexes into the z-array, then linearly interpolates:
  `result = z[i] ± ((z[i+1]−z[i]) * frac) / span` via `mulu`/`divlu` (MDH:MDL). Handles
  both rising and falling segments (the `cc_UGT` branch at 0x41AC2).

**`sub_419F4(...)`** — the **byte** variant of the same interpolation (`movb`/`movbz`,
`divu` instead of `divlu`). **[C]** (0x419F4). This is the “byte/1-D lookup variant”
that the findings doc listed as an open task. Used by the component-protection path
(sub_86318 calls it at 0x868B6, 0x86950, 0x869DC, 0x86A68) and inside sub_8981C (0x89926).

Helper arithmetic used in the fueling path:
- **`sub_42CF4(r12,r13,r14)`** — interpolation/blend: `r13<<=8`, compares to `r14`,
  returns a value scaled between `r14` and a `r12·Δ` term. Used to pre-condition the
  LAMFA pedal axis input. **[C]**
- **`sub_42C1C(r12,r13,r14)`** = `(r12*r13)/r14` saturating to 0xFFFF (`mulu`+`divlu`). **[C]**
- **`sub_43904(r12=gain,r13=in,r14:r15=state32) → r4:r5`** — **PT1 / first-order lag
  filter** (rate-limited integrator toward `in` with step `gain·(in−state)`), 32-bit state.
  This is the same filter used by the boost controller. **[C]**
- **`sub_42F16` / `sub_42DF4`** — slew/ramp limiters (rate limit toward a target with a
  32-bit accumulator), used in sub_86318’s temperature-protection state filtering. **[I]**

---

## 1. Driver-requested lambda — `sub_894C0` (LAMFA path)  **[C]**

This is the function that produces the **driver/base commanded lambda** from the LAMFA
family. Located 0x894C0–0x895B8.

1. **Pedal-axis conditioning** (0x894C4–0x894F4): selects a pedal/throttle source
   (`byte_304760` shifted <<8, or a stored `word_30299A`), and when the gate
   `word_FD7A.15` is clear, blends it through **`sub_42CF4`** against calibration
   `word_2381C` → stored back to `word_30299A`. The high byte becomes `byte_3047A8`. **[C]**
2. **First LAMFA-family lookup** (0x89500–0x89512):
   `r12=#37FA, r13=#8, r14=byte_3047A8` → `sub_41A68` → `word_305268`.
   phys `0x237FA`. **[C]**  (matches `lookup_callers.txt` line 0x237FA / sub_894C0)
3. **A second small map** via `sub_42464` using `byte_2380C` (page 8) → `word_3029A6`. **[C/I]**
4. **Main LAMFA lookup** (0x89542–0x89556):
   `r12=#37E4, r13=#8, r14=byte_304E27` → `sub_41A68` → **`word_3029A4`**.
   phys `0x237E4`. **[C]** This is the principal driver-requested-lambda map read
   (`lookup_callers.txt` 0x237E4 / sub_894C0). **`byte_304E27` is the load/index axis
   input** (engine-load class), the pedal value is the other axis. **[I]**
5. **Reciprocal / scaling** (0x8955A–0x895B2): builds a 32-bit numerator from
   `word_302986`, divides (`divlu`) by either `word_1655E` or `word_1655C`
   (calibration, selected by `word_FD4A.0`), clamps to 0xFF, stores `byte_3047A9`. **[I]**
   This converts the lambda/load term into a byte-scaled factor for downstream use.

**Outputs of sub_894C0:** `word_3029A4` (LAMFA value), `word_305268`, `word_3029A6`,
`byte_3047A8`, `byte_3047A9` — consumed by sub_8981C. **[C]**

---

## 2. Lambda → fuel correction & the integrator — `sub_8981C`  **[C]**

Called by `sub_B81C` (0x0B918). Located 0x8981C–0x89A74. This assembles the **commanded
lambda correction** and folds in the LAMFA result, closed-loop trim, and final scaling
that flows toward injection.

Key steps:
1. **Load-term select** (0x89820–0x8986E): bit `EFFBM` (cal @0x19C37) picks one of two
   measured-load sources (`word_237F4` cal × `byte_3014EE`, or `loc_F476` × `byte_3014EE`),
   doubled and saturated → `r9`. **[C]** (`word_237F4` is a LAMFA-region calibration.)
2. **Lambda error** (0x8986E–0x8988E): `word_30561E − r9`, saturated to ±range,
   arithmetic-shifted, stored `word_305258`. **[I]** (closed-loop lambda deviation term)
3. **Closed-loop integrator** (0x89892–0x898C8): if cal bit `byte_19C36` set, runs the
   **PT1 filter `sub_43904`** with gain `word_2381E` over state `word_3029A0/3029A2`
   → updated lambda trim `r8`. Otherwise uses static `word_302E38`. **[C]**
4. **Enable/threshold gating** (0x898C8–0x8998C): compares load/temperature against cals
   `word_237F6`, `word_237F8`, byte cals `byte_19C34/19C33`; in the enabled branch does a
   byte lookup `sub_419F4` (cal @0x1C3A, page 6, input `byte_304E27`) and several
   `sub_42C1C` ratio scalings (constants `#3E8`/`#138` = 1000/312, `word_23556`). **[C/I]**
5. **Combine** (0x8998C–0x899A0): `r8 −= (r9>>3)`, saturate → `word_30297A`
   (the corrected lambda/fuel factor). **[C]**
6. **Additive offsets** (0x899A4–0x899E6): adds `word_3029A6 + word_305268` (from sub_894C0)
   and a `sub_42486` map term (cal `word_237CA`, page 8) → `word_302998`, saturating. **[C]**
7. **Final multiply chain (toward injection)** (0x899EA–0x89A4C):
   - `r9 = word_3029A4` (the **LAMFA** value from sub_894C0)
   - multiply by a `sub_42486` map term (`word_2379C`, page 8) using `word_30297A`,
   - `mulu r4,r9` → take high word ×2 (Q15 fixed-point), saturate,
   - multiply by calibration `word_237F2` (LAMFA-region) → **`word_30525C`**. **[C]**
8. **Final fuel-factor lookup** (0x89A50–0x89A6A): `sub_41CC0` with cal `#3558` (page 8),
   axis input `byte_F40E` (**rpm-class index** = nmot/0xA0, not coolant — see ram-names.md) and `word_302984` → **`word_30297C`**. **[C]**

**`word_30297C` is the commanded fuel/lambda multiplier that feeds the injection-time
accumulation** (consumed by sub_775C8). **[C]**

---

## 3. Lambda target → injection time — `sub_775C8`  **[C]**

Called from 0x0B338. Located 0x775C8–0x7763C. This is the **rk → injection-time
accumulation** step (XDF category 0x9 “RKTI – Calculation of Injection Time from Relative
Fuel Mass rk”).

1. Gated by `word_FD22.7`. **[C]**
2. `r4 = word_30297C` (commanded fuel multiplier from sub_8981C) ×
   `r5 = word_302968` (base relative fuel mass rk / load) via `mulu`, take high word ×2
   (Q15), saturate → `r14`. **[C]**
3. Signed-add into a running cylinder fuel accumulator `word_302A14` (with under/overflow
   clamp to 0 / 0xFFFF) → `r15`. **[C]**
4. Multiply by calibration `word_237F2` (same LAMFA-region scale constant as sub_8981C),
   rescale (`>>9` / `<<7` recombine), saturate → **`word_3028BA`** and accumulate into the
   32-bit injector quantity `word_30069C:word_30069E`. **[C]**

So the lambda target modulates relative fuel mass rk, which is summed into the injector
pulse-width accumulator. **[C]**

---

## 4. Component-protection lambda enrichment — `sub_86318` (KFLBTS / LAMBTS)  **[C/I]**

Located 0x86318–0x875B4. This is the **component-protection (over-temperature)
enrichment** subsystem — XDF categories `[LAMBTS] 2.120 (Lambda for component Protection)`
and KFLBTS. It is large because it is a multi-sensor temperature state machine that
arms enrichment when measured temperatures exceed thresholds and then PT1-filters /
slew-limits the enrichment lambda.

What it does (high level):
1. **Threshold/arming logic** (0x86320–0x86540): compares `byte_F473`/`loc_F474` (load family)
   and the rpm-class index `byte_F40E` against many page-6 byte cals
   (`0x19A82–0x19A98`: DTMPTA, TCFL, TUMDMN/TUMDMX, ANTISCAN_MAX, FRARAWG, etc.) and
   page-8 word cals (`0x2348E–0x23496`), setting/clearing protection-request flag bits in
   `byte_30479A/B/C`. **[C]** Per-cylinder debounce counters at `0x876E–0x8771` increment
   against limits `byte_19A94..19A98` (0x866A6 onward). **[C]**
2. **Per-cylinder enrichment via byte lookup** (0x86858, 0x868F2, 0x8698C, 0x86A18): runs
   the **byte-map lookup `sub_419F4`** (cals @ `0x1A4E/0x1A5B/0x1A68/0x1A75`, page 6) and
   PT1-filters with `sub_43904` per cylinder, writing `byte_30A0BE..C1`. **[C]**  *Note:
   in this calibration the KFLBTS z-table @0x19B5A is referenced via the protection
   limit/lookup descriptors in this page-6 cal block; the literal `0x19B5A` does not appear
   as a direct operand because the lookup receives the descriptor offset, not the z address.* **[I]**
3. **Enrichment lambda formation + clamp** (0x86A76–end): computes a lambda-deviation
   `word_305212` (from `word_302816 − 0x8000`), then for each protection channel ramps a
   filtered enrichment value (`sub_42F16` / `sub_42DF4` slew limiters, gain cals
   `0x23440/0x23426/0x2345A/0x23474`, page 8) between calibratable lower/upper bounds
   (`0x23412–0x234AC` block) and stores the channel lambda targets
   `word_30521A / word_305216 / word_30521E / word_305222`. **[C]**

The enrichment lambda is bounded and rate-limited, not directly added to the injector
accumulator here; it feeds the component-protection lambda target that the main lambda
selector uses. **[I]**

---

## 5. The “take the richer lambda” (MIN) decision  **[C]**

The richer-of-two arbitration is implemented as repeated **clamp blocks** in `sub_86318`,
where each protection channel’s computed lambda is clamped between a lower bound `r9` and
upper bound `r8` derived from calibration before being committed. The decisive
clamp pattern (e.g. 0x87282–0x872C4 and 0x8753C–0x8757E) is:

```
  r6 = filtered_channel_value >> 3      ; candidate enrichment lambda
  cmp r6, r9 (upper-rich limit)
    if r6 <= r9: commit r9   (clamp to richest allowed)   ; loc 0x8728C / 0x87546
  cmp r6, r8 (lean limit)
    if r6 >= r8: commit r8   (clamp to leanest allowed)   ; loc 0x872A6 / 0x8755C
  else: commit r6
  -> word_30521E / word_305222   (committed protection lambda)
```

i.e. the protection lambda is **bounded to the richer/leaner calibratable envelope**, so
component protection can only pull the mixture **richer** (toward smaller lambda) up to a
hard limit. **[C]**

The actual **min(driver-request, component-protection)** “take the richer (numerically
smaller) lambda” selection — choosing the richer of LAMFA (sub_894C0/sub_8981C) vs KFLBTS
(sub_86318) — is performed where both targets meet: the lambda-deviation/select stores
flow through the shared cells `word_305212` (deviation) and the `word_3052xx` protection
targets, and the lower (richer) value wins via the saturating-subtract/compare blocks
(`sub r8,#8000h; cc_C/cc_N` saturation at 0x86540, 0x86C76, 0x86F10, 0x87460). **[I —
the arbitration is distributed across these clamp/saturate compares rather than a single
explicit `min` opcode.]**

> NOTE / CORRECTION to the task premise: the literal address `0x19B5A` (KFLBTS z) is **not**
> a direct operand in `sub_86318`; KFLBTS is reached through the page-6 protection-lookup
> descriptors via the **byte** lookup `sub_419F4` (not `sub_41A68`). The byte-lookup
> identification (`sub_419F4`) is the key new finding here. **[C]**

---

## 6. End-to-end data flow (summary)

```
 pedal/throttle (byte_304760)                 engine load class (byte_304E27)
        │  sub_42CF4 condition                         │
        ▼                                              ▼
   LAMFA lookup @0x237FA  ──► word_305268     LAMFA lookup @0x237E4 ──► word_3029A4
   (sub_894C0, sub_41A68)                     (driver-requested lambda, z@0x2383E ×1/128)
        └───────────────┬──────────────────────────────┘
                        ▼  sub_8981C
   measured lambda/load (word_237F4·byte_3014EE) ─► error vs word_30561E
   closed-loop PT1 trim (sub_43904, gain word_2381E)         component-protection:
   + offsets (word_3029A6, word_305268)                       sub_86318  (KFLBTS @0x19B5A,
   × LAMFA (word_3029A4) × cals (word_2379C, word_237F2)      byte lookup sub_419F4,
        ▼                                                     PT1 sub_43904, slew sub_42F16/
   word_30297C  (commanded fuel/lambda multiplier)            42DF4) → word_30521A/16/1E/22
        │                                                     (richer-clamped enrichment λ)
        ▼  sub_775C8  (RKTI)
   word_30297C × rk(word_302968) → accumulate into
   injector quantity word_30069C:word_30069E  ──► injection time
```

`min`/“richer wins” lives in the saturating compare-and-clamp blocks of `sub_86318`
(§5); the LAMFA driver request is the baseline that component protection can only enrich.

---

## 7. Long-term lambda adaptation (learned fuel trim, LRA) — `sub_88540` (+ boot restore `sub_884E8`)  **[C]**

`sub_8981C` (§2) is the *instantaneous* closed-loop trim (`fr_w` @ `word_3029A0:A2`) — volatile,
per-drive. `sub_88540` (0x88540–0x88CC6) is the **slow learned adaptation** layered on top: it
time-integrates that controller's output into a persistent trim that survives key-off, so the engine
starts pre-corrected. Reached via scheduled/indirect dispatch (through trampoline `sub_88CC6`). **[C]**

- **Learn** — two cascaded PT1 integrators (`sub_43904`): state `word_302972:74` → output
  **`word_30523E`** (the learned trim), then a slower second stage `word_302976:78`. **[C]**
- **Persist / restore** — the trim is stored to **`word_30A18A` on page 0xC2** (the battery-backed
  segment, same page as the LDR adaptive trim) at 0x88890, and **restored into the integrator at
  power-on** by `sub_884E8` (0x884E8–0x88540), which wipes it when `word_FD4E.8` (clear-adaptation) is set. **[C]**
- **Gating** — partitioned by an operating-point index `byte_3015D8` (= `word_3029C6 / 0xA0`); each
  region waits out a debounce reloaded from cal **`EFFASK07` (`0x19C2D`)** into counters `byte_3015CB..CE`,
  and only learns inside the load/rpm window in cal block `0x23528–0x23540` (`center±delta` vs `word_305240`).
  Enable bits `byte_19C2E`; frozen outside closed-loop via `word_3035F8.15` / `word_FD3A.9`; deviation
  clamped ±0x7FFF, output clamped to `word_2352C`. **[C]**

```
  0x88668  calls 4, sub_43904        ; PT1 learn: state += gain*(fr_target - state)
  0x88684  mov   word_30523E, r8     ; <- learned trim (integrator-A output)
  0x88890  mov   word_30A18A, r8     ; <- persist to page-0xC2 (survives key-off)
  ; --- boot restore (sub_884E8) ---
  0x884F8  mov   r12, word_30A18A    ; read persisted trim
  0x88504  mov   word_302974, r13    ; seed integrator state
  0x8850C  movb  rl1, EFFASK07       ; CAL->0x19c2d   reload region debounce
```

**Control vs adaptation:** the documented fuel path (`sub_894C0` / `sub_8981C` / `sub_775C8`) references
**none** of the adaptation cells — the two share the `fr` *input* but not state. **Open [I]:** the exact
site where the learned trim re-enters injection isn't proven — `word_30523E` is read only by a diagnostic
accessor and a secondary smoothing filter in the functions examined; it most likely biases the fast
controller's baseline upstream rather than multiplying `ti` directly. Next: trace consumers of
`word_30524C` / `word_302976:78`.

## 8. Evaporative-emissions canister purge (TEV) — `sub_8DE10`  **[C]**

`sub_8DE10` (0x8DE10–0x8F050) is the **EVAP / tank-vent (Tankentlüftung, TEV) purge controller** — *not*
the ignition-efficiency/dwell function its IDA auto-label `EFFSF13T` suggested; that label is the
disassembler's name for **`FSRFKAS`** (the purge fuel-portion factor) at `0x19DF4`. Every cal it touches
decodes to a purge / mass-flow / HC-concentration object (`DMSTES`, `KAKFAD`, `DFTEVFLO`, `FSRFKAS`,
`KHCTEM*`, `TFTEINI`); it touches no ignition/dwell cal. Dispatched via the process table
(`callers=0`, full frame). **[C]**

- From a manifold/throttle **pressure ratio** (`divlu` on `word_30294C`/`word_302822` at 0x8DE2C) it
  derives the purge driving signal, scales it through purge mass-flow + HC-concentration maps, runs
  several PI/PT1 integrators (`sub_430DA`/`sub_438F6`/`sub_43904`), and emits the **purge-valve duty** to
  `byte_30A0C2/C3/C4` (page 0xC2). **[C]**
- In parallel it computes the **purge fuel-portion correction** `byte_304949` via `FSRFKAS` — the term
  the fuel path uses to discount injected fuel for vapour drawn from the canister:

```
0x8E180  movb  rl6, EFFSF13T      ; CAL->0x19df4  (= FSRFKAS, purge fuel-portion)
0x8E186  mul   r9, r6             ; delta * FSRFKAS
0x8E1A2  ashr  r8, #6             ; >> 6 (saturating)
0x8E1C0  movb  byte_304949, rl6   ; -> purge fuel-correction byte (page 0xC1)
```

It does not touch the ignition or torque paths — its only coupling to the documented core is this fuel
correction. **Open [I]:** the upstream `word_302E0x` flow inputs (from `sub_D89CC`) and the consumer of the
`byte_30A0C2` duty (assumed the PWM/CAN valve driver) aren't traced end to end. Cals, I/O cells, and the
integrator topology are **[C]**.

## 9. O2-sensor diagnostics (readiness / plausibility) — `sub_A5A9E`  *(not a control path)*

`sub_A5A9E` (0xA5A9E–0xA7CEC, scheduled via trampoline `sub_A7CEC`, gated on `word_3018D8 & 4`) is the
**OBD exhaust-sensor monitor** ("Diagnose Abgas-Sonde" — cals `INHASE02` 0x1A15F / `INHASE04` 0x1A187 /
`INHASE05` 0x1A19B). It is **pure diagnostics, not control**: across its whole body there are **zero**
multiply/divide ops and **zero** lookup-table calls — it only debounces per-monitor results
(`sub_32E88`/`sub_32EBE`), queries fault memory (`sub_BC6C6`), and commits readiness/status bitfields to
the battery-backed page-0xC2 words `word_30A24E/30A250/30A252` + `byte_30A0E4/E5`. **[C]**

It does **not** feed the lambda controller or its adaptation (none of `sub_8981C`/`sub_88540`'s cells are
written here); its only coupling is *reading* the closed-loop-active bit `word_3035F8.15` (§7) to validate
results. The actual **O2 signal conditioning and heater duty live in sibling functions** (candidates
`sub_90000`/`sub_90232`, `sub_A40D6` — they share the `0x1A19x` cal block), **not** here — a useful scope
boundary: this is where readiness/DTCs are set, not where mixture is controlled. **[C]** non-coupling; **[I]** sibling identities.

## 10. Cranking & after-start enrichment (Start / Nachstart)  **[C]**

The cold-start fuel path, feeding the rk → injection chain (§3). Three stages:

- **Start-state machine — `sub_D22B6`:** sets `word_FD7A.14` (cranking) / `word_FD7A.15` (after-start /
  running) by comparing the rpm-class index `byte_F40E` against page-0xD threshold maps `0x4764`/`0x476B`,
  and counts the **after-start timer `word_302D70`** up while running. **[C]**
- **Cranking quantity — `sub_7040C`** (0x7040C–0x70716): gated by `word_FD7A.14` + config byte `byte_1BE74`,
  reads the **start-quantity map `0x21282` indexed by load byte `byte_F473` × rpm `byte_F40E`** (cold = more
  fuel), applies battery-voltage/correction terms → `word_30A178` (battery-backed) → `loc_F35C` → `word_30280E`. **[C]**
- **After-start decay — `sub_7157A`** (0x7157A–0x715D2): a 2-D map `0x5F0A`/`0x5F10` indexed by the
  **after-start timer `word_302D70` × rpm-class `byte_30163A`** → `word_302812`, so the enrichment **decays
  as the timer counts up**. `sub_717F0`/`sub_724E2` arbitrate it (min vs accumulated `word_302818`, cap `0x15F04`)
  into the factor `word_30281A`. **[C]**

```
0x7046C  movbz r15, byte_F473        ; load byte = rl>>5 (NOT coolant; see ram-names.md)
0x70470  calls 4, sub_41BD4          ; cranking-quantity map @0x21282 (coolant x rpm)
0x7159C  mov   r4, word_302D70       ; after-start timer = the decay axis
0x715BE  calls 4, sub_415B0          ; after-start decay map @0x5F0A -> word_302812
; --- folded into rk in sub_875D4 ---
0x87708  mov   r4, word_30281A       ; arbitrated start/after-start enrichment factor
0x8770C  mulu  r13, r4               ; x rk (Q15)
0x87788  mov   word_302968, r4       ; -> rk_w, consumed by sub_775C8 (RKTI, §3)
```

So cranking/after-start enrichment **scales rk multiplicatively** (`sub_875D4`), then rides the normal RKTI
injection path (§3) — not a separate `ti` adder.

> **Note:** the `FST*` start cals (`FSTTAL`/`FSTTEW`/`FSTDMN`/`FSTDMX`/`DLAMOB`) are read only by the idle
> cluster (`sub_7D58E` et al.) and configure the idle/start *torque reserve* ([idle-governor.md](idle-governor.md)),
> **not** this cranking fuel. And `byte_F40E` here is the rpm-class index, **not** coolant — the coolant cell
> is **not** `byte_F473` — that's the load byte (`rl>>5`); the real coolant cell isn't pinned (see [ram-names.md](ram-names.md)). **[C]**

**Open:** map names are positional (`0x21282` cranking-qty, `0x5F0A` after-start decay — no DB names on this
band); `byte_1BE74` per-bit config and the accumulated term `word_302818` are **[I]**.

## Confirmed vs inferred — ledger

| Item | Status |
|---|---|
| LAMFA read by sub_894C0 @0x237E4 (input byte_304E27) and @0x237FA | **[C]** |
| LAMFA z@0x2383E, axes 0x23822(RPM)/0x23832(%pedal), scale 1/128 | **[C]** (XDF + code) |
| `sub_41A68` = word interp lookup; `sub_419F4` = **byte** interp lookup | **[C]** |
| `sub_43904` = PT1/integrator; `sub_42C1C` = saturating mul/div | **[C]** |
| sub_8981C builds commanded fuel multiplier word_30297C, with closed-loop PT1 trim | **[C]** |
| sub_775C8 multiplies word_30297C × rk into injector accumulator (RKTI) | **[C]** |
| KFLBTS/component-protection in sub_86318 via byte lookup sub_419F4, PT1+slew filtered | **[C]** for mechanism; **[I]** for exact map-descriptor→0x19B5A binding |
| “richer wins” = distributed clamp/saturate compares (not one min opcode) | **[I]** |
| Closed-loop lambda error/trim cells (word_305258, word_30561E) exact physical meaning | **[I]** |
| Long-term adaptation sub_88540: cascaded PT1 → persistent trim word_30A18A (page 0xC2), restored by sub_884E8 (§7) | **[C]**; apply-to-injection site **[I/open]** |
```
