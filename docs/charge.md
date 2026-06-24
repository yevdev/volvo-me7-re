# Volvo ME7.0 (50GPHJ) — manifold-pressure → charge model

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The intake-manifold-pressure → charge estimator (`sub_AD3D0`) and its limiter/plausibility half
(`sub_AC5DE`) — the ME7 speed-density "rl-from-ps" path, one stage upstream of boost. Traced from the
stock 50GPHJ disassembly. `[C]`/`[I]` as elsewhere.

> **Not EGR.** A firmware-wide search finds only two `AGR` symbols (`CDAGR` 0x9A74, `CDKAGRF`), **both
> outside this cluster**, and the arithmetic is a cascade of pressure-ratio divisions + a charge
> gradient/peak-hold — no residual-fraction or valve-duty math. This is the charge/manifold-pressure
> path, not an EGR estimator. **[C]**

## Functions
| Func | Range | Role |
|---|---|---|
| **`sub_AD3D0`** | 0xAD3D0–0xAD97A | pressure-ratio cascade → modelled charge `word_302C40`; charge-gradient `word_302C04`; 5-slot peak-hold; output PT1 → `word_302C54` |
| **`sub_AC5DE`** | 0xAC5DE–0xACCAA | charge **ceiling** `word_302C00` + limit/region flag machine (`word_FD5C/FD5E`); PT1 (`sub_43904`) / slew (`sub_438F6`) / clamped integrator (`sub_42F16`) |

~13 siblings (`0xAC45A–0xADA06`) share the `word_302Bxx/302Cxx` RAM bank. **Scheduling:** `sub_B81C`
calls `sub_ACCAA` at `0xB828`; `sub_B6E6` drives `sub_AD9CE`/`sub_ADA06` — the same periodic tasks as
the LDR boost loop, one stage upstream. (`sub_AD3D0`/`sub_AC5DE` show `callers=0` → computed dispatch.) **[C]**

## The pressure-ratio cascade (`sub_AD3D0`)  **[C]**

```
0xAD3DA  mov   r12, word_30563A     ; reference pressure (sub_D2C9A, cal-clamped)
0xAD3E2  mov   r14, word_302496     ; measured load/boost (the same cell the LDR loop uses)
0xAD3F6  divlu r12                  ; ratio#1 = word_302496 / (word_30563A>>1)
0xAD424  divlu r8                   ; ratio#2 = (.<<15) / word_302DAE (model pressure)
0xAD432  mov   word_302C40, r9      ; *** modelled charge (intermediate) ***
0xAD44A  divlu r8                   ; ratio#3 = (word_302C40<<15) / word_302E28 (charge/temp term)
```

Each `(X<<15)/Y` is a 1.15 fixed-point pressure quotient — measured boost (`word_302496`) normalised by
a reference pressure, a model pressure, and a temperature term → modelled charge `word_302C40`. It then
forms a **charge gradient** `word_302C04` over a 4-tick shift register and a 5-slot peak-hold, PT1-filtered
into the deliverable `word_302C54`. `sub_AC5DE` derives the charge **ceiling** and runs the
`word_FD5C/FD5E` region/limit state machine, smoothing with PT1/slew. **[C]**

## Tie to boost / load
`word_302496` is the shared measured-load cell the LDR boost loop reads (`sub_DBB04`, [boost.md](boost.md));
`word_302C40`/`word_302C54` feed back into the `0xD2–0xDA` sensor/LDR-preprocessing bank. So this model
sits between the raw sensors and the boost controller. **[C]**

## Open / uncertain
- `word_FD5C/FD5E` bit labels are inferred from set/test context, not proven names. **[I]**
- Whether `word_302C40` is `rl_w`-scaled or a raw pressure ratio — cross-check vs the XDF. **[I]**
- The rpm gates `0x16CE4`/`0x16CE6` are `0xFFFF` in stock → one `sub_AD3D0` branch is inert in this cal. **[C]**
- Inline-map pointers via `sub_40D5C`/`sub_40B88` are DPP-relative (page not resolvable from the text dump);
  cited by call site only, no KF* name invented. **[I]**
