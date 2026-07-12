# Volvo ME7.0 (50GPHJ) — throttle-servo cluster: position loop + stop-learn adaptation

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The `0xC5xxx–0xC9xxx` function cluster is a **DC-motor position servo with a dual-track
potentiometer and a stop-learn adaptation** — the signature of a Bosch ME7 electronic-throttle
(DVE) subsystem. The *mechanism* below is read directly from the instruction stream **[C]**;
the *physical identity* (electronic throttle body vs. another motor-driven air actuator) is
inferred from ME7 convention **[I]** — see §5.

Legend: **[C]** = shown in the quoted disassembly; **[I]** = inferred.

## 1. The cluster

| Func | Range | Role |
|---|---|---|
| `sub_3FF58` | 0x3FF58–0x3FF82 | latches 3 ADC channels: `loc_F2DA→word_301952` (<<2), `loc_F2D6→word_301954` (<<2), `loc_F2D8→word_301950` **[C]** |
| `sub_C96FC` | 0xC96FC–0xC9838 | linearizes ch1: `loc_F45E = (word_301952 − word_302CB4) × word_302CA2` = **throttle position** (binding dispute resolved, see §5 and [load-rl.md §2](load-rl.md)) **[C]** |
| **`sub_C677A`** | 0xC677A–0xC6A92 | **position servo loop**: error → deadband → PD → H-bridge PWM **[C]** |
| **`sub_C7EEA`** (`etc_stop_learn_adapt`) | 0xC7EEA–0xC891C | **stop-learn adaptation state machine** (scheduled from `sub_B81C` at 0x0B8C8) **[C]** |
| `sub_C891C` | 0xC891C–0xC8970 | adaptation-failure handler: substitute cal defaults **[C]** |
| `sub_C73E2` | 0xC73E2–0xC7432 | protection shutoff: if adaptation counter `byte_304D45` (page 0xC1) > `byte_1B966` → kill drive (`loc_F440=0`) **[C]** |
| `sub_C75C2` | 0xC75C2–0xC77DA | seeds gain/offset cells from page-5/6 cal (per [load-rl.md](load-rl.md)) |
| **`sub_C77DE`** (`etc_adapt_sequencer`) | 0xC77DE–0xC7D4E | adaptation **precondition/sequencer**: arms the `word_FD6A.14` gate for §3 (see §3b) **[C]** |

## 2. The position servo (`sub_C677A`)  **[C]**

```
0xC6780  mov     r10, loc_F446        ; position SETPOINT
0xC6784  sub     r10, loc_F45E        ; − position FEEDBACK (linearized pot)
0xC67A0  mov     loc_F442, r10        ; error, clamped ±0xFFF
0xC67CA  mov     r1, loc_F45A         ; previous position
0xC67CE  mov     r11, loc_F45E
0xC67D2  sub     r1, r11              ; Δposition (derivative input)
0xC67DE  cmp     r1, loc_F448         ; deadband thresholds (cal 16EB2/16EB4,
0xC67EA  cmp     r2, loc_F44A         ;   16EB6/16EB8 selected by loc_FD70.1)
0xC67F0  movbz   r4, loc_F434         ; D-gain
0xC67F4  mul     r4, r3               ; D-term (clamped ±0x2800/0xD800)
0xC6820  add     r5, loc_F456         ; + accumulated term → signed drive
0xC6826  bset    word_FD68.3          ; drive sign → direction flag
0xC682C  mulu    r15, r5              ; magnitude × loc_F436 (output gain)
0xC683A  mov     loc_F440, r4         ; → PWM duty magnitude
0xC683E  bfldl   word_FFD0, #84h, #4  ; H-bridge direction port bits (other
0xC685E  bfldl   word_FFD0, #84h, #80h;   branch: opposite polarity)
0xC6862  mov     r15, #2711h
0xC6866  mulu    r15, r4
0xC6868  mov     word_FE34, MDH       ; → hardware PWM compare register
0xC686E  mov     word_F034, #270Fh    ; PWM period = 9999
```

A textbook PD position loop: setpoint `loc_F446`, feedback `loc_F45E`, deadband from the cal
pairs `word_16EB2/16EB4` and `word_16EB6/16EB8`, signed drive split into a direction flag
(`word_FD68.3` + port bitfield `word_FFD0`) and a PWM magnitude `loc_F440` scaled into the
C167 PWM compare register `word_FE34` with period 9999. **This is a motor H-bridge, so
`loc_F45E` here is the position feedback of a motor-driven actuator** **[C]**.

## 3. The stop-learn adaptation (`sub_C7EEA` = `etc_stop_learn_adapt`)  **[C]**

