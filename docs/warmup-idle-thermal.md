# Volvo ME7.0 (50GPHJ) — warm-up, thermal protection & idle-ignition coordination

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The second-pass subsystems — the code that runs while the engine warms up, the thermal models that
guard the cat and exhaust, and the idle/startup spark reserve. Same method as the core docs: read
off the stock 50GPHJ disassembly (Infineon C167CR), addresses cited, `[C]`/`[I]` as before. All three
are live — two are scheduled directly by the main periodic task `sub_B81C`, one is dispatched through
the RTOS process table — and none sit in tuner-hack regions.

Legend: **[C]** = read directly from the disassembly; **[I]** = inferred from structure / ME7 convention.

---

## 1. Catalyst-heating / warm-up coordinator — `sub_52D16`  (FWM / KAT)

- **Entry:** `sub_52D16` (`0x52D16–0x5360A`), scheduled directly by `sub_B81C` (`callers=1`). **[C]**
- **Touch-points:** 39 calibration refs, 66 RAM refs. Callees: `sub_418DA` (slew/ramp), `sub_419F4`
  (byte lookup), `sub_4210C`/`sub_42CF4` (interp / fraction blend). **[C]**
- **Named calibration cells** (page-6 cat-heat block, named in the dump): `FWMKATR` `0x184BF`,
  `FWMKATW` `0x184C0`, `FWMZAPWF` `0x184C1`, `IMTUMTAT` `0x184C3`, `KFATMLA` `0x184C4`. **[C]**
- **RAM written:** `byte_30133D` (cat-heat active flag), `byte_30133E` (phase bits), the slewed working
  value `word_3024C4`. These sit immediately next to the ignition base-advance cell `byte_30132E`. **[C]**

It arms phase bits by comparing measured temperatures and RPM-class against the warm-up cals, slews a
working value toward the new request (`sub_418DA`), then bounds it through a cascade of min-clamps against
the FWM/KFAT limits:

```
0x53160  cmpb    rl6, IMTUMTAT  ; CAL->0x184c3
0x53164  jmpr    cc_NC, loc_5316E
0x5316A  movb    rl6, IMTUMTAT      ; clamp to IMTUMTAT
 ...
0x53220  cmpb    rl6, FWMKATW   ; CAL->0x184c0   (gated by an engine-state flag)
0x5322A  movb    rl6, FWMKATW       ; clamp to FWMKATW
```

**What it does:** the Bosch ME7 catalyst-heating / warm-up coordinator (`FWM` = warm-up mode, `KAT` =
catalyst). From coolant/exhaust temperatures, RPM-class and engine-state flags it picks the warm-up /
cat-light-off phase, computes a phase-dependent working value bounded by the warm-up limit cals, and
publishes the mode in `byte_30133D/3E` **[C]**. The downstream effect — the idle-up and the
cat-heating spark retard that lives next to `byte_30132E` — is **[I]**, but strongly supported by the
adjacency and the named cals.

---

## 2. Thermal / component-protection temperature model — `sub_64C80`

- **Entry:** `sub_64C80` (`0x64C80–0x65DA6`). `callers=0` in the CSV/callgraph → dispatched via the
  process table, not dead code (full prologue/epilogue, 88 RAM refs). **[C]** structure; **[I]** dispatch.
- **Touch-points:** 33 calibration refs, 88 RAM refs. Callees: **six** `sub_43904` PT1 integrators,
  `sub_41CC0` (2-D bilinear word map), `sub_41BD4` (2-D byte map), plus interp helpers. **[C]**
- **Inputs:** `byte_F40E` (rpm-class index = nmot/0xA0, **not** coolant — see
  [`ram-names.md`](ram-names.md)), `byte_F473` (the load byte = `rl>>5`, **not** a temperature — see [`ram-names.md`](ram-names.md)), `word_F410` (nmot). **[C]**
- **RAM:** six independent 32-bit PT1 states in the page-0xC1 block `word_304F84…9E`; smoothed outputs
  `byte_304711…304F1D` and `word_304F78`. **[C]**

