# Volvo ME7.0 (50GPHJ) — idle-speed governor (Leerlaufregelung / LLR), air side

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Load/rl](load-rl.md) · [Charge](charge.md) · [Cam timing](cam-timing.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [Idle gov](idle-governor.md) · [Limiters](limiters.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

The **air-side idle governor** — the ME7 *Leerlaufregelung* (LLR): how the ECU holds idle rpm by
trimming the cylinder-charge / torque-reserve request that the air path then realises. Read off the
stock 50GPHJ disassembly (Infineon C167CR); addresses cited, `[C]`/`[I]` as elsewhere.

This is **distinct from the idle/startup *spark* reserve `sub_53DEC`** (warm-up/idle/thermal doc §3):
that routine *consumes* the idle state; the function here *produces* it. The two are coupled through
the `word_FD46.9/.10/.15` flag group (see §5).

Legend: **[C]** = read directly from the disassembly; **[I]** = inferred from structure / ME7 convention.

> **Important framing — this is a torque/charge-reserve governor, not a throttle-angle PI.** In this
> bin the air-side LLR does **not** servo a throttle position directly against an rpm error. It runs in
> the **load / torque-reserve domain**: an idle filling/reserve setpoint (indexed by an rpm-class byte
> and engine state) is compared against a reference, the deviation is normalised and conditioned, and
> the result is published as a **reserve/idle-fill quantity** that the torque structure
> ([`torque.md`](torque.md)) turns into airflow (ETC) and that ignition reads for the fast spark path.
> The rpm dependence enters through nmot-(`word_F410`)-keyed maps in `sub_7E36C`, **not** through a
> single `nllsol − nmot` subtraction. Where the brief expected a textbook rpm-error PI, the code
> implements the canonical ME7 *Momenten-LLR* instead — see §6 (open/uncertain).

---

## 1. Entry functions & address ranges

| Function | Range | Role | Evidence |
|---|---|---|---|
| **`sub_7D58E`** | `0x7D58E–0x7E274` (3302 B) | **LLR master / idle state machine + reserve assembly.** Arms/disarms the idle state bits `word_FD46.9..15`; forms the idle error ratio; reads the KFNLL* page-8 maps; assembles the idle-fill/reserve bytes. 39 cal refs, 76 RAM refs, 10 callees. | [C] |
| **`sub_7E36C`** | `0x7E36C–0x7E56E` (514 B) | **Idle reserve shaping vs rpm.** Reads five nmot-(`word_F410`)-keyed 2-D maps (`sub_41CC0`) + a PT1 (`sub_43904`), clamps to `±0x3FFF`, publishes the reserve word `word_305182` / byte `byte_304785`. | [C] |
| `sub_7D48C` | `0x7D48C–0x7D52C` | LLR power-on init: seeds the reserve/counter RAM from cals, computes a battery/voltage-corrected gain `word_305168` (page-0xC2 `byte_30A015/16`). | [C] |
| `sub_7D52C` | `0x7D52C–0x7D58E` | Computes the **setpoint-side** map output `word_305174` (`sub_42464` on cal `0x21FD2`/desc `0x1FD3` indexed by `byte_304979`) + two more idle terms (`word_30158C`, `byte_30158F`). | [C] |
| `sub_7CADE` | `0x7CADE–0x7CC7C` | Idle **base load** path: nmot-keyed 2-D maps (`sub_41CC0` @ `0x1C5E`/`0x1D02`) × a fuel/temp byte → working load `word_3028E2`, default `0x1000` (=1.0). | [C] |
| `sub_7CA5E` | `0x7CA5E–0x7CADE` | Idle load **upper clamp**: reads map `0x21B0A` (`sub_42688`), clamps `word_3028E2`→`word_3028E4` (default `0x1000` when LLR off). | [C] |
| `sub_7E274` | `0x7E274–0x7E2F8` | Idle **dashpot / decel-fill** down-counter (`sub_42CF4` slew on cal `0x162CC`) → `byte_301585`. | [C] |

All seven sit in one contiguous code cluster (`0x7CA5E–0x7E56E`) on the shared idle RAM band
`word_3028Exx / word_30516x–305180s / byte_30157F–30159x`. **[C]**

---

## 2. Scheduling / callers

- `sub_7CC7C` (`0x7CC7C`, the IAT-spark-correction `byte_30157C` writer — *not* LLR proper) and
  `sub_7CE76` (`0x7CE76`, knock-window/idle-spark sub-state) are scheduled **directly by the main
  periodic task `sub_B81C`** (callgraph: `0x0B81C → 0x7CC7C`, `0x0B81C → 0x7CE76`). **[C]**
- The LLR workers **`sub_7D58E` and `sub_7E36C` have `callers=0`** in the callgraph, with full
  prologue/epilogue and 76/—RAM refs → **dispatched through the RTOS process table**, exactly like the
  documented thermal model `sub_64C80`. **[C]** structure; **[I]** that the dispatcher is the process table.
- They run as a chain: the setpoint/init helpers (`sub_7D48C`, `sub_7D52C`, `sub_7CADE`, `sub_7CA5E`)
  feed the shared RAM that `sub_7D58E` then consumes; `sub_7E36C` reads `sub_7D58E`'s state bits
  (`word_FD46.9/.14`) and reserve byte (`byte_301586`). **[C]**

---

## 3. Calibration maps & RAM cells

### 3a. Page-8 LLR calibration band (KFNLL* family, ~`0x21Bxx–0x22010`)

The map data lives in page 8; the code reads it with the interp helpers and **descriptor/axis bytes**
that the dump shows inline. The lead cal **`KFNLLKHM` @ `0x21EFC`** is **confirmed referenced** as a
2-D map z-block at `0x7DF18` (`mov r4, #1EFCh`, paired with axis-ptr byte `0x21EEA/0x21EEB` and
descriptor `0x1EF4`, read via `sub_425E8`, indexed by the idle rpm-class byte `byte_30163A`). **[C]**

| CAL (phys) | How read | Role | Conf |
|---|---|---|---|
| `0x21EFC` (**KFNLLKHM**) | `sub_425E8`, desc `0x1EF4/0x1EFC`, axis `0x21EEA/EB`, idx `byte_30163A` (0x7DF18) | idle-fill / reserve **map vs rpm-class & engine-state** | [C] read; **KFNLLKHM** name [I] from brief + position |
| `0x21EB8/0x21EB9` (+`0x1EBA`,`0x1EC2`,`0x1ECA`) | `sub_425E8` (0x7DED2, 0x7DF90) | reserve sub-map A (engaged-clutch branch) | [C] |
| `0x21F1C/0x21F1D` (+`0x1F1E`,`0x1F2E`,`0x1F36`) | `sub_42638` (0x7E16A) | reserve sub-map (2nd output, `byte_304782`) | [C] |
| `0x21F76/0x21F77` (+`0x1F78`,`0x1F88`,`0x1F90`) | `sub_42638` (0x7E1EA) | reserve sub-map (3rd output, `byte_304783`) | [C] |
| `0x21FD2` (desc `0x1FD3`,`0x1FE0`) | `sub_42464`, idx `byte_304979` (0x7D546) | **setpoint-side** idle term → `word_305174` | [C] |
| `0x21E2A` (desc `0x1E2C`) | `sub_4272A` (0x7D74C) | idle actual/normaliser term | [C] |
| `0x21FF8` | direct word (0x7D7D2, 0x7D7FC) | idle-fill enable/scale (gates `word_305170`) | [C] |
| `0x21EA6` | direct word (0x7D492) | init value for `word_3028F6` (reserve rate limit) | [C] |
| `0x21EA8`, `0x21E3E` | `cmp` (0x7D9AE, 0x7D9DE) | idle error / deviation thresholds (state arming) | [C] |
| `0x21DCA/0x21DCB` | `sub_42596` (0x7CCFC) | (in `sub_7CC7C` — IAT spark corr `byte_30157C`, adjacent not LLR) | [C] |
| `0x2024,0x2058,0x208C,0x20C0,0x2164` | `sub_41CC0`, axis `word_F410` (sub_7E36C) | **nmot-keyed reserve-vs-rpm maps** (the rpm dependence) | [C] |
| `0x2200A,0x2200C,0x2200E,0x22010` | `cmp` vs `word_302D70` | **after-start TIMER thresholds** gating LLR sub-modes | [C] |
| `0x22004,0x22006,0x22008` | `cmp`/load | idle debounce / hold counters | [C] |
| page-6 `FSTTAL 0x196FA`, `FSTTEW 0x196FC`, `FSTDMN 0x196F8`, `FSTDMX 0x196F9`, `DLAMOB 0x196FF`, `KRKTE 0x196FE`, `CWPKAPP 0x196FD`, `0x196C8–0x196CE`, `0x19700/01` | direct (sub_7D58E) | start/idle **FST*** config + idle limit/enable bytes | [C] names (IDA-resolved); roles [I] |
| page-0xD `0x4764/0x476B` (idx `byte_30163A/301626`) | `sub_40B3E` result vs `byte_F40E` (sub_D22B6) | **rpm-class gate** (`byte_F40E` = nmot/0xA0, **not** coolant — see [`ram-names.md`](ram-names.md)) → sets `word_FD7A.14/.15` | [C] |

> The `FST*`, `KRKTE`, `DLAMOB`, `CWPKAPP` cells at `0x196F7–0x196FF` are **IDA-resolved engineering
> names present in the dump** (start/idle group). `KFNLLKHM` at `0x21EFC` is **not** named in the DB
> (consistent with [`ram-names.md`](ram-names.md): no names on this band); the label is the brief's,
> matched to the confirmed read site.

### 3b. Idle-governor RAM (working variables)

| RAM cell | Role | Conf |
|---|---|---|
| `byte_30163A` | **idle rpm-class index** (nmot binned; written by `sub_93F2C`/`sub_945C2`/`sub_966F6`); axis into KFNLL* | [C] role; [I] "rpm-class" identity |
| `byte_304979` | **idle setpoint-class index** (= `byte_30163A` or `byte_304976`, gated by `word_FD52.11`, in `sub_966F6`) | [C] |
| `word_305174` | idle **setpoint side** of the error (`sub_7D52C`, from KFNLL setpoint map) | [C] |
| `word_305170` | idle **actual side** (charge/fill, from `0x21FF8`/`sub_E40DE` chain) | [C] |
| `word_305176` | **idle deviation** = `word_305174 − word_305170`, floored at 0 (0x7D95A–0x7D972) | [C] |
| `word_305172` | error **normaliser/divisor** = `word_304F70` (a charge ref from thermal model `sub_64C80`) | [C] |
| `word_3028F8` / `word_30517C` / `byte_301587` | **normalised idle deviation** = `word_305172 / word_305176` via `divlu` (reference ÷ deviation, 0x7DBE0); `>>8` byte. Used as the *axis index* into the idle reserve maps `0x1E62/0x1E84` | [C] |
| `byte_301582` | idle **integral-ish counter / fill state**, slewed by `sub_42CF4` (0x7DB32) toward `word_302900`; the multiplicative term in all reserve products | [C] role; [I] "integral" label |
| `byte_301583` | idle ramp/decay state (`sub_42C1C` on cal `0x2200E`, 0x7DD2C) | [C] |
| `byte_301586` | **idle-fill output** = `byte_301582 × min(map(0x1E62/0x1E84), word_3028F6) >> 8` (0x7DCC4) | [C] |
| `byte_301584` | idle reserve from map `0x1E40` × `byte_301582` (0x7E0FC) | [C] |
| `byte_304782/304783` | reserve sub-outputs (clutch-engaged / -open branches) from the `0x21F1C/0x21F76` maps | [C] |
| `byte_301588/301589` | final clamped reserve pair (`FSTDMN`/`FSTDMX` clamps, 0x7DFD4–0x7E00A) | [C] |
| `word_305182` / `byte_304785` | **published idle torque/load reserve** (`sub_7E36C` out) → torque & ignition | [C] |
| `word_305180`, `word_305184` | reserve PT1 output / alt-map clamp companion (`sub_7E36C`) | [C] |
| `word_3028E2/3028E4` | idle base load / clamped (`sub_7CADE`/`sub_7CA5E`); `word_3028E0=0x1000` | [C] |
| `byte_301585` | idle **dashpot/decel** value (`sub_7E274`) | [C] |
| `byte_301580/301581/301590/301591` | **idle state-bit bytes** (enable/branch/limit/debounce flags throughout `sub_7D58E`) | [C] |
| `word_302D70` | **after-start timer** (free-running counter, `sub_D22B6`) gating LLR modes | [C] |
| `word_FD46.9` | **LLR-active flag** — *set/cleared ONLY here* (0x7DC58 `bclr` / 0x7DC66 `bset`) | [C] |
| `word_FD46.10/.11/.12/.13/.14/.15` | idle sub-state bits (idle-confirmed / windup / ramp / etc.) published by `sub_7D58E` | [C] |
| gain cals: `byte_196C8` (0x7D7AA), `USMNSHMN 0x19715` (PT1 gain, sub_7E36C 0x7E44E/88), `word_30518A` (reserve scale) | — | idle-loop gains | [C] |

---

## 4. Quoted disasm — the idle deviation, its normalisation, and the reserve assembly

From `sub_7D58E`. (i) the deviation `setpoint − actual` floored at 0; (ii) the `divlu` that turns the
charge reference and the deviation into an axis index; (iii) the fill state slewed by `sub_42CF4`;
(iv) the reserve product `byte_301586 = fill_state × min(idle-map[deviation], rate-limit)`:

```
; (i) idle deviation = word_305174 (setpoint side) - word_305170 (actual), floored at 0
0x7D95E  mov     r4, word_305174        ; idle setpoint-side term (KFNLL setpoint map, sub_7D52C)
0x7D966  sub     r4, word_305170        ; - actual idle-fill/charge
0x7D96A  jmpr    cc_NC, loc_7D96E
0x7D96C  mov     r4, #0                 ; clamp negative -> 0
0x7D972  mov     word_305176, r4        ; -> idle deviation
 ...
; (ii) normalise: divide the charge reference word_305172 (= word_304F70, thermal model) by deviation
0x7DBCA  mov     r4, word_305176        ; idle deviation -> DIVISOR
0x7DBD4  mov     r2, word_305172        ; charge reference -> dividend (MDH:MDL = ref:0)
0x7DBD8  mov     MDH, r2
0x7DBE0  divlu   r4                     ; (word_305172 << 16) / word_305176  = reference / deviation
0x7DBEE  mov     word_3028F8, r3        ; -> normalised idle term (axis index into reserve maps)
0x7DC00  movb    byte_301587, rl4       ;   >>8 byte form
 ...
; (iii) idle fill/integral state byte_301582 slewed toward word_302900 (rate-limited by sub_42CF4)
0x7DB32  movbz   r12, byte_19702        ; CAL->0x19702  (slew rate)
0x7DB3A  mov     r14, word_302900
0x7DB3E  calls   4, sub_42CF4           ; ramp toward target
 ...
; (iv) reserve product: fill_state x min( idle map(0x1E62/0x1E84 vs word_3028F8), rate-limit )
0x7DCB4  calls   4, sub_41A68           ; idle map @0x1E84 indexed by word_3028F8 (norm. deviation)
0x7DCBA  cmp     r8, word_3028F6        ; vs reserve rate-limit
0x7DCC0  mov     r8, word_3028F6        ;   min()
0x7DCC4  movbz   r4, byte_301582        ; idle fill/integral state
0x7DCC8  mulu    r4, r8                 ; reserve = state x conditioned-deviation
0x7DCD4  movb    byte_301586, rl4       ; -> idle-fill / reserve byte
```

The published reserve is then formed and gated in `sub_7E36C` (rpm-shaped, PT1-smoothed, clamped):

```
0x7E472  mov     r14, word_F410         ; nmot (engine speed) — the rpm dependence
0x7E47E  calls   4, sub_41CC0           ; 2-D map @0x20C0 (nmot x word_305188)
0x7E488  movbz   r12, USMNSHMN          ; CAL->0x19715  (PT1 gain)
0x7E496  calls   4, sub_43904           ; PT1: state += gain*(map - state)  -> word_300706/8
 ...
0x7E4B2  movbz   r12, byte_301586       ; idle-fill reserve (from sub_7D58E)
0x7E4B6  mulu    r12, r8                ;  x rpm-shaped term
0x7E4E2  sub     r8, #0FFFFh
0x7E4E6  subc    r14, #3FFFh            ; clamp to +/-0x3FFF
0x7E540  mov     word_305182, r12       ; -> PUBLISHED idle torque/load reserve
0x7E566  movb    byte_304785, rl1       ;    (>>8 byte form)
```

---

## 5. Relation to the spark reserve (`sub_53DEC`) and the torque/air path

The air-side LLR is the **producer** of the shared idle state, and three already-documented
subsystems are its **consumers** — this is how "the controller drives the air path" is realised in
ME7's torque structure rather than by a direct throttle servo:

- **Idle state flags.** `sub_7D58E` is the **only** writer of `word_FD46.9` (`bclr` 0x7DC58 / `bset`
  0x7DC66) and also publishes `word_FD46.10/.11/.12/.13/.14/.15` (0x7DB16–0x7E0BA). **[C]** The
  spark-side idle/startup reserve **`sub_53DEC`** (warm-up/idle/thermal §3) *reads* exactly these:
  `word_FD46.10` (0x53DFE), `word_FD46.15` (0x53E0E), `word_FD46.9` (0x53F6C, 0x5445A…). So the air
  governor **arms the idle condition; the spark reserve reacts to it** — the coupling that doc hinted
  at, now traced to its source. **[C]**
- **Torque path (air realisation).** `sub_4F0CE` (`0x4F0F0`) takes the published reserve
  `word_305182` as a torque-demand candidate, min-clamps it against the torque-model cells
  (`word_30526C`, `0x31E4D6`, `0x31EE3A`) and folds it into the indicated-torque request
  `0x31DADA/31DADE`. That request flows through **KFMIRL (`sub_4F97A`) → `rlsol` (`word_31E484`) →
  LDR / ETC** ([`torque.md`](torque.md)). So the idle reserve becomes a **load/airflow** demand. **[C]**
- **Fast spark path.** `sub_51658` (`0x5168C`) reads the same `word_305182`; above cal `0x1EEA6` it
  selects a page-7 ignition map (`byte_1EE7E`, idx `byte_30163A`) into `word_304F42` — the idle
  ignition torque-reserve trim, parallel to `sub_53DEC`. **[C]**

Plain description: at idle the ECU bins engine speed into an rpm-class index (`byte_30163A`), looks up
an idle-fill / reserve target from the page-8 KFNLL* maps (incl. **KFNLLKHM @ 0x21EFC**) and a
temperature/after-start–gated setpoint term (`word_305174`), and forms a deviation against an actual
charge estimate. That deviation is normalised by a charge reference (`divlu`, → `word_3028F8`), used to
condition a slew-limited idle-fill state (`byte_301582`/`byte_301586`), then shaped against
nmot-indexed maps and a PT1 in `sub_7E36C` into a single **idle torque/load reserve** `word_305182`.
The reserve is published to the torque structure (which converts it to throttle/airflow) and to the
ignition path, while `sub_7D58E` simultaneously arms the `word_FD46.9..15` idle state that the
spark-side reserve `sub_53DEC` consumes. It is a **torque/charge-reserve idle governor** (ME7
*Momenten-LLR*), gated by an after-start timer (`word_302D70` vs `0x2200A…0x22010`) and warm/cold
coolant state (`word_FD7A.14/.15`).

---

## 6. Open / uncertain

- **No single `nllsol − nmot` rpm-error PI exists in this bin.** The closest thing is the load-domain
  deviation `word_305176 = word_305174(setpoint) − word_305170(actual)` (§4) plus the nmot-keyed
  reserve maps in `sub_7E36C`. The "P" and "I" of the loop are spread across the slew-limited fill
  state `byte_301582`, the `divlu`-normalised deviation, and the map-shaped reserve — not a clean
  `state += gain·(nmot_set − nmot)` integrator. If the brief's expectation was a discrete rpm PI, the
  finding is: **this ME7 implements idle governing as a torque/air-reserve scheme instead.** **[C]
  absence of the subtraction; [I] the architectural interpretation.**
- **`KFNLLKHM` label.** The read site at `0x7DF18` (z=`0x21EFC`) is confirmed; the *name* is the
  brief's lead matched to position, not a DB symbol (this band carries no engineering names — cf.
  [`ram-names.md`](ram-names.md)). Treat the **address as authoritative, the name as plausible**.
- **`byte_30163A` / `byte_304979` as "rpm-class".** Confirmed as the axis indices into the idle maps
  and confirmed written in the `sub_93F2C`/`sub_945C2`/`sub_966F6` air-mapping block, but their exact
  scaling (rpm bin vs operating-point class) is **[I]**.
- **`word_305172` = `word_304F70`** is confirmed sourced from the thermal model `sub_64C80` (one of its
  PT1 outputs, 0x64D7A) and used as the idle-deviation normaliser; its precise physical meaning
  (charge reference vs modelled load) is **[I]**.
- **`sub_7E36C`'s `word_305188`** (a second map axis paired with nmot) comes from `word_30243C` /
  `word_3024EA` (0x7E37A–0x7E3C0) — likely a measured-vs-target load or a pedal/throttle term; not
  pinned. **Open.**
- Dispatch of `sub_7D58E`/`sub_7E36C` is **[I]** the RTOS process table (callers=0, full frame),
  by analogy to `sub_64C80`; the process-table slot was not located.