Gated state machine (`byte_301779`, states 0–0xB), entered only while `word_FD6A.14` is set
and `word_FD6C.5` (adaptation-done/lockout) is clear. What it does, state by state:

- **State 0 → 1**: initialize the search window: `word_302CB2 = word_16F16` (low start),
  `word_303C4C = word_16F2E` (high start).
- **State 1**: converge the window by `word_16F0E` per tick, clamp both bounds to 0xFFF
  (12-bit signal range), and **average the settling signal pair**:

```
0xC80DC  mov     r4, loc_F440          ; abort learn while motor drive
0xC80E0  cmp     r4, word_16F0A  ; CAL ;   exceeds cal threshold
0xC8152  mov     r4, word_302CB0
0xC8156  add     r4, word_301952       ; (old + new ADC ch1) / 2
0xC815A  shr     r4, #1
0xC815C  mov     word_302CB0, r4
0xC8160  mov     r5, word_302CC2
0xC8164  add     r5, word_301954       ; same for parallel track ch2
0xC8168  shr     r5, #1
```

- **States 2–3**: widen by `word_16F34`, re-check plausibility (`word_16F18`/`word_16F2C`
  limits); drive-direction/duty gates (`word_FD68.3`, `loc_F440` vs `word_16F0C`).
- **States 4–5**: latch the learned low stop (`word_303C44`) and run a **gain check**:
  `word_302CCA = ((unk_302CAC − word_302CB2) × word_302CA2) >> 11`, bounded by
  `word_16F42..word_16F44`; store `byte_304D49` to adaptation page 0xC1.
- **States 6–9**: two-point slope test — sample `word_301952>>2` and `word_301950` at two
  operating points, compute the difference/ratio via the 32-bit divide helpers
  `sub_E4058`/`sub_E4078`, and window the intercept (`word_302CBA` vs `word_16F20/16F22`)
  and slope (`word_302CC0` vs `word_16F28/16F2A`).
- **State 0xA**: **persist** — the learned words (`word_300BF8` status, `word_303C40/44/46/
  48/4E/4A/42`) are queued through transfer descriptors (`0xC86F8/0xC8710/… calls 3,
  sub_386F2`, block at `0x300BEC`, kicked by `0xC87C6 calls 3, sub_38ECE`) to non-volatile
  storage, then the adaptation is closed (`word_FD6C.5` set).
- **Every abort** writes an error code to `byte_301775` (`0x14`, `0x18`–`0x1E` — e.g.
  `0xC7F22 movb byte_301775, rl4`), sets `word_FD6C.7`, flags `byte_301778 |= 0x40`
  (`0xC8038`) and calls `sub_C891C`.

### 3b. The adaptation sequencer (`sub_C77DE` = `etc_adapt_sequencer`)  **[C]**

Runs ahead of §3 (entered through the 4-byte stub `sub_C77DA` at the end of `sub_C75C2`) and
decides *whether* a stop-learn may start. It evaluates the enable windows from the
`cfg_14635` byte band — two temperature-like bytes `byte_30163A` vs `byte_14657/14658`
(`0xC77F4`), `byte_301626` vs `byte_14655/14644`, `byte_3015D8` vs `byte_14656`, `byte_301655`
vs `byte_14646` — and a **drift demand check** `(word_16F1A − word_302CB2) × word_302CA2` vs
`word_302C6C` (`0xC780C–0xC783A`). Any failed gate writes a block-reason code 1–9 to
`byte_301775`, sets `word_FD6C.2` and calls the abort helper `sub_C7D5E` (`byte_301778 |= 0x20/0x40`).
With gates passed it runs its own small state machine (`byte_301776` states, settle counter
`byte_301777` vs `byte_14647/14648`, status nibble in `byte_301778`): spring/return-motion tests
comparing the throttle position `loc_F45E` against `word_302CCA + word_16F3E/16F40` windows
(`0xC79D2`, `0xC7A2A`) and amplifier checks around `word_16EFE/word_16F00`, then **arms the
stop-learn gate `word_FD6A.14`** (`0xC7B66 bset word_FD6A.14`) that §3's state machine requires,
resetting the §3 state cells (`byte_301779` etc., `0xC784A–0xC7872`). **[C]**

**Failure fallback (`sub_C891C`)** — substitute calibration defaults for the learned values:

```
0xC892C  mov     r4, word_16F1A   ; default low-stop reference
0xC8934  mov     r5, word_16F30   ; default high-stop reference
0xC8944  mov     r4, word_16EFA
0xC8948  mov     word_302CA2, r4  ; default linearizer gain
```

