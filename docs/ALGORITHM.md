# Volvo ME7 (50GPHJ) — the control algorithm, from the code

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

End-to-end synthesis of the C166 reverse engineering (IDA). Every claim here is grounded
in the disassembly; per-subsystem detail + cited instruction addresses are in the companion
docs: [`lookup.md`](lookup.md), [`boost.md`](boost.md), [`ignition.md`](ignition.md), [`fueling.md`](fueling.md), [`torque.md`](torque.md), plus [`ram-names.md`](ram-names.md)
(RAM/CAL cell → engineering name) and [`bytemap_callers.md`](bytemap_callers.md) (byte-map linkage). See
[`methodology.md`](methodology.md) for the toolchain and [`../data/pseudocode/key_functions.c`](../data/pseudocode/key_functions.c) for Ghidra pseudo-C.
Confirmed unless marked (inferred).

---

## Subsystem map (what's been reverse-engineered)

The control path end to end, with the doc + entry function for each subsystem. All read from the stock 50GPHJ code.

**Air & load** — Air/MAF → relative load `rl` ([load-rl.md](load-rl.md): `sub_D2C9A`/`sub_D34DC`, KFURL/KRKTE) · manifold-pressure → charge model ([charge.md](charge.md): `sub_AD3D0`/`sub_AC5DE`)
**Torque** ([torque.md](torque.md)) — pedal→torque (KFPED) · optimum-torque model (KFMIOP `sub_4F4BC`) · coordinator (`sub_4D73A`→`sub_4D86C`) → load setpoint `rlsol` (KFMIRL `sub_4F97A`)
**Boost** — LDR controller ([boost.md](boost.md): `sub_DBB04`/`sub_DBF44`; KFLDIMX/KFLDRX/KFLDRL/KFLDHBN)
**Ignition** ([ignition.md](ignition.md)) — base advance (KFZW `sub_518B8`) · knock (`sub_7BA8C`) · output (`sub_50984`) — and **cam timing/VVT** ([cam-timing.md](cam-timing.md): dual `sub_49DB8`/`sub_4C878`)
**Fuelling** ([fueling.md](fueling.md)) — LAMFA (`sub_894C0`) → controller (`sub_8981C`) → RKTI (`sub_775C8`) · LRA adaptation (`sub_88540`, §7) · component protection (KFLBTS `sub_86318`) · cranking/after-start (`sub_7040C`/`sub_7157A`, §10) · EVAP purge (`sub_8DE10`, §8)
**Idle / warm-up / limits** — idle air governor (LLR, [idle-governor.md](idle-governor.md): `sub_7D58E`) · idle-spark reserve + cat-heating + thermal model ([warmup-idle-thermal.md](warmup-idle-thermal.md)) · rev + ~250 km/h speed limiters ([limiters.md](limiters.md))
**Machinery & names** — [lookup.md](lookup.md) · [map-inventory.md](map-inventory.md) · [ram-names.md](ram-names.md) · [bytemap_callers.md](bytemap_callers.md) · [methodology.md](methodology.md)
**Diagnostics** (monitors, not control) — §7: O2, brake-booster, knock-circuit, rationality, misfire.

**Coverage.** The engine-control surface above is mapped end to end; **no control subsystem is known to be
missing**. Beyond it, five OBD diagnostic monitors are identified (§7). A handful of high-cal-touch functions
remain unidentified (`sub_9A52`, `sub_E018C`, `sub_922B8`, `sub_C7EEA`, `sub_6C6DA`, `sub_9D894`) — their
callee signatures and the run of five-straight-diagnostics above point to the diagnostic/monitoring tail, not
control. The remainder is CAN/KWP2000 comms and leaf/library routines. This is the control algorithm + the
tooling to extend it, **not** a complete annotated image (see [methodology.md](methodology.md) → Coverage).

---

## 0. The lookup family (every map goes through one of these)

| Routine | Type | Used by |
|---|---|---|
| `sub_41A68` | 1-D word, unsigned axis | most word tables (96 callers) |
| `sub_41B5A` | 1-D word, **signed** axis | boost error tables |
| `sub_419F4` | 1-D **byte** | KFLBTS-class byte maps |
| `sub_41CC0` | **2-D bilinear word** | KFLDRL WGDC feed-forward, KF* word maps |
| `sub_411F4` | 2-D bilinear **sbyte** | **KFZW** ignition maps |
| `sub_43430` | 2-D bilinear word (torque) | KFMIOP |

