# Volvo ME7 (50GPHJ) C166 — the air→load path (MAF/HFM → relative load `rl`)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

How the ECU turns the measured air signal into the **relative load `rl`** that the torque
model (KFMIOP/KFMIRL), the boost loop (LDR), ignition, knock and fueling all consume. Traced
through the C166 disassembly of the stock 50GPHJ image (Infineon C167CR); the code is
byte-identical across calibration revisions, so this holds for any GPHJ tune.

Legend: **[C]** = read directly from the cited instruction stream; **[I]** = inferred from
structure / Bosch ME7 convention, not literally proven. Physical address = `(page<<14)|offset`;
the `sub_41CC0` map pointer the caller loads is `(offset=r12, page=r13)`. Map *names* are taken
from the GPHJ dictionary [`../loadkit/map_names.csv`](../loadkit/map_names.csv) and attached
only where the pointer lands on the named block; otherwise a map is cited by address.

> **Baseline is clean stock.** The tuner-hack injection offsets `0x0D3F0`, `0xE4240`,
> `0xF0800` contain **no functions** in this image (verified: no headers, no disassembled
> bytes there) — the `0xD2xxx–0xD3xxx` load cluster documented below is genuine high-ROM stock
> code, *not* the low-ROM `0x0D3F0` hack region (different address entirely). **[C]**

---

## 0. TL;DR — what produces `rl`, and where it goes

This firmware is **MAP-based** (manifold-pressure / speed-density) for its primary load, with
the **HFM (hot-film MAF)** signal applied as corrections and plausibility — *not* a pure
MAF→load conversion. The load is built in a task cluster in code **page 0x0D**
(`sub_D2C9A → sub_D31CA → sub_D327E → sub_D34DC`), and the result is written to the live
engine-data cells **`loc_F47A`** and **`loc_F478`** (= ME7 `rl_w` / `rl`, 0xF4xx live page).

| Stage | Function(s) | Address range | Produces |
|---|---|---|---|
| Air signal (HFM/MAF voltage → air mass) | `sub_3FF58` (ADC latch) → `sub_C96FC` (linearize) | 0x3FF58; 0xC96FC–0xC9838 | `loc_F45E` (air-mass signal) **[C]** |
| Engine speed `nmot` | `sub_98C42` | 0x98C42–0x98C74 | `word_F410` = `nmot` **[C]** |
| **KFURL load model + corrections** | **`sub_D2C9A`** | **0xD2C9A–0xD31CA** | blended load + correction terms **[C]** |
| Load assembly + offsets | `sub_D31CA`, `sub_D327E` | 0xD31CA–0xD3220; 0xD327E–0xD337C | `word_302D94/98`, `word_302DA8` **[C]** |
| **`rl` output** | **`sub_D34DC`** | **0xD34DC–0xD35AE** | **`loc_F47A`, `loc_F478` (`rl`), `byte_F473`** **[C]** |
| Default/limp `rl` | `sub_D35AE` | 0xD35AE–0xD35D4 | forces `rl = 0x10AB` **[C]** |
| HFM-vs-model plausibility | `sub_D337C`, `sub_76A68` | 0xD337C; 0x76A68 | fault bits + HFM correction `word_30564C` **[C]** |

**Consumers of `loc_F47A` / `byte_F473` (= `rl`) — confirms it is *the* load variable [C]:**
`sub_4F4BC` (KFMIOP torque model, 0x4F4CA), `sub_64C80` (thermal model, 0x64CC4),
`sub_52D16` (cat-heat, 0x52A22), `sub_7BA8C` (knock, 0x7B9AE/0x7BAC8), and ~40 other sites.
`loc_F47A`/`byte_F473` is read across the whole image — exactly the footprint of `rl`.

---

## 1. Where it lives and how it is scheduled  **[C]**

The cluster runs as a set of **segment-0x0D far-call task callbacks** from the cooperative
schedulers in the `0x0Bxxx` region. The primary scheduler `sub_B81C` (a per-tick task list)
calls the air-mass/pressure preprocessing (page-0x0C functions) first, then the load cluster,
then LDR boost, then fuel — i.e. the **air → load → boost → fuel** ordering is visible right
in the dispatch list. From `sub_B81C` (0x0B8AC–0x0B918):