```
0x64C9C  mov   r12, #980h          ; r13=#6  (page-6 byte map)
0x64CA4  movbz r14, byte_F40E      ; rpm-class idx (= nmot/0xA0, NOT coolant)
0x64CAC  calls 4, sub_41BD4        ; 2-D byte map
0x64CC8  calls 4, sub_41CC0        ; 2-D bilinear word map (nmot-indexed)
 ...
0x651B0  calls 4, sub_43904        ; PT1 step: state += gain*(in - state)
```

**What it does:** a multi-channel thermal model — it reads temperature/operating-point maps keyed on an
rpm-class index `byte_F40E` (= nmot/0xA0), the load byte `byte_F473` and engine speed `word_F410`, then runs **six
parallel PT1 lag filters** to produce smoothed temperature/quantity estimates **[C]**. The temperature-map + multi-filter shape is a calibrated
multi-channel **thermal estimator**; the exact modelled quantity (component-metal vs charge vs a
coolant-derived temp) is **[I]**. **Correction (see §4):** despite the shape, its smoothed outputs do
**not** feed the `KFLBTS` component-protection enrichment — that path (`sub_86318`) is gated on *raw*
conditioned temps, and this image has no `TABGBTS`/`tabgbts_w`. The consumer of `sub_64C80`'s outputs is
**not yet established** — treat it as a thermal estimator of unconfirmed downstream use.

---

## 3. Idle / startup spark reserve & knock-window — `sub_53DEC`

- **Entry:** `sub_53DEC` (`0x53DEC–0x54728`), scheduled directly by `sub_B81C` (`callers=1`). **[C]**
- **Touch-points:** 26 calibration refs, 71 RAM refs. Callees: `sub_42544` (dual-map interp),
  `sub_438F6`/`sub_43904` (integrators), several 1-D interp helpers. **[C]**
- **Gating inputs:** knock-window flags `word_FD46.10/.15`, cat-heat mode `byte_30133D` (shared with §1),
  enable bits `byte_1863D`. **[C]**
- **RAM written:** the spark reserve/limit byte `byte_301360` + debounce counters `byte_301361…364`, on
  the same `word_3024xx` ignition working band the ignition mode-limiter `sub_50ED2` uses. **[C]**

```
0x53DF6  movbz r9, byte_1863D       ; CAL->0x1863d  (enable bits)
0x53DFE  jnb   word_FD46.10, loc_53E0A   ; knock-window flag
0x53E0E  jnb   word_FD46.15, loc_53E16   ; 2nd knock-window flag
0x53E1E  movbs r6, byte_30133D      ; cat-heat mode (shared with sub_52D16)
0x53E54  calls 4, sub_42544         ; dual-map interpolation
0x53E5C  movb  byte_301360, rl4     ; -> spark reserve / limit byte
```

**What it does:** runs inside the ignition cluster (`0x53xxx`, between the documented `sub_518B8` /
`sub_50ED2` / `sub_5172C`) on the ignition working band. Gated by the knock-detection windows and the
cat-heat mode, it reads page-4 ignition/knock cals (`0x137xx`, next to the documented knock set
`0x139B6–0x139BD`) and produces a reserve/limit byte plus debounced state counters **[C]**. This is the
**idle / startup spark-reserve and knock-window coordination** — the routine that arms the knock window
and manages the spark torque-reserve idle-speed control and cold-start lean on. The precise label
(idle-reserve vs startup-window enable) is **[I]**; the gating inputs, ignition-band cals and outputs are **[C]**.

> §1 and §3 both read/write `byte_30133D` — a coupled **warm-up / cat-heat / idle-ignition** control
> group, though they remain distinct functions (mode coordinator vs ignition-band reserve).

---

## 4. Exhaust-gas-temperature (EGT) sensor model — `sub_945C2` (+ sibling `sub_93F2C`)  **[C]**

`sub_945C2` (0x945C2–0x9650C) is the EGT sensor model + diagnostics — pinned by its `EXA*` ("Abgas" =
exhaust) cal family: `EXATEST` 0x19FE3, `EXATESK` 0x19FCF, `EXAFRAU` 0x19F43, `EXAFRAO` 0x19F2F. Scheduled
via wrapper `sub_965E4` + input-latch `sub_9667E` off the sequential task list `sub_B6E6`. `sub_93F2C` is
the near-identical second sensor channel. **[C]**