**Map binary layout** (little-endian, axis length = low byte, ≤255 pts, monotonic ascending,
linear/bilinear with floor-division, **end-clamped, no extrapolation, no rounding**):
`[lenX][X pts][lenY][Y pts][Z row-major]`. Helpers `sub_43904` (PT1/integrator
`state += gain·(target−state)`), `sub_42F16`/`sub_42DF4` (clamped integrators) recur everywhere.

---

## 1. Driver demand → torque → load setpoint  (torque.md)

1. **Pedal → requested torque**: KFPED (z=0x1E776) maps pedal × rpm → driver torque request.
   (The KFPED 2-D read is a word-path lookup; `sub_4E6F6` is the pedal channel-select/plausibility helper — inferred.)
2. **Optimum torque model — `sub_4F4BC` (KFMIOP, z=0x156CC)**: looks up optimum indicated
   torque, blends 4 correction sub-maps, applies ignition-efficiency byte corrections, scales
   ×164, and **averages over 5 cylinders** (`divu #5`) — the inline-5 model.
3. **Torque → load setpoint — `sub_4F97A` (KFMIRL, z=0x158A4)**: converts torque demand to a
   relative-charge setpoint with P + integral-MAC terms, PT1-smoothed, output to
   **`word_31E484` = rlsol** (the relative-load request). It is **clamped against a stack of
   ceiling words** (`word_15852/54/56/5A`, slewed `word_31C200`) — *this min-against-ceiling is
   the structural link to the boost limit* (KFLDRX/KFLDIMX).

**Correction (per [`ram-names.md`](ram-names.md)):** `word_F410` = **`nmot_w` (engine speed)**, not `rl` — so the
boost-loop term that uses it is an **rpm-scaled precontrol**, not load feedback. The control
structure is unchanged; only the label. The setpoint/feedback split is rlsol vs measured charge `rl`.

---

## 2. Boost control (LDR)  (boost.md)

Scheduled chain in `sub_B81C`. Core math in **`sub_DBB04`**:
- **Setpoint** `word_302E62` = (load request × gain `0x2BE38`) + KFLDIMX-region map term, clamped.
- **Actual ratio** `word_302E58` = (measured load `word_302496` ≪ 11) / reference `word_30294A` (`divlu`).
- **I-term**: `sub_43904` integrator, gain/limit = **KFLDIMX (`word_2BF32`)**, error clamped ±0x7FFF.
- **P-term**: error × gain (KFLDRX-region map 0x2BE3A), shaped through a signed table.
- **PI sum** + adaptive trim, clamped ±0x3FFF.
- **Feed-forward**: 2-D map (`sub_41CC0`, KFLDRX-region 0x2BECA) indexed by setpoint → base WG duty; PI added on top → `word_302E5E`.
- **KFLDRL linearization**: deviation → map(0x2BEAC) → integrated → final demand `word_302E60`.

**Enable/limit state machine `sub_DBF44`**: gates on the **KFLDIMX threshold `word_2BF4A`**
(margin `word_2BF4C`); anti-windup freezes the integrators on saturation; scales demand into
duty and clamps to **WG-duty MIN `word_2BF4E` / MAX `word_2BF50`**. **`sub_DC31A`**: master
enable `byte_1BE46`, **over-boost RPM trip vs `word_2BF48` (=6000)**, KFLDHBN compressor-ratio
guard (`sub_D5E80` computes the pressure ratio), final solenoid bit `byte_301870.0`.

> This confirms in code why raising **KFLDIMX** extends controller authority (it's the I-limit
> *and* the enable threshold `word_2BF4A`), and why **KFLDRX** sets the ceiling (it clamps rlsol
> in §1 and is the P-gain/feed-forward map source).

---

## 3. Ignition + knock  (ignition.md)

- **Base advance — `sub_518B8`**: KFZW1-4 (z=0x133B1/71/0x13531/0x135F1) via the sbyte bilinear
  `sub_411F4`, on shared RPM/load axes; blends KFZW1·2 and KFZW3·4 by cam-phase fractions
  (`byte_30129C`/`byte_30129B`) → base advance `byte_30132E` (0.75°/count).