```
0x0B8AC  calls 0Ch, sub_C5F2C      ; air-mass / pressure preprocessing (page 0xC)…
0x0B8B4  calls 0Ch, sub_C9F44
0x0B8C8  calls 0Ch, sub_C7EEA
0x0B8CC  calls 0Ch, sub_C6FA4
0x0B8D4  calls 0Dh, sub_D222A      ; *** load cluster (segment 0xD) entry ***
…
0x0B8F4  calls 0Dh, sub_DB370      ; LDR boost chain begins (consumes rl)
0x0B900  calls 0Dh, sub_DBB04      ; LDR PI / feed-forward
0x0B918  calls 8,   sub_8981C      ; fuel multiplier (consumes rl via KRKTE)
```

The `calls 0Dh,…` operand is the **target segment** (0x0D → physical `0xDxxxx`), so these are
far-calls into the load code. The big computational functions (`sub_D2C9A`…`sub_D34DC`) carry
`callers=0` in the dump — an IDA cross-segment-resolution gap, not indirect dispatch; sibling
members of the cluster are reached from parallel scheduler roots (`sub_B6E6`, `sub_B3A2`,
`sub_B218`, `sub_BB16`). **[C for the dispatch lines; I for which root drives the inner chain]**

---

## 2. The air signal: HFM/MAF voltage → air mass  **[C]**

The raw air signal is a hardware A/D channel, latched and then **linearized in arithmetic, not
through a characteristic map**. `sub_3FF58` masks the 10-bit ADC results
(`loc_F2DA/F2D6/F2D8`, which have no code writers → PEC/DMA-filled hardware registers) and
shifts them into working cells:

```
0x3FF58  mov   r4, loc_F2DA      ; raw A/D channel
0x3FF5C  and   r4, #3FFh         ; 10-bit ADC mask
0x3FF60  shl   r4, #2
0x3FF62  mov   word_301952, r4
```

`sub_C96FC` (0xC96FC–0xC9838) then converts to the air-mass signal **`loc_F45E`** with an
offset + linear-gain (one branch adds a `divlu` normalization), the gain being a reciprocal of
a calibration word:

```
0xC9704  mov   r15, word_301952  ; raw ADC value
0xC9708  sub   r15, word_302CB4  ; − offset (cal)
0xC971C  mov   r4,  word_302CA2  ; × gain  (word_302CA2 = 0x08000000 / cal word_16F1C)
0xC9732  mulu  r10, r4
0xC9744  mov   loc_F45E, r5      ; → air-mass signal
```

So **`loc_F45E = (ADC − offset) × gain`** [C]. There is **no HFM characteristic *curve*** in
this path — the hot-film transfer function is folded into the linear gain/offset cals
(`word_302CA2`, `word_302CB4/BA`, `word_302CC0`), which are seeded from page-5/6 calibration in
`sub_C75C2`. **[C]**

> **KFKHFM (`0x138A5`, page 4, axes Upm × %) is applied separately as a multiplicative
> correction, not as the primary linearizer.** It is read at `0x7638E` indexed by `byte_F40E`
> (an rpm-class index, = `nmot/0xA0`, see §3) and `byte_F473` (the load byte), producing a
> correction in `word_3028A8`; and at `0x8A7C4` it multiplies an air-mass value into
> `word_30526C`. **[C]** (Note: the `KRKTE` symbol IDA shows at `0x196FE` is a *different*,
> def-file-mislabeled byte cell — the real injection constant KRKTE is `0x237F2`, §6.)

---

## 3. Engine speed `nmot` (the second map axis)  **[C]**

`sub_98C42` computes `word_F410` = **`nmot`** as frequency/period — confirming
[`ram-names.md`](ram-names.md): `word_F410` is engine speed, **not** load:

