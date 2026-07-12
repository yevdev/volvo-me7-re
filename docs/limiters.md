# Volvo ME7.0 (50GPHJ) — rev & vehicle-speed limiters

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The two protection limiters tuners most want to touch — the engine **rev limiter** and the
**vehicle-speed limiter** — traced through the C166 disassembly of the stock 50GPHJ image. Both are
separate from the over-boost RPM/boost trip in `sub_DC31A` (see [boost.md](boost.md)). `[C]` = read
from the instruction stream, `[I]` = inferred.

> **Cal values here are read from the GPHJ EU baseline** (`S60R_2005_MAN_Stock.Bin`, identity
> `B5254RT 25RT MAN AWD EU`) — the bin the disassembly matches. They differ by market: a US bin
> (`…AWD US DECOS`) zeroes the speed limiter; the EU baseline does not.

## 1. Rev limiter — `sub_4F97A` (NMAX)

`sub_4F97A` (0x4F97A–0x4FE7E) is a combined **load governor + rev limiter**: it produces the relative-load
setpoint `rlsol` (`word_31E484`) from KFMIRL (the part [torque.md](torque.md) covers) **and** enforces the
rev limit. It reads engine speed nmot (`word_F410`, 0.25 rpm/count) at entry and trips a fuel cut near redline. **[C]**

```
0x4F988  cmp   r4, word_1584E      ; nmot vs NMAX (0x1584E = 6500 rpm)
0x4FBE4  cmp   r4, word_15854      ; nmot vs resume/hysteresis (0x15854 = 6000 rpm)
0x4FC22  mov   r4, word_15848      ; DNMAXH (0x15848 = +400 rpm overshoot)
0x4FC36  bset  word_FD22.2         ; nmot >= active_limit + DNMAXH -> set OVER-REV CUT flag
0x4FDFA  jnb   word_FD22.2, loc_4FE04
0x4FDFE  mov   word_31E484, ZEROS  ; <- THE CUT: rlsol = 0 (load collapses -> injection -> 0)
```

The cut is realized by **zeroing the load setpoint `rlsol`** (`word_31E484`), which drives the
rk→injection-time product (`sub_775C8`) to zero — an effective all-cylinder fuel cut. A coolant gate
(**TMOTNMX** `0x1EDBE`) and road-speed gate (**VNMX** `0x12D71`) select the raised limit **NMAXOG**
(`0x15858`) over **NMAX**; resume is gated at 6000 rpm (`word_15854`, sets `word_FD22.3`). **[C]**

| Cal | Addr | GPHJ-baseline value | Role |
|---|---|---|---|
| **NMAX** | `0x1584E` | 0x6590 → **6500 rpm** | base rev limit |
| **NMAXOG** | `0x15858` | 0x6A40 → **6800 rpm** | raised limit (warm + moving) |
| **DNMAXH** | `0x15848` | 0x0640 → **+400 rpm** | overshoot → hard cut (≈6900 rpm) |
| resume | `0x15854` | 0x5DC0 → 6000 rpm | hysteresis / re-enable |
| TMOTNMX | `0x1EDBE` | — | coolant gate for NMAXOG |
| VNMX | `0x12D71` | — | road-speed gate for NMAXOG |

> **Naming note:** the `0x15848–0x1585C` cluster sits beside KFMIRL (z=`0x158A4`) and was described loosely
> elsewhere (ALGORITHM §1 / ram-names) as KFMIRL "ceiling words." The code compares them against **nmot**
> (e.g. `0x4FBE4: cmp nmot, word_15854`), so they are the **NMAX rev-limiter cals**, not load ceilings.
> KFMIRL (the torque→load map at `0x158A4`) is a separate object and unaffected.

## 2. Vehicle-speed limiter — `sub_50000` (VMAX) + table reader `sub_A5EE`

`sub_50000` (0x50000–0x501D8) is a **PI torque governor**, not a fuel cut. `sub_A5EE` (0x0A5EE) looks up
the gear-dependent VMAX limit (table `0x1BECC`, clutch-engaged fallback `0x1BEE2`); the governor forms
`error = VMAX − predicted_speed` (predicted from vehicle speed `word_3029C6` + a rate term), runs P + I
(`sub_42F16` integrator), and emits a torque-request ceiling `word_304F3C` that is **min-clamped into the
load request** `rlsol`. **[C]**

```
0x50060  sub   r8, word_304F3E     ; error = VMAX_limit - predicted_speed
0x50166  calls 4, sub_42F16        ; I-term (clamped integrator)
0x501C2  mov   word_304F3C, r8     ; VMAX torque-request ceiling
;  applied as a min into the request:
0x4D764  cmp   r12, word_304F3C
0x4D76E  mov   r12, word_304F3C    ; r12 = min(request, VMAX ceiling)
```

| Cal | Addr | GPHJ-baseline value | Role |
|---|---|---|---|
| **VMAX** (table base) | `0x1BECC` | 0x7D00 → **≈250 km/h** | gear-dependent speed limit |
| VMAX clutch | `0x1BEE2` | 0x5A00 → **≈180 km/h** | limit during clutch engagement |