- **+ IAT/temp correction** (`sub_7CC7C` → `byte_30157C`).
- **− knock retard — `sub_5086A`**: subtracts **global knock retard `byte_F3FA`** + **per-cylinder
  retard `0x30B24C[cyl]`**. Knock control `sub_7BA8C`/`sub_7BD04`: +cal `0x139B7` per knock event
  (cap `0x139B6`), bleed-back rate `0x139B8`/`0xBA`, gated above RPM-class `0x139BD`. Knock cal
  set = ROM `0x139B6–0x139BD`.
- **Final spark — `sub_50984`**: clamps per cylinder to the output window (≈ −48°..+60°), writes
  the ignition output array at `0x309317`.

> Per-cylinder knock retard is a real subtraction from base advance. There is no hidden timing
> reserve: output = base map − knock retard, per cylinder.

---

## 4. Fueling  (fueling.md)

- **Driver lambda — `sub_894C0`**: LAMFA (z=0x2383E, ×1/128) via `sub_41A68`, indexed by load-class → `word_3029A4`.
- **Lambda → fuel multiplier — `sub_8981C`**: closed-loop PT1 lambda integrator (`sub_43904`,
  gain `word_2381E`) × cal scalers × temp lookup → `word_30297C` (commanded multiplier).
- **Injection — `sub_775C8`**: `word_30297C × charge` → 32-bit injector quantity `word_30069C`.
- **Component protection — `sub_86318` (KFLBTS)**: multi-sensor over-temp state machine; PT1 +
  slew-limited per-cylinder enrichment lambdas. "Take the richer lambda" is **distributed
  clamp/compare blocks** (not one `min`); protection can only pull *richer* than the LAMFA baseline.

---

## 5. Tuning-relevant takeaways (code-confirmed)

- **Boost ceiling is enforced twice**: KFLDRX clamps `rlsol` (§1) *and* sources the P-gain/feed-forward (§2). Raising one without the other is why naive boost edits misbehave.
- **KFLDIMX = I-limit *and* enable threshold** (`word_2BF4A`) — it literally gates whether the controller is allowed to drive the wastegate harder.
- **WG duty is hard-clamped** to `word_2BF4E`/`word_2BF50`, with an **over-boost RPM cut at 6000** (`word_2BF48`).
- **Ignition output = base map − knock retard**, per cylinder — confirming there's no hidden timing reserve beyond the base maps.

## 6. Warm-up, thermal protection & idle ignition  (warmup-idle-thermal.md)

A second pass picked up three more live subsystems beyond the core path, all read off the same stock
image — see [`warmup-idle-thermal.md`](warmup-idle-thermal.md):

- **Catalyst-heating / warm-up coordinator** — `sub_52D16` (scheduled by `sub_B81C`): picks the
  warm-up / cat-light-off phase and bounds a working value against the FWM/KFAT limits (`FWMKATR`
  `0x184BF`, `FWMKATW` `0x184C0`, `KFATMLA` `0x184C4`); publishes the mode in `byte_30133D/3E`, next to
  the ignition base-advance cell.
- **Thermal / component-protection model** — `sub_64C80`: six parallel PT1 filters (`sub_43904`) over
  temperature-indexed maps keyed on coolant `byte_F40E` and nmot `word_F410` → smoothed component/EGT
  estimates feeding over-temp protection.
- **Idle / startup spark reserve & knock-window** — `sub_53DEC` (scheduled by `sub_B81C`): gated by the
  knock windows (`word_FD46.10/.15`) and cat-heat mode (`byte_30133D`); produces the spark reserve/limit
  `byte_301360` on the ignition working band.

## 7. Diagnostics (monitors — identified, not control)

Several of the highest cal-touch functions turned out to be **OBD/diagnostic monitors**: they raise fault
bits/DTCs and compute no actuator or setpoint, so they're identified for completeness but are **not
tuning-relevant**. (That five of the top undocumented functions are diagnostics is the signal the control
surface in §§0–6 is now mapped.)

- **O2 / lambda-sensor monitoring** — `sub_A5A9E` (readiness/plausibility/DTC; cals `INHASE02/04/05`). Pure
  diagnostic; heater + signal conditioning live in siblings `sub_90000`/`sub_A40D6`. → [fueling.md §9](fueling.md).