```
0x98C4E  mov   r4, word_30190A   ; crank segment period
0x98C52  mov   r5, #0C4B4h       ; constant 0x0004C4B4 = 312500
0x98C56  mov   r2, #4
0x98C60  divlu r4                ; nmot = 0x0004C4B4 / period
0x98C6E  mov   word_F410, r2
```

> **Correction to [`ram-names.md`](ram-names.md):** `byte_F40E` is **not coolant** — it is a
> byte rpm-class index, `byte_F40E = word_F410 / 0xA0` (clamped 0xFF), computed at `0x98C96`
> (`0x98CA2 divu #0A0h`). It is used as the rpm axis for byte-indexed maps (e.g. KFKHFM at
> `0x7638E`). **[C]**

---

## 4. The load model — KFURL + cam-phase blend  (`sub_D2C9A`, z-maps page 9)  **[C]**

`sub_D2C9A` (0xD2C9A–0xD31CA) is the heart of the load calculation. It reads **four page-9
2-D word maps** via the bilinear lookup `sub_41CC0`, all keyed on **X = `word_304E8E`** and
**Y = `word_F410` (nmot)**. Resolving the loaded pointers against the GPHJ dictionary (each
pointer lands a consistent 4 bytes before the named axis block):

| Site | ptr (r12,r13) | physical | Map (dictionary) | → cell |
|---|---|---|---|---|
| 0xD2EA0 | #3476, #9 | 0x27476 | **KFPRGSU** (purge, startup) | `word_302D88` |
| 0xD2EBC | #365E, #9 | 0x2765E | **KFURLSU** (load %/hPa, startup) | `word_305634` |
| 0xD2ED8 | #3382, #9 | 0x27382 | **KFPRG** (purge) | `word_302D86` |
| 0xD2EF8 | #356A, #9 | 0x2756A | **KFURL** (load %/hPa) | `word_305632` |

It then **blends KFURL with KFURLSU** (and KFPRG with KFPRGSU) by the fraction `word_302D80`
(0…0x8000), where `word_302D80` itself is selected from cam-phase / valve-timing cals
(`FWNWVSAP 0x2737C`, `DNWVSMN 0x27374`, plus `0x27380/0x2737E`) — i.e. the load model crossfades
between the normal and the start-up surfaces as a function of camshaft position. The blended
load is PT1-smoothed via `sub_43904` (cal gain `word_27758`, in the **KISRM** region `0x27752`)
and scaled by a manifold-pressure-class term `word_305614`:

```
0xD2EF4  mov   r12, #356Ah          ; KFURL pointer  (phys 0x2756A)
0xD2EF8  mov   r13, #9
0xD2F00  mov   r14, word_304E8E     ; X axis (charge/cam index, see §5)
0xD2F04  mov   r15, word_F410       ; Y axis = nmot
0xD2F08  calls 4, sub_41CC0         ; → KFURL value
0xD2F10  mov   word_305632, r4
…
0xD2F9A  mov   r4, word_305632      ; KFURL
0xD2F9E  mov   r5, word_302D80      ;   × blend fraction
0xD2FA2  mulu  r5, r4
0xD2FB8  add   r4, r7               ;   + (1−frac)·KFURLSU  → word_305636
0xD2FCC  mov   r12, word_27758      ; KISRM-region PT1 gain
0xD2FD0  mov   r13, word_302D82
0xD2FDC  calls 4, sub_43904         ; PT1 integrate → word_300DA4
0xD2FEC  mov   r2, word_305614      ; × pressure-class normalization
0xD2FF4  mulu  r3, r2               ; → word_305646 (base charge)
```

**This is the speed-density core:** `KFURL` is the load-per-pressure (%/hPa) surface, indexed
by an air-charge/cam index and rpm, crossfaded with its start-up variant, smoothed, and scaled
by manifold pressure to yield the base relative charge. **[C for the arithmetic and map
pointers; map *names* by dictionary-pointer match; KFURL "%/hPa" role is the canonical ME7
semantic — I.]**

---

## 5. Load assembly → `rl` output  (`sub_D34DC`)  **[C]**