**The EU GPHJ baseline ships an active ≈250 km/h limiter** (the classic European cap; count scale
≈ 1/128 km/h, **[I]**). It bleeds **torque** — lowering the request reduces fuel and boost together — so
there is no hard cut to defeat. *(US `…DECOS` bins set these to 0xFFFF ≈ off, which is why reading a US bin
shows "disabled"; this baseline is EU.)* Mechanism **[C]**; values **[C]** from the EU baseline.

## 3. Cruise-control speed governor — `sub_CA5C6` (`cruise_speed_governor`)

Not a limiter, but it lives on the same vehicle-speed/torque-governor mechanics as VMAX (§2), so it
is documented here. `sub_CA5C6` (0xCA5C6–0xCB3C4, `sub_B81C` chain) is a **state-machined
vehicle-speed governor**: a 7-state jump-table machine and a stored set-speed that tracks/ramps and
a PI stage that emits a torque request. Mechanism **[C]**; the cruise/FGR identity is **[I]** —
strong structurally (set/hold/resume/accel/decel semantics), but no dictionary token names it and
the switch bits are only traced to the debounce block (`0x3B4A2 bmov word_FD0A.7, word_FD08.14`).

```
0xCA73A  cmpb    rl6, #6             ; state byte_300C1E in 0..6
0xCA748  mov     r8, [r8]            ; jump table at 0xD33E
0xCA74A  jmpi    cc_UC, [r8]         ;   -> per-state handler
0xCA6D0  sub     r8, word_3029C6     ; set-speed − vehicle speed (vfzg)
0xCA6DC  cmp     r8, word_26B50      ;   tracking band (above)…
0xCA6F2  cmp     r8, word_26B24      ;   …and below -> in-band flag word_FD76.7
0xCAD10  add     r8, word_26B4E      ; ramp set-speed UP at cal rate
0xCAD54  sub     r8, word_26B4E      ;   or DOWN (accel/decel/resume states)
0xCAD74  mov     word_302CF8, r8     ; word_302CF8 = slew-limited set speed
0xCAFEE  calls   4, sub_41A68        ; gain/limit map 0x26BE0 keyed set-speed
0xCB0A8  calls   4, sub_430DA        ; integrator (state word_300C3E:40)
0xCB35C  mov     word_302CE4, r8     ; OUTPUT torque request (0 below word_26B7A)
```

Structure: set-speed `word_302CF8` follows actual speed `word_3029C6` (`vfzg`) or a held target at
±`word_26B4E` per cycle, clamped to `[word_300C3A, word_300C38]`; a speed-correction term
`word_302CD6` comes from word maps `0x26A7A`/`0x26B02` (keyed vfzg) or fixed/RAM overrides selected
by deviation bands `word_26B54/56/58`; the PI stage (gain map `0x26BE0` keyed set-speed, ramp helper
`sub_42486` with `word_26BAE` + tables `0x26BB0/0x26BC0`, integrator `sub_430DA`, 2-D map via
`sub_43430`) produces `word_302CE4`, scaled by `byte_304D4A` and zeroed below the authority
threshold `word_26B7A`; `sub_CB61C`-region code consumes it (0xCB648). The whole scalar band
`0x26B24–0x26B7C` is this governor's calibration set (see `loadkit/map_names.csv`
`cfg_26B24_cruise_gov_scalars`). **This also resolves the open point in
[etc-throttle.md §6](etc-throttle.md)**: the reference/follower pair supervised by
`diag_setpoint_follow_monitor` (`word_3029C6` vs `word_302CF8`, same slew cal `word_26B4E`) is
vehicle speed vs the cruise set-speed — a set-speed-runaway plausibility monitor. **[C mechanics /
I identity]**

## Open / uncertain
- Scheduling roots: `sub_4F97A`/`sub_50000` show `callers=0` (computed dispatch from the torque
  coordinator, as with the LDR roots) — the dispatch site isn't pinned; the data flow doesn't depend on it.
- VMAX count scale (1/128 km/h vs ×0.004855 mph) gives ≈250 km/h either way; the exact unit is **[I]**.
- NMAXOG timer semantics (ITNMXH `0x1584C` / TNMXH `0x1585C`) inferred from the down-counter structure. **[I]**

## Tuner takeaways
- **Rev limit:** raise **NMAX `0x1584E`** and **NMAXOG `0x15858`** (×0.25 rpm/count; 7200 rpm = 0x7080). The
  hard cut fires at `limit + DNMAXH (0x15848, +400)` — keep a margin. Bump resume `0x15854` so the band
  doesn't re-clamp low. NMAXOG only applies warm (TMOTNMX) and moving (VNMX).
- **Speed limit:** raise or 0xFFFF the **`0x1BECC`** table (and clutch `0x1BEE2`) to lift/remove the
  ≈250 km/h cap. It's a torque ceiling, so there's no cut to chase.