- **Brake-booster (BKV) vacuum diagnosis** — `sub_724E2` (+ front-end `sub_72C02`): Δp(ambient−manifold)
  staircase → `byte_304753` → fault; cals `0x2169A/9C/9E` "brake booster". → [bytemap_callers.md](bytemap_callers.md).
- **Knock-control-circuit diagnosis** — `sub_39FCA` (+ init `sub_39F24`): knock-sensor channel-balance /
  plausibility; cals `CDKKS1/S2/S3`,`CDKKOSE`,`CDKKPE`,`CDKKRTP` (`0x14EE8–0x14EF8`) → fault bits `word_FD06/FD08`
  + DTC bytes `byte_300108–10A`. Verified: **no spark/actuator write**, no map lookups. **[C]**
- **Sensor/model rationality monitor** — `sub_9A034` (+ cluster `sub_99414`/`sub_9B534`): builds a modelled
  quantity (charge × temp via slew/PT1/clamped integrators), windows it against cal thresholds, and sets
  status/DTC bits (`byte_301667`, counter `word_30530E`). Diagnostic; exact monitored channel **[I]**
  (cal band `0x1A0xx`/`0x23Exx` carries no dictionary names).
- **Running-roughness / misfire detection** (Laufunruhe) — `sub_A0000` (0xA0000–0xA1A4A, ~6.7 KB; + workers
  `sub_9F32E` etc.): a 168-entry per-segment accumulator → min/max **spread** vs limit `0x13ED2`, bucketed
  into an rpm×load cell grid with per-cell learned banks, matured and published to the `word_FDAE/FDB0/FDB2`
  fault bits. Verified diagnostic: **0 control integrators, 0 actuator writes, 291 status-bit ops**. **[C]**

## Cross-checks against canonical ME7

Sanity-checked against the [S4 wiki](https://s4wiki.com/wiki/Tuning) ME7 reference (Audi 2.7T, ME7.1,
V6 — so expect some divergence). The structure lines up:
- **KFMIRL** torque→spec-load (`rlsol`), **KFMIOP** load↔torque, **KFPED**→capped by `mimax`/`rlmax_w` — matches §1; `rl` = relative load, 100% ≈ 1 bar.
- **KFLDIMX** is the LDR **I-regulator limit** (matches §2), **KFLDRL** the **post-PID** WGDC duty linearization, **KFLDHBN** the max pressure-ratio limit.
- **KFLBTS** component-protection lambda: on the S4 it gates on a *calculated EGT* (`tabgbts_w > TABGBTS`). **This Volvo image diverges** — `sub_86318` gates on **raw conditioned inputs** (`byte_F473` load + `byte_F40E` rpm-class), there is **no `TABGBTS`** symbol, and the EGT sensor *model* (`sub_945C2`) drives a separate over-temp flag via `sub_8C636`, not KFLBTS. See [warmup-idle-thermal.md §4](warmup-idle-thermal.md).
- No extrapolation past the last breakpoint — matches [`lookup.md`](lookup.md).

Divergences / naming: this is an **inline-5**, so the torque model divides by **5** (`divu #5`), not 6.
The boost-target/ceiling map is named **KFLDRX** in the GPHJ dictionary; the canonical ME7 name for that
role is **LDRXN**. Documented for the S4 but **not yet traced here**: the **MAF→load** path (`KFKHFM`,
`FKKVS`) and the `KRKTE` load-scaling bias — good next targets.

## Status & open items
- RAM/CAL cell naming — done ([`ram-names.md`](ram-names.md)), corroborated against the sibling 50GSHJ family A2L/XDF.
- Byte-map master table (KFZW/KFLBTS readers) — done ([`bytemap_callers.md`](bytemap_callers.md)).
- Warm-up / thermal / idle subsystems — traced ([`warmup-idle-thermal.md`](warmup-idle-thermal.md)); ~10 more
  candidates (EGT `sub_945C2`, O2 monitor `sub_A5A9E`, charge/EGR, lambda adaptation) are enumerated there as a backlog.
- Open: pin the exact KFPED interpolation site (vs the `sub_4E6F6` helper); extend
  function-by-function coverage beyond the control path (see [`methodology.md`](methodology.md) → Coverage).