**Live outputs** (every pass, tail of `sub_C7EEA`): `word_302CB4 = word_302CB2 +
word_302CC6` clamped 0xFFF (`0xC88DE mov word_302CB4, r8`) and `word_302CC4 = word_303C4C −
word_302CC6` — i.e. the **offset that `sub_C96FC` subtracts at `0xC9708`** to linearize the
signal, plus byte exports `byte_30177E`/`byte_301780` (= low/high >> 4). **[C]**

## 4. Calibration cells of the 0x16EBx–0x16F5x band (partial)  **[C roles]**

| Cal | Role |
|---|---|
| `word_16EB2/16EB4`, `word_16EB6/16EB8` | servo deadband thresholds (two operating modes) |
| `word_16EFA` | default linearizer gain (failed-adaptation substitute) |
| `word_16F0A`, `word_16F0C` | max motor duty during low/high-stop learn |
| `word_16F0E`, `word_16F34` | window converge / widen step |
| `word_16F16`, `word_16F2E` | low/high window start values |
| `word_16F18`, `word_16F2C` | learned low/high plausibility limits |
| `word_16F1A`, `word_16F30` | default low/high stop references |
| `word_16F1C` | linearizer gain source (`word_302CA2 = 0x08000000/word_16F1C`, [load-rl.md §2](load-rl.md)) |
| `word_16F20/16F22`, `word_16F28/16F2A` | two-point test intercept / slope windows |
| `word_16F42/16F44`, `word_16F48`, `word_16F50` | gain-check bounds / retest threshold / travel margin |
| `byte_14642`, `byte_1464B–0x1465A` | retry counts, settle counts, temperature/step limits for the state machine |
| `word_26A76` (page 9) | divisor in the state-9 duty/count derivation (`0xC85FA`) |

## 5. Open / uncertain

- **Actuator identity: electronic throttle [I, now strongly corroborated].** Dual-track pot
  (two `<<2` ADC channels averaged and cross-checked), H-bridge + PWM drive, learned mechanical
  stops with EEPROM persistence and cal-default fallback: on an ME7 E-gas engine this is the
  **electronic throttle (DV-E) stop-learn** ("Anschlagadaption"). No other motor-driven
  dual-pot air actuator exists on this engine. Corroboration (round 2): the position signal
  `loc_F45E` feeds the `0x161EE` map axis in the HFM plausibility (`sub_76A68`), and the GPHJ
  dictionary labels that axis **KFMLDMX "Throttle#"** — the calibration itself calls this
  signal's axis *throttle*. Nothing in the quoted code names the device, so the identity stays
  [I], but every external anchor points the same way.
- **`ml_hfm` binding dispute — RESOLVED (round 2, `sub_76A68` traced).** This doc's reading
  won: **`loc_F45E` is the linearized throttle position**, not the air-mass signal.
  In `sub_76A68` the value is only a **map-axis input** (`0x76A7E mov r12, loc_F45E` →
  `word_3028AC` → KFMLDMX `0x16208`, axes "Throttle#" × "RPM"), producing the max-plausible
  air-mass bound; the cell actually tested against `MLDHFMKU 0x2188A` and the KFMLDMX/KFMLDMN
  window is **`loc_F384`** — the real `ml_hfm`, produced by `sub_7633C`/`sub_7628C` from the
  128-point **MAF curve `0x160E8`** on ADC channel `loc_F2DE`, with the KFKHFM correction
  multiplying it. And `sub_C96FC`'s linearization offset `word_302CB4` is written **only** by
  the stop-learn state machine (`0xC88DE`) — a learned end-stop, which no MAF has.
  [`ram-names.md`](ram-names.md), [`load-rl.md §2`](load-rl.md) and `loadkit/ram_names.csv`
  are corrected (`0xF45E = throttle_pos_fb`, `0xF384 = ml_hfm`). **[C]**
- `word_301950` (ADC ch3, unshifted) identity unpinned: sampled at both slope-test points —
  candidates are motor current or the second pot on a different scale. **[I]**

## 6. Cluster monitors (diagnostic — round 2)

Two more members of the `0xC5xxx–0xCAxxx` cluster turned out to be **pure monitors** (no
actuator/setpoint writes — outputs are debounce counters, status flags and fault bytes only):

**`sub_C5F2C` = `diag_input_monitor_bank`** (0xC5F2C–0xC6410; 1st slot of the `sub_B81C`
dispatch, `0x0B8AC`). A bank of ~14 debounced condition monitors over CAN-mirror signals
(`byte_301437` state 0/1/3, `byte_301443` with hysteresis cals `0x14576/77`, `word_30256C.12`
— all fed by `can_rx_signal_unpack`) and the ADC byte `byte_3014D2` (= `word_301934 >> 2`,
`sub_75AD2`): absolute min/max (`0x1458B/88/89`), stuck-signal (`|Δ| < byte_1457C` persisting),
and deviation below a slow learned baseline:

```
0xC5F88  movb    rl1, byte_1457E     ; debounce threshold (cal)
0xC5F8C  mov     r12, #975Ch         ; debounce counter cell
0xC5F9C  cmpb    rl2, rl1            ; count reached?
0xC5FA6  bset    word_FD64.6         ; -> monitor flag
0xC62CA  mov     r12, word_16EAC     ; baseline filter gain
0xC62D4  calls   4, sub_42CF4        ; me7_fraction_blend
0xC62D8  mov     word_303C3E, r4     ; slow baseline of byte_3014D2
```

Its mask flags gate other subsystems: `word_FD64.11/.12` disable the **misfire monitor**
(`sub_A0000`, 0xA06AA/0xA0718) and **knock-circuit diag** (`sub_39FCA`, 0x3AA7C); `word_FD66.5`
is read by the **torque coordinator** (`sub_4D86C` 0x4DB84) and `word_FD66.2` by the **idle
governor** (`sub_7D58E` 0x7D5AC). One-shot fault bytes `byte_301767–6F` are consumed and
cleared by **`sub_C6410`** (`diag_monitor_status_report`), which packs status to CAN
(`sub_B31AC` ×2, 0xC660E/0xC661C). Mechanism **[C]**; which physical module the CAN state
belongs to is **[I]** (unresolved).

**`sub_C9F44` = `diag_setpoint_follow_monitor`** (0xC9F44–0xCA4B8; `sub_B81C` slot 0x0B8B4).
Deviation supervision of a reference/follower pair: `word_3029C6` (reference, produced by
`sub_8A834` in the fuel band and forced to 0 under fault gates) vs `word_302CF8` (a
rate-limited follower of that reference computed in `sub_CA5C6`, slew cal `word_26B4E`),
plus a raw-ADC cross-check `word_30196E` (hardware-latched, no code writer):

```
0xC9F94  mov     r4, word_3029C6     ; reference …
0xC9F98  sub     r4, word_302CF8     ;   − follower
0xC9F9C  cmp     r4, word_16F5A      ; deviation > cal threshold?
0xC9FA6  cmp     r4, word_16F5E      ; … debounced (count cal)
0xC9FB6  orb     byte_300C14, rl4    ; -> fault bit
0xCA1B2  mov     r4, word_30196E     ; ADC cross-check
0xCA1B6  cmp     r4, word_3029C6     ;   vs same reference
```

Enable window: rpm-class `byte_F40E` in `[byte_14744, byte_14743]`, ADC byte `byte_3014DD` in
`[byte_14742, byte_14741]`, masked by `word_FD64.12` (from the monitor bank above). Outputs:
status bytes `byte_300C06/13/14`, `byte_301794`, and condition bits `loc_FD70.13–.15` /
`loc_FD72.0–.1` — the same `FD70` status word whose bit 1 selects the servo deadband set (§2).
Mechanism **[C]**; the supervised physical quantity is **[I]** (its readers are CAN/diag
reporting only: `sub_57CD4`, `sub_6000C`).

> **Update (cruise identification):** `sub_CA5C6` is now identified as a cruise-control-type
> vehicle-speed governor ([limiters.md §3](limiters.md)); `word_3029C6` is vehicle speed (`vfzg`)
> and `word_302CF8` its slew-limited **cruise set-speed**. So this monitor supervises
> set-speed-vs-vehicle-speed tracking (set-speed runaway). Mechanism unchanged **[C]**; identity
> now **[I-strong]** via the governor's state machine + LIVFZDE/VMAX cross-refs.

**`sub_C983A` = `diag_throttle_angle_from_charge`** (0xC983A–0xC9E36; scheduler slot 0x0B722) —
DIAGNOSTIC, short entry. Computes the **expected throttle angle from charge** (the dictionary's
exact phrase for cal `0x14709`, its min-rpm enable): expected `byte_301791` = min(2-D byte map
`0x1465E` keyed rpm-class `byte_F40E` × charge-derived `byte_30178C` (from load byte `byte_F473`,
`sub_40CA4` at 0xC9B3E), cap table `0x14724`); maintains two PT1-filtered banks
`byte_30178E`/`byte_301790` (`sub_42CF4`, rate table `0x1470B`); checks the raw pot `word_301952`
against a `byte_30177F<<4 ± word_16F50` window and majority-votes bank deviation above min-rpm
`byte_14709` with time cal **TDKPAW** `0x1470A` → fault/condition bits `loc_FD70.3/.4`,
`word_FD6E.3/.4/.8/.9/.10/.13/.14`, `word_FD6C.15`. No actuator write — monitoring only; the
filter-time family **TFWDKPN** `0x14712` sits in the same table region (**[I]** for that binding).
**[C]**
