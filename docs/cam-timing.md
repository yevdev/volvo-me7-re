# Volvo ME7.0 (50GPHJ) — variable cam-timing controller (VVT / NWS)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The closed-loop **cam-phase position controller** that the load model ([load-rl.md](load-rl.md)) only
references as an input. It's a **dual, continuously-variable** system — **both intake (`E`/Einlass) and
exhaust (`A`/Auslass)** camshafts are servo'd; the two channels are structurally identical (separate code
+ cals). Traced from the stock 50GPHJ disassembly. `[C]`/`[I]` as elsewhere.

## Structure (two mirror channels, scheduled together from `sub_B3A2`)

| Stage | Intake (E) | Exhaust (A) |
|---|---|---|
| Cam-edge latch → measured angle `nwist` | `sub_44D22` (shared) → `0x31DA76` | → `0x31DA96` |
| Setpoint map (cam-angle target `nwsoll`) | `sub_48786` reads **KFWNWSAPE** `0x1DB32` → `word_304EC0` | `sub_4B12E` reads **KFWNWSAPA** `0x1E338` → `word_304EFA` |
| **Closed-loop controller (PT1 + P/I)** | **`sub_49DB8`** (0x49DB8–0x4A5DE) | **`sub_4C878`** (0x4C878–0x4D08E) |
| Deliverable solenoid PWM duty (byte) | **`byte_31D2CF`** | **`byte_31D2E5`** |

Scheduled from the page-0xB root `sub_B3A2` (`0x0B3C4`→exhaust init, `0x0B3C8`→intake init). Both
controllers are `callers=2`. Enable/valid byte `byte_31D293` (bit0 intake, bit2 exhaust). **[C]**

## The position loop (`sub_49DB8` intake; exhaust `sub_4C878` is identical)  **[C]**

Error = `nwsoll − nwist`; an asymmetric **PT1** feedback filter (`sub_438F6`, separate gains by error
sign) feeds a **P + I** law with a clamped integrator; gain/limit cals live in the `0x15076–0x150FB`
NW-control block (anchored by the dictionary-named `WNWREO` at `0x150A8`); the duty word becomes a byte:

```
0x49DE0  mov   r12, 9A76h          ; nwist (filtered measured intake cam angle, 0x31DA76)
0x49E04  calls 4, sub_438F6        ; PT1 feedback filter (gain selected by error sign)
0x49F0E  movbz r14, byte_12955     ; P-gain (cal)
0x49F5C  add   r8, loc_F2F2        ; + I-term  (clamped to CDTSLS/CDTSLPE)
0x4A5CE  shr   r8, #8              ; 16-bit duty -> 0..255
0x4A5D2  movb  92CFh, rl1          ; *** byte_31D2CF = intake cam-solenoid PWM duty ***
```

Setpoint maps are cam-angle (°crank) vs rpm×load; a family of condition surfaces refines `nwsoll`
(start `KFNWSE/SA`, knock `KFNWKRE/KRA`, cat-heat `KFNWKHE/KHA`, idle `KFNWLLE`, warm-up `KFNWWLE/WLA`),
selected by engine state. **[C]** for reads/arithmetic; the `KF*E/A` role-by-token names are **[I]**.

## Couplings
- **Load model:** the regulated phase (`nwist`) drives the cam-phase fraction `word_302D80`
  (`FWNWVSAP`/`DNWVSMN`), crossfading KFURL↔KFURLSU ([load-rl.md §4](load-rl.md)). **[C]**
- **Ignition:** the measured phases also surface as `wnwise`/`wnwisa` (`byte_30129C`/`byte_30129B`) and
  blend KFZW1·2 / KFZW3·4 in `sub_518B8` (read at `0x518EA` / `0x51A24`) — matches [ignition.md](ignition.md). **[C]**

So cam timing is bidirectionally coupled: the controller commands the phasers, and the resulting phase
re-indexes both the load reading and the spark advance.

## Open / uncertain
- The physical PWM/CAPCOM register that toggles the solenoid is in a low-level output layer outside this
  cluster; the duty cells (`0x31DA84`/`0x31DAA4` → `byte_31D2CF`/`byte_31D2E5`) are read-only there. **[I]**
- `CDTS*`/`CDTT*` gain names are the IDA DB's own def-file labels (only `WNWREO` `0x150A8` is
  dictionary-verified, which anchors the block as the NW-control band). **[I]**
- `wnwise`/`wnwisa` (`byte_30129C/B`) writers use a segmented store the linear listing pass misses; the
  ignition consumer and the GSHJ XDF identity are solid. **[C]** consumer; writer not shown.
