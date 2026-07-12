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
missing**. Beyond it, the OBD diagnostic monitors and their configuration layer are identified (§7). A
handful of former high-cal-touch unknowns are now identified as the **diagnostic/monitoring tail**, not
control (`sub_E018C` = status/ID-frame init, `sub_922B8` = EGT status monitor, `sub_6C6DA` = O2/lambda
status packer, `sub_9D894` = EVAP-purge monitor, `sub_AAC4E` = CDDST OBD monitor — all §7). (`sub_9A52` = diagnosis-codeword expansion and `sub_BEEDC` =
monitor enable table, §7; `sub_C7EEA` = throttle-servo stop-learn adaptation,
[etc-throttle.md](etc-throttle.md); `sub_5637C` = CAN RX signal unpack, §7.) The remainder is CAN/KWP2000 comms and leaf/library routines. This is the control algorithm + the
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
- **Diagnosis-enable codeword expansion** — `sub_9A52` (`diag_codeword_expand_init`, init-time, sole caller
  `sub_A082`): reads ~40 one-byte cal codewords from the `0x18000–0x1802D` band (dictionary-named `KAMFZ`,
  `CDAGR`, `CDDST`, `CDEFST`, `CDKVS`, `CDHSV`, `CDLSH`, `CDLSV`, `CDMD`, `CDLDP`, `CDLLR`, `CDSWE`,
  `CDTEFST`, `CWNWS`, `EPRSLNR`, `CDKAT`, `CWSLS`, `SWTTNR`, `CWUVLOG`, `CWDSLSY`, `CDHSH`, `CDSLS`,
  `CDLASH`, + unnamed `0x18016–0x1802D`, `0x12600/03/05`) and expands each bit into the RAM enable flags
  `word_3018D6/D8`, `byte_301220–22` and the bit-addressable `word_FD00/FD02` (e.g. `0x09A56 movb rl1,KAMFZ`;
  `0x09E58 bmov word_FD00.1, r1.0`). Pure vehicle-configuration: which OBD monitors run is decided here. **[C]**
- **Per-monitor enable table** — `sub_BEEDC` (`diag_monitor_enable_table_init`): converts those codeword
  flags into 0/1 enable words at `word_30BE38+8k` (adaptation page 0xC2, one 8-byte record per monitor,
  `0xBEEEA/0xBEF42 mov word_30BE38/word_30BE80,…`), walking the per-monitor cal tables `0x1B8E3`
  (1 B/monitor) and `0x1B8F1` (3 B/monitor). **[C]**
- **ETC-cluster input monitor bank** — `sub_C5F2C` (`diag_input_monitor_bank`, 1st `sub_B81C` slot) +
  status reporter `sub_C6410`: ~14 debounced monitors over CAN-mirror signals (`byte_301437/43`,
  `word_30256C.12`) and ADC byte `byte_3014D2` (min/max/stuck/baseline-deviation vs cals `0x14576–0x1458C`,
  `0x16EAC–B0`). Its mask flags `word_FD64.11/.12` **gate the misfire and knock-circuit monitors**;
  `word_FD66.2/.5` are read by idle governor / torque coordinator. Verified: no actuator writes. **[C]**
  → [etc-throttle.md §6](etc-throttle.md).
- **Reference/follower deviation supervision** — `sub_C9F44` (`diag_setpoint_follow_monitor`): windows the
  fault-gated reference `word_3029C6` (`sub_8A834`) against its slew-limited follower `word_302CF8`
  (`sub_CA5C6`) and a raw ADC cross-check `word_30196E`, debounced via the `0x16F52–0x16F66` cal band, →
  status bytes `byte_300C06/13/14` + condition bits `loc_FD70.13–.15`/`loc_FD72.0–.1`. Supervised quantity
  identity **[I]**. → [etc-throttle.md §6](etc-throttle.md).
- **OBD parameter seed / readiness edges** — `sub_A7D34` (`diag_obd_param_seed_init`): copies the scalar cal
  band `0x2418E–0x241B4` into RAM mirrors `word_305386–word_3053B2`, builds monitor bitmasks from cal
  bit-indexes (`byte_1A18C/8F/91`), and edge-detects NV status `word_30A252 & word_241A6` (readiness flags
  `byte_300A04–0B`). The whole `0x24162–0x241DA` orphan cluster is **scalars, not a map** (plain `mov`/`cmp`
  readers `sub_A3A18`/`sub_A4904`/`sub_A7D34`). **[C]**
- **CAN RX signal unpack** (comms, not a monitor) — `sub_5637C` (`can_rx_signal_unpack`, via `sub_57FBE`):
  polls (flag-pointer, mask) pairs held in **calibration** `0x11A32–0x11AE8` (incl. dictionary cells
  `ZKLLRD`/`MDST` at `0x11A86/88`), extracts signals through descriptor readers `sub_E3A86`/`sub_E3ACE`
  (word signals carry a −0x200 offset, torque-interface style: `0x5640E sub r4,#200h`) into RAM mirrors
  `byte_301427–48`/`word_302580–25AA`, acknowledges by clearing the flag byte (`0x5642C movb [r12],rl2`),
  and calls two **cal-held far code pointers** (`0x11B42/44`, `0x11B92/94`) through the push-rets
  trampoline `sub_8E52`. First confirmed member of the "remainder is comms" tail. **[C]**