`sub_D31CA`/`sub_D327E` derive two saturating additive correction words from the §4 results
(`word_302D94 = max(0, word_302D90 − word_302D98)` at 0xD31FA; `word_302D98 = max(0, …)` at
0xD2C8E), and `word_302DA8` (→`word_302DB8`) carries the base charge (written at 0xD3374).
`sub_D34DC` then **assembles the final `rl`** — this is the producer of record:

```
0xD34FC  mov   r1, word_302DA8     ; base relative charge
0xD3500  mov   word_302DB8, r1
…
0xD3522  mov   r12, loc_F47A
0xD3526  mov   r13, word_302DB8    ; rl_base
0xD352A  add   r13, word_302D98    ;   + correction #1   (saturating)
0xD352E  jmpr  cc_NC, loc_D3534
0xD3530  mov   r13, #0FFFFh
0xD3534  mov   loc_F47A, r13       ; *** loc_F47A = rl (primary) ***
0xD3538  cmp   r13, #1FE0h
0xD353C  jmpr  cc_ULE, loc_D3544
0xD353E  movb  byte_F473, ONES     ; clamp byte form to 0xFF
0xD3544  mov   r13, loc_F47A
0xD3548  shr   r13, #5             ; byte_F473 = loc_F47A >> 5  (load byte, 8-bit)
0xD354C  movb  byte_F473, rl1
…
0xD356A  mov   r12, loc_F47A
0xD356E  add   r12, word_302D94    ;   + correction #2   (saturating)
0xD3578  mov   loc_F478, r12       ; *** loc_F478 = rl + offset (= GSHJ rl_w 0xF478) ***
```

So **`loc_F47A = rl_base + Δ1`**, **`byte_F473 = loc_F47A ≫ 5`** (the byte load used by the
byte-map axes), and **`loc_F478 = loc_F47A + Δ2`** (the GSHJ-family `rl_w` cell at 0xF478).
The init/limp path `sub_D35AE` forces `loc_F478 = loc_F47A = 0x10AB`, `byte_F473 = 0x85`. **[C]**

---

## 6. Producer → consumer (the link the docs were missing)

The torque doc's [§2](torque.md) noted `sub_4F4BC` (KFMIOP) locates its operating point with
`sub_40EB0(#582C, loc_F47A)`. That input **is `rl`** computed above — closing the loop from
air signal to the torque model **[C]**:

```
0x4F4C6  mov   r12, #582Ch
0x4F4CA  mov   r13, loc_F47A       ; ← rl from sub_D34DC
0x4F4CE  calls 4, sub_40EB0        ; locate point on KFMIOP load axis
```

And the **inverse constant KRKTE (`0x237F2`, ms/%)** appears on the *fuel* side: `sub_775C8`
turns relative charge into injector time, `ti = (rk × commanded-λ-multiplier) × KRKTE` **[C]**:

```
0x77602  mov   r4, word_237F2      ; KRKTE  (ms per % charge)
0x77606  mulu  r15, r4             ; × charge·λ  → injector pulse
0x77632  add   word_30069C, r4     ; accumulate into ti (32-bit)
```

So the full chain, end to end:

```
A/D (loc_F2DA…)─sub_3FF58─►ADC words─sub_C96FC─► loc_F45E (air-mass signal)
                                                      │  (HFM plausibility: sub_D337C/sub_76A68 → fault bits)
period ─sub_98C42─► word_F410 = nmot ─/0xA0─► byte_F40E (rpm index)
                                                      │
                  X-index word_304E8E (=word_304E96<<2, a charge/cam index, §7)
                                                      ▼
   sub_D2C9A:  KFURL/KFURLSU (%/hPa) × pressure, cam-blended, PT1   ──► base charge
   sub_D31CA/327E: + saturating corrections (Δ1, Δ2)
   sub_D34DC:  ► loc_F47A = rl  ;  byte_F473 = rl>>5  ;  loc_F478 = rl_w
                                                      │
            ┌─────────────────────────────────────────┼───────────────────────────┐
            ▼                       ▼                  ▼              ▼              ▼
   KFMIOP torque (4F4BC)   LDR boost (DBB04)   knock (7BA8C)   thermal (64C80)   fuel×KRKTE (775C8)
```