- **Model (0x945C2–0x95064):** the raw EGT-sensor ADC (`word_301948`→`word_302AC0`) is interpolated
  (`sub_41A68`) through maps `0x23C82`/`0x23CD4`, blended with charge-axis maps `0x23B60`/`0x23C74`, and
  filtered (`sub_42CF4`) → filtered EGT `word_302ACE` + published byte `byte_30163A` / `byte_304974`. **[C]**
- **Diagnostics (after 0x95064):** debounce counters + fault bitfields `byte_301636…48` gated by the `EXA*`
  cals; a telemetry tail packs two CAN signals (`sub_B31AC`). **[C]**
- **Consumer:** the modelled EGT (`byte_304974`) feeds **`sub_8C636`**, which thresholds it against
  **`EFFMFA2` (`0x19D95`)**, sets an overheat flag `byte_3007DD`, and emits a scaled term `word_3007E2`; it
  also feeds the warm-up coordinator (§1) and a gauge/CAN conversion. **[C]**

```
0x8C668  movbz r5, byte_304974     ; (in sub_8C636) modelled EGT byte
0x8C864  orb   byte_3007DD, rl4    ; set overheat flag
0x8C970  mov   word_3007E2, r4     ; scaled over-temp term
```

**Component-protection link — refuted [C].** The S4/ME7.1 pattern "`KFLBTS` gates on a calculated EGT
(`tabgbts_w > TABGBTS`)" does **not** hold here: `sub_86318` (fueling.md §4) reads only *raw* conditioned
inputs (`byte_F473`/`loc_F474` load + the rpm-class `byte_F40E`, 10 refs) and **zero** EGT/thermal-model outputs, and there is
**no `TABGBTS` symbol** in this image. Component-protection enrichment is temperature-sensor-gated, not
EGT-model-gated; the §2 thermal model doesn't feed it either.

**Open:** whether `sub_8C636`'s over-temp term (`word_3007E2`/`byte_3007DD`) ultimately biases enrichment
or pulls timing/load (the next trace); and the consumer of the §2 `sub_64C80` outputs.

## 5. Backlog — candidates not yet traced

High calibration/RAM touch-count functions that look like control or protection logic but whose
algorithm has not yet been worked out. Counts are from [`../data/xref/functions.csv`](../data/xref/functions.csv);
the role column is **[I]** (a starting guess from cal names + call shape), not a result.

| Function | cal | ram | Candidate role (inferred) |
|---|---:|---:|---|
| `sub_945C2` | 69 | 96 | ✅ **done** — EGT sensor model; see §4 |
| `sub_A5A9E` | 47 | 138 | O2 / lambda-sensor monitoring (cals `INHASE02/04/05`); diagnostic-leaning |
| `sub_AC5DE` | 21 | 81 | ✅ **done** — manifold-pressure→charge model (limiter half); see [charge.md](charge.md) |
| `sub_AD3D0` | 10 | 73 | ✅ **done** — manifold-pressure→charge model (estimator); see [charge.md](charge.md) |
| `sub_69F5E` | 13 | 48 | Air/load min-max envelope tracker + PT1 (KFMIRL-adjacent gain) |
| `sub_5369C` | 21 | 43 | Warm-up ignition coordinator (`sub_B81C` callee; reads `byte_30133D`) — §1/§3 sibling |
| `sub_C7EEA` | 35 | 68 | ✅ **done** — throttle-servo stop-learn adaptation (`etc_stop_learn_adapt`); see [etc-throttle.md](etc-throttle.md) |
| `sub_8DE10` | 20 | 111 | ✅ **done** — EVAP canister-purge (TEV) controller, **not** dwell; see [fueling.md §8](fueling.md) |
| `sub_88540` | 16 | 44 | ✅ **done** — long-term lambda adaptation (LRA); see [fueling.md §7](fueling.md) |
| `sub_7CE76` | 9 | 42 | Knock-window / spark sub-state (`sub_B81C` callee; knock flags `word_FD46`) |
| `sub_933BE` | 18 | 31 | Periodic byte-table service (one integrator + one lookup) |

To work one: `idat.exe -A -S"../scripts/ida/ida_dump_func.py out.txt 0x945C2" me7_carve.i64`, then follow
the call tree and the cal/RAM touch-points the same way the core docs were built.