- **EGT / exhaust status monitor** — `sub_922B8` (`diag_egt_status_monitor`): debounced status bank
  (13× `sub_32E88`, packs via `sub_B31AC`) over the `EXA*`/`EFF*` exhaust-diag cal band `0x19F10–0x19F37`
  (`EXAAAA`,`EXAFRAO`,`EFFZET8`,`EFFZZZ`; `EXA*` shared with `egt_sensor_model`) → status bytes
  `byte_30084C…7C` + flag bank `byte_301624/625`. Verified: **no port/actuator write**. Exhaust/EGT
  identity **[I]**. **[C]**
- **O2 / lambda-sensor status packer** — `sub_6C6DA` (`diag_o2_sensor_status_pack`): gated by codeword
  `byte_301220.1` (`CDSLS`); 34× debounce `sub_32E88` + 12× CAN-pack `sub_B31AC` of status words
  `word_303B64/70/74`; reads threshold band `0x210CA–0x21104` (`MSDRKAT`/`MSDRKAT2`) + `NDLDRAPU`
  (`0x18A78`); adjacent dict `FLAMPFT`/`FLAMPMR`/Nernst-cell-temp cals corroborate the lambda/exhaust
  role. No actuator write. Identity **[I]**. **[C]**
- **EVAP purge-system monitor** — `sub_9D894` (`diag_evap_purge_monitor`): gated by `word_3018D6.1` +
  `word_FD02.9`; reads the purge quantity `word_3052A8` (from `evap_purge_ctrl` `0x8DE10`), `divlu`-normalizes
  it and PT1-filters (`sub_43904`) into page-C2 EVAP RAM (`byte_30A0E2`,`word_30A20A`); cal `EXBLASH2`
  (`0x1A06F`), `byte_1A06D/6E`; status flag banks `byte_30169C–3016A8`. No actuator write. EVAP-system
  identity **[I]**. **[C]**
- **CDDST OBD monitor** — `sub_AAC4E` (`diag_obd_monitor_cddst`): gated by `word_3018D8.2` (`CDDST`);
  edge-tracks `byte_303331/332`, debounces (`sub_32EF0/FC4/F5C`) + one PT1, packs status via `sub_B31AC`.
  Its threshold band `0x23FC8–0x24016` is **scalars, not a map** (`mov`/`cmp` on `word_23FD4–23FE8` + byte
  config `byte_1A1A2–8` near `INHASE06`) → `cfg_obd_diag_thresholds`. Exact monitor identity **[I]**. **[C]**
- **Diagnostic status/ID-frame init** — `sub_E018C` (`diag_status_frame_init`): builds the status/ID frame
  RAM block `word_300404–word_3004D8` from 27 config-word+mask pairs `0x2C52A–0x2C580` (`val AND mask`,
  merged with `~mask & literal`) plus ASCII/literal seeds; the block is later serialized into CAN mirror
  `byte_305780–79D` by the `0xE1xxx` packer (`sub_E134E`). Sole caller `sub_642C2` (when
  `word_300404 != 0x3FD0`). Config/identity frame, not control. Frame identity **[I]**. **[C]**
- **Component-protection (BTS) thresholds** — the `0x23440–0x234AC` orphan cluster is **scalars, not a map**:
  `fuel_component_protect` (`sub_86318`) reads it purely via `mov`/`cmp` — over-temp threshold+hysteresis
  pairs (`word_2349C/A0`, `2349E/A2`, `234A4/A8`, `234A6/AA`) with dict `DTBTS 0x234AE`/`KFDLBTS 0x234D2`
  adjacent → `cfg_bts_thresholds`. **[C]**
- **CAN RX per-message handler bank** (comms) — `sub_56E00` (`can_rx_msg_handler_bank`, called from
  `can_rx_signal_unpack` at 0x56982): jump-table dispatch on a message index (`0x56E04 cmpb rl1,#62h`,
  table at `0xC1E2`, `0x56E16 jmpi`); each case polls its cal-held (flag-pointer, mask) pair in
  `0x11A50–0x11B0C`, extracts fields via `sub_E3A86`/`sub_E3ACE`/`sub_E3B34`/`sub_E40DE` into the same
  `byte_3014xx`/`word_3025xx` mirrors, clears the flag, and maintains a message-timeout counter
  `byte_30143D` vs cal `byte_13803` (codeword `byte_137FF`; handshake bits via pointers
  `word_11B0C`/`word_11B5C`). Second confirmed comms-tail member. **[C]**

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