---

## 7. Open / uncertain

- **`word_304E8E` (the load-map X-axis) is `word_304E96 << 2`** (0x44E04 in `sub_44D70`),
  and `word_304E96 = max(0, word_304E88 − word_304E86)` — a saturated difference of two model
  quantities sourced (via `sub_48786`/`sub_4B12E`, page-7 maps `0x1DB32`/`0x1E338` keyed on
  nmot) from sensor mirrors `word_304F02`/`word_304ECA`. Those mirrors are latched from far
  cal/RAM words (`0x1E454/56`, `0x1DC6C/6E`) under sensor-validity default-substitution flags.
  **The exact physical quantity of `word_304E8E` (an air-charge index vs a throttle-angle/cam
  index) is inferred, not labeled in code [I].** It is the surface index for KFURL together
  with rpm; given KFURL's "%/hPa" output, the pressure itself enters via the `word_305614`
  multiply (§4), which traces to a pressure-class cell `word_30561E`/`word_302D6A` [I].
- **No `air-mass ÷ rpm` (mass-per-stroke) division exists in the 0xD20F0–0xD3220 cluster.**
  The two `divlu` there divide *by the computed load* `loc_F478` (0xD31DC, 0xD320C) — i.e.
  reciprocal scalings of `rl`, not the textbook MAF/rpm. This firmware's primary load is the
  KFURL speed-density path, so the MAF "mass per stroke" step is not on the critical path here.
  **[C that the division is by `loc_F478`; I that there is no MAF/rpm step upstream — not
  exhaustively proven across the whole image.]**
- **Map-name caveat.** KFURL/KFURLSU/KFPRG/KFPRGSU/KFKHFM/KRKTE names come from the GPHJ
  dictionary by pointer-address match; the IDA DB's *own* `KRKTE` label sits on an unrelated
  byte (`0x196FE`) and is wrong (see [`ram-names.md`](ram-names.md) on the def-file layout
  mismatch). Roles are [C] from the arithmetic; the engineering token is dictionary-sourced.
- **FKKVS not separately resolved.** The brief lists FKKVS (fuel-system correction) on the
  air→load path; in this image the fuel-side correction is folded into the KRKTE/λ-multiplier
  chain (`sub_8981C`/`sub_775C8`), and the dictionary's FKKVS block (`0x2355C`) was not seen
  read as a load-path map. Treat FKKVS as a fuel correction, not a load producer, here. **[I]**

---

## 8. Tuner-relevant takeaways (code-confirmed)

- **`rl` is built from KFURL (load %/hPa), not from a MAF transfer curve.** This is a
  speed-density-dominant load path; the HFM/MAF channel (`loc_F45E`) feeds **corrections
  (KFKHFM) and plausibility** (`sub_D337C`/`sub_76A68` set fault bits `word_FD3C.x`/`word_FD7A.x`
  when HFM and the model disagree against `MLDHFMKO 0x16298` / `MLDHFMKU 0x2188A`). Editing the
  MAF scaling alone moves corrections/diagnostics, **not** the base load. **[C]**
- **The load surface is cam-phase-dependent.** KFURL and KFURLSU are crossfaded by valve-timing
  position (`FWNWVSAP`/`DNWVSMN`), so VVT calibration and the load reading are coupled — a
  consideration when changing cam timing or the load model. **[C]**
- **`rl` (`loc_F47A`/`byte_F473`) is the single load variable feeding torque, boost, knock,
  thermal and fuel.** Anything that biases this producer (KFURL, the `word_305614` pressure
  scaling, the additive Δ corrections) propagates everywhere downstream. The boost/torque
  ceilings in [`torque.md`](torque.md)/[`boost.md`](boost.md) clamp the *setpoint* `rlsol`; this
  doc is the *measured* `rl` they are compared against. **[C]**
- **KRKTE (`0x237F2`, ms/%)** is the load↔injection-time constant: `ti = rk·λmult·KRKTE`
  (`sub_775C8`). It is the bidirectional scalar tying charge to fuel. **[C]**
