# Volvo ME7.0 (50GPHJ) — RAM-variable → ME7 name → meaning

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

Engineering names for the RAM/CAL cells referenced throughout [`ALGORITHM.md`](ALGORITHM.md) and the
subsystem docs ([`boost.md`](boost.md), [`ignition.md`](ignition.md), [`fueling.md`](fueling.md), [`torque.md`](torque.md), [`lookup.md`](lookup.md)), so the
algorithm reads in real ME7 terms instead of `word_XXXXX`.

## How the bindings were sourced (read this first)

Four name sources were cross-referenced. Their reliability for **our** bin
(`car/bins/me7_stock.bin`, family 50GPHJ) turned out to be very uneven:

| Source | What it is | Reliability for our bin |
|---|---|---|
| **The disassembly** (IDA DB `me7_stock_torque.i64`) + the subsystem docs | code-confirmed arithmetic/data-flow | **authoritative for ROLE**; gives no text names |
| **`reference/gshj/ECUParametersGSHJ.xml`** + `39357-50GSHJ.xdf` | 50GSHJ sibling family: friendly names + addresses + map names | **best name source.** Map *names/meanings* (KFLDRX, KFLDIMX, KFLDRL, KFZW1-4, LAMFA, KFMIRL/OP) match our family. RAM *addresses* are a different bin → treat as corroboration, not byte-exact |
| **`reference/gphj/VolvoME7def.txt`** | a Volvo ME7 symbol/desc/addr list | **different calibration layout** than our bin. Of all the doc CAL cells, only `0x19B5A` matches byte-exact. Use only to confirm the ME7 *vocabulary* exists |
| **`tuner-tools-r2/1xEbvsde.a2l`** | a foreign ME7 A2L | **address cross-check is invalid** — every doc RAM address resolves to nonsense (`fln*` learning filters, `B_*uvwdk` fault paths). Use only as a name dictionary |

**Two facts that changed the picture:**

1. **The IDA DB has NO engineering names on any of these RAM cells.** All 122 queried
   addresses came back as auto-generated `word_/byte_/loc_`. The "VolvoME7def.txt symbols
   were imported" note is only true for the **CAL band** (e.g. `0x110BA=DPWMAP`,
   `0x1135C=KFPED`), and those def addresses are for a *different* layout, so they do **not**
   land on the doc's CAL cells. Net: names below are derived from **code role + GSHJ
   names + ME7 convention**, not from a pre-existing symbol import.

2. **`0x19B5A` is `DTXKS3`, not KFLBTS.** It is the only doc CAL address present byte-exact
   in `VolvoME7def.txt` (`DTXKS3 "" 0x19B5A`) and it is also the name IDA shows at that
   address in our DB. [`fueling.md`](fueling.md) already hedged this binding as inferred — confirmed wrong:
   KFLBTS is reached via the page-6 protection-lookup descriptors, `0x19B5A` itself is a
   knock-related cell (DTXKS = knock-sensor test threshold class).

Confidence legend: **[CONFIRMED]** = role read directly from the instruction stream (the
disassembly proves what the cell does); **[NAME-XDF]** = ME7 name corroborated by the GSHJ
XML/XDF for a sibling bin; **[INFERRED]** = name assigned from ME7 convention + role only.

---

## ⚠️ Correction: `word_F410` is `nmot_w` (engine speed), NOT `rl`

`ALGORITHM.md §1`, [`boost.md`](boost.md), and [`torque.md`](torque.md) treat `word_F410` as the measured relative
charge `rl`. **The evidence says it is engine speed `nmot_w`:**

- `ECUParametersGSHJ.xml` maps `0xF410 → nmot_w "Engine Speed", factor 0.25, RPM`. The
  sibling family puts **rl/actual-load at `0xF478` (`rl_w`)**, a *different* cell.
- In `sub_4F97A` (KFMIRL) the very first thing the code does (0x4F984–0x4F98C) is
  `cmp word_F410, word_1584E` → set/clear a flag with a debounce timer — the canonical
  **engine-running / min-rpm detection** gate, which operates on **rpm**, not load.
- The boost term `word_2BE38(gain) × word_F410` (`sub_DBB04` 0xDBB14) is then an
  **rpm-scaled** feed-forward/precontrol term — standard in ME7 LDR (precontrol vs rpm).

So everywhere the docs say "`word_F410` = measured relative charge `rl_w`", read it as
**`nmot_w` (engine speed, 0.25 rpm/count)**. The genuine `rl_w` (actual load) is a separate
cell (GSHJ `0xF478`); our docs did not pin its address in this bin. This does not break the
boost/torque *structure* (the math is unchanged) — only the variable label. **[NAME-XDF +
CONFIRMED code role]**

---

## 1. Torque / load structure (torque.md)

| RAM cell | ME7 name | Meaning | Source / confidence |
|---|---|---|---|
| `word_31E484` (0xA484) | **rlsol_w** | relative-load **setpoint** (the load request fed to LDR boost) | role CONFIRMED (`sub_4F97A` output); name [NAME-XDF] (GSHJ `rlsol_w` "Requested Load", scale 0.0234375 %/ct) + [INFERRED] addr |
| `word_31E482` (0xA482) | rlsol pre-clamp | rlsol before ×2 / final store | CONFIRMED role; INFERRED name |
| `word_304F30` | rlsol PT1 history | smoothed previous rlsol (0.5/0.5 average) | CONFIRMED role; INFERRED name |
| `word_31E480` (0xA480) | **drlsol_w** | rlsol error / load deviation (setpoint − feed-forward) | CONFIRMED role; [NAME-XDF/A2L vocab] |
| `word_31E47C` (0xA47C) | rlsol I-part | integral component (MAC integrator `sub_42DF4`) | CONFIRMED role; INFERRED name |
| `word_31E47E` (0xA47E) | rlsol P-part | proportional component | CONFIRMED role; INFERRED name |
| `word_31E48A` (0xA48A) | rlmax-clamped load | candidate load after boost-ceiling clamp (§3b) | CONFIRMED role; INFERRED name |
| `word_31E486` (0xA486) | rl working value | running relative-load working register | CONFIRMED role; INFERRED name |
| `word_31E488` (0xA488) | rl feed-forward | precontrol load = rl + reserve term | CONFIRMED role; INFERRED name |
| `word_31C200` | rlmax slew | slewed upper load ceiling | CONFIRMED role; INFERRED name |
| `word_31DAEC` | **miopt_w** | optimum indicated torque (KFMIOP output) | CONFIRMED role (`sub_4F4BC`); name [NAME-XDF] (GSHJ `miopt_w` "Optimum Indicated Torque") |
| `byte_31D303`/`byte_31D302` | mi efficiency corr / per-cyl avg | torque byte corrections (5-cyl `divu #5`) | CONFIRMED role; INFERRED name |
| `word_302968` | **rk_w / mibas** load-or-fuel-mass term | torque/load request input to boost (`sub_DBB04`) AND base rel. fuel mass rk (`sub_775C8`) | CONFIRMED role; INFERRED name (dual use) |
| `byte_304E27` | load-class index | engine-load axis index into LAMFA/KFMIRL maps | CONFIRMED role; INFERRED name |

CAL z-blocks (these are map *data*, names confirmed by GSHJ XDF titles, addresses are this
bin's file offsets, **[INFERRED addr / NAME-XDF]**): KFPED z=`0x1E776`, KFMIOP z=`0x156CC`,
KFMIRL z=`0x158A4`. KFMIRL limit/ramp cals `word_1584E`(default rl), `word_15858`(max rl),
`word_15852/54/56/5A` (rlmax ceilings — the boost-limit clamp stack).

---

## 2. Boost control / LDR (boost.md)

### 2a. Calibration cells (page 0xA boost-cal band 0x2BExx/0x2BFxx)

The GSHJ XDF confirms the **map family names** (KFLDRX "Maximum cylinder charge",
KFLDIMX "LDR I-Regulator limit", KFLDRL "linearise charge pressure vs duty cycle",
KFLDHBN "altitude/compressor-ratio limit"). Addresses below are this bin's; they do **not**
match the GSHJ/def addresses (different layout) — so the family is **[NAME-XDF]**, the
specific cell role is **[CONFIRMED]** from how `sub_DBB04`/`sub_DBF44` read it.

| CAL cell | ME7 name | Meaning | Confidence |
|---|---|---|---|
| `word_2BE38` | LDR precontrol gain | rpm-scaled feed-forward gain (× `word_F410`) | CONFIRMED role |
| `word_2BE92` (map) | KFLDIMX-region map | conditional setpoint add term | CONFIRMED reader |
| `word_2BF32` | **KFLDIMX** I-gain/limit | boost I-term integrator gain & limit | CONFIRMED role + [NAME-XDF] |
| `word_2BE3A` (map) | KFLDRX P-gain source | error→P-gain lookup | CONFIRMED reader; [NAME-XDF] |
| `word_2BE74` (table) | LDR P-shaping table | signed table shaping P-term | CONFIRMED reader |
| `word_2BF2E`/`word_2BF30` | 2nd-loop scale / I-gain | derivative/pilot path scale & gain | CONFIRMED role |
| `word_2BE56` (table) | LDR 2nd-term shape table | signed shaping of 2nd term | CONFIRMED reader |
| `word_2BECA` (2-D map) | **KFLDRX** feed-forward | base WG duty vs (setpoint, rpm-ref) | CONFIRMED reader + [NAME-XDF] |
| `word_2BEAC` (map) | **KFLDRL** linearization | wastegate-duty vs deviation linearization | CONFIRMED reader + [NAME-XDF] |
| `word_2BF4A` (=0x0FFA) | **KFLDIMX threshold** | enable/authority gate (`sub_DBF44`) | CONFIRMED + [NAME-XDF] |
| `word_2BF4C` (=0x00F0) | KFLDIMX margin | overrun-compare offset | CONFIRMED |
| `word_2BF4E` (=0x2E15) | **WG duty MIN** | wastegate duty min clamp (ldtvm floor) | CONFIRMED |
| `word_2BF50` (=0xD99A) | **WG duty MAX** | wastegate duty max clamp (ldtvm ceiling) | CONFIRMED |
| `word_2BF48` (=0x1770=6000) | over-boost RPM trip | high-rpm/over-boost shutdown threshold (`sub_DC31A`) | CONFIRMED |
| `byte_2BF34` (=0x06) | LDR duty scale idx | actuator scale-table index | CONFIRMED |
| `byte_1BE46` (=0x07) | LDR master enable | config/enable bitfield (bit0 gates closed loop) | CONFIRMED |
| `byte_1BE47`/`byte_1BE48` | LDR aux config | anti-windup / over-boost gating bytes | CONFIRMED role |
| `byte_1BE69` (=0x10) | LDR debounce count | enable debounce | CONFIRMED |

### 2b. RAM cells (working variables of the LDR loop)

| RAM cell | ME7 name | Meaning | Confidence |
|---|---|---|---|
| `word_302E62` | **plsol / ldsol setpoint** | combined boost-control **setpoint** (request + map term) | CONFIRMED (computed). GSHJ has `plsol_w` "Desired Boost"; this cell = internal load-domain setpoint |
| `word_302E58` | LDR actual ratio | normalized **actual** boost/load ratio `(word_302496<<11)/word_30294A` | CONFIRMED |
| `word_302496` | rl-actual numerator | measured load/boost quantity (ratio numerator) | CONFIRMED role; INFERRED name |
| `word_30294A` | normalizing reference | divisor (ambient/throttle reference pressure) | CONFIRMED role; INFERRED name |
| `word_302E60` | **ldtvm-demand (final)** | FINAL LDR demand → output stage | CONFIRMED |
| `word_302E5E` | feed-forward+PI demand | base duty + PI correction (pre-KFLDRL) | CONFIRMED |
| `word_302E64`/`word_302E66` | setpoint parts A/B | request-scaled / KFLDIMX-map components | CONFIRMED |
| `word_302E52`/`word_302E5C` | **ldrkp_w** P raw / P shaped | proportional term raw and table-shaped | CONFIRMED role; GSHJ has `ldrkp_w` "BoostPID-P-Portion" [NAME-XDF] |
| `word_302E5A`/`word_302E50` | 2nd-term shaped / raw | derivative/pilot contribution | CONFIRMED |
| `word_302E68:6A` | **lditv_w** I-state (32-bit) | KFLDIMX-limited integrator state | CONFIRMED role; GSHJ `lditv_w` "BoostPID-I-Result" [NAME-XDF] |
| `word_302E70:72` | 2nd integrator state (32-bit) | pilot/derivative integrator | CONFIRMED |
| `word_302E54`/`word_302E56` | KFLDRL linearized / deviation | wastegate linearization term & its input | CONFIRMED |
| `word_302E34` | I-limit compare quantity | gated against KFLDIMX threshold `word_2BF4A` | CONFIRMED |
| `word_302E38` | boost actual (limiter) | actual boost used by limiter/over-boost trip | CONFIRMED |
| `word_302E3C`/`word_302E3E` | actual / reference (2nd loop) | inputs to 2nd term and overrun compare | CONFIRMED |
| `word_302E4A` | duty offset | offset added before final duty scale | CONFIRMED |
| `word_302E7C` | **ldtvm** scaled duty | scaled wastegate duty (pre-clamp) | CONFIRMED role; GSHJ `ldtvm` "Boost Controller Duty Cycle" [NAME-XDF] |
| `word_302E7E` | ldtvm clamped duty | deliverable duty (clamped MIN/MAX) | CONFIRMED |
| `word_30BF0A` | LDR adaptive trim | learned/adaptive offset (page 0xC2) | CONFIRMED |
| `byte_301867/68/69/6F` | LDR state bits | enable/limit/mode/windup flags | CONFIRMED |
| `byte_301870.0` | wastegate solenoid bit | final LDR solenoid command | CONFIRMED |

> Confirms the tuning takeaway: `word_2BF4A` (KFLDIMX threshold) is the enable+authority
> gate and `word_2BF32` (KFLDIMX) is the I-limit; `word_2BF4E/50` hard-clamp wastegate duty;
> `word_2BF48`=6000 is the over-boost rpm cut. **[CONFIRMED]**

---

## 3. Ignition & knock (ignition.md)

Timing cells are **SBYTE, 0.75°/count**. GSHJ XDF confirms KFZW1-4 names ("Target ignition
angle with min/max intake/exhaust cam adjustment"). GSHJ XML confirms the output cell names.

| RAM/CAL cell | ME7 name | Meaning | Confidence |
|---|---|---|---|
| `byte_30132E` | **zwbas / base advance** | base ignition advance (pre-knock), post KFZW blend + offsets | CONFIRMED |
| `byte_30132F` | zwbas (interp) | interpolated base advance before adding cal offsets | CONFIRMED |
| `byte_30157C` | **dzwtans / IAT corr** | IAT/temperature ignition correction (additive) | CONFIRMED role + [INFERRED name] |
| `byte_3014F6` | dzw correction | additional additive correction term | CONFIRMED role; INFERRED |
| `byte_12D85` | dzw cal const | flat cal-byte correction | CONFIRMED |
| `byte_F3FA` | **wkr / dwkr global retard** | GLOBAL knock retard (subtracted from advance) | CONFIRMED. NB GSHJ `wkrm "Average Knock Retard"` @`0xF3F8` — `0xF3FA` is the live global retard adjacent to it |
| `0x30B24C[cyl]` | **dwkrz[cyl]** | per-cylinder knock-retard accumulator (5 entries) | CONFIRMED. GSHJ exposes `dwkrz_0..4 "Cyl N Knock Retard"` |
| `0x309545[cyl]` | per-cyl knock offset | per-cylinder retard offset applied in spark sum | CONFIRMED role; INFERRED name |
| `byte_301571`/`byte_301572` | KR step / KR map-amount | components summed into `byte_F3FA` | CONFIRMED |
| `word_3019B6`/`word_3019CA` | **nmot-idx / rl-idx** | RPM / LOAD axis index+fraction words for KFZW lookups | CONFIRMED read-only role; axis identity [INFERRED] |
| `byte_30129C`/`byte_30129B` | **wnwise / wnwisa frac** | intake / exhaust cam-phase blend fractions f1/f2 | CONFIRMED role; cam identity [NAME-XDF] (GSHJ `wnwise_w`/`wnwisa_w`) |
| `word_3024A8/AA/AC` | KFZW12 / KFZW34 / blend | intermediate KFZW blend results | CONFIRMED |
| `byte_30132E` → out | (see above) | — | — |
| `0x309317[cyl]` / `0x309313[cyl]` | **zwout** array out / advance in | emitted per-cyl spark advance (`sub_50984`) | CONFIRMED. GSHJ `zwout "Ignition Angle Output"` @`0xF33A`, `zwist` @`0xF338` |
| `byte_F337`/`byte_F338`/`loc_F33A` | zw / zwist / zwout (live) | per-cyl spark store / actual / output | CONFIRMED role; [NAME-XDF] |
| `byte_30125D` | cylinder index | current firing cylinder 0..4 | CONFIRMED |
| `0x19B5A` | **DTXKS3** (NOT KFLBTS) | knock-sensor test-threshold-class cal (def-confirmed) | CONFIRMED via VolvoME7def.txt |

KFZW1-4 z-blocks (this bin): `0x133B1 / 0x13471 / 0x13531 / 0x135F1` (sbyte) **[NAME-XDF]**.
Knock-control cal set `0x139B6..0x139BD` (`sub_7BD04`): step-up `0x139B7`, max `0x139B6`,
min `0x139B9`, recovery step `0x139B8`, recovery period `0x139BA`, ratio thresholds
`0x139BB/BC`, RPM-enable `0x139BD`. **[CONFIRMED roles]**

---

## 4. Fueling / lambda (fueling.md)

GSHJ XDF/XML confirm LAMFA "Driver requested Lambda" (`lamfa_w`), KFLBTS "Lambda for
component protection" (`lambts_w`). Lambda word scale ≈ 1/128 internal; GSHJ logged lambdas
use 0.000244140625 (1/4096).

| RAM/CAL cell | ME7 name | Meaning | Confidence |
|---|---|---|---|
| `word_3029A4` | **lamfa_w** | driver-requested lambda (LAMFA result) | CONFIRMED role (`sub_894C0`); name [NAME-XDF] (GSHJ `lamfa_w "Lambda LAMFAW Value"`) |
| `word_305268` | LAMFA aux | secondary LAMFA-family lookup result | CONFIRMED |
| `word_3029A6` | LAMFA offset term | additive lambda offset | CONFIRMED |
| `word_30297C` | **fkkvs / commanded fuel multiplier** | commanded fuel/lambda multiplier feeding injection (`sub_8981C`→`sub_775C8`) | CONFIRMED |
| `word_30297A` | corrected lambda factor | closed-loop-corrected lambda/fuel factor | CONFIRMED |
| `word_302998` | lambda + offsets | combined commanded value pre-multiply | CONFIRMED |
| `word_30525C` | LAMFA×cal product | scaled commanded lambda | CONFIRMED |
| `word_3029A0:A2` | **fr_w** lambda I-state | closed-loop lambda integrator state (PT1 `sub_43904`) | CONFIRMED role; GSHJ `fr_w "Lambda Control (Fuel Trim)"` [NAME-XDF] |
| `word_30561E` | lambda target/ref | closed-loop lambda reference | CONFIRMED role; INFERRED |
| `word_305258` | lambda deviation | closed-loop lambda error term | CONFIRMED role; INFERRED |
| `word_2381E` | lambda I-gain | closed-loop PT1 gain (cal) | CONFIRMED |
| `word_2379C`/`word_237F2` | LAMFA scale cals | fixed-point lambda scale constants | CONFIRMED |
| `word_30297C` × `word_302968` | rk × multiplier | → injector accumulator (RKTI, `sub_775C8`) | CONFIRMED |
| `word_30069C:9E` | **ti / te injector qty** | 32-bit injector pulse-width accumulator | CONFIRMED role; GSHJ `te_w "Effective Injection Time"` [NAME-XDF] |
| component-protect λ (`sub_86318`) | **lambts_w** | KFLBTS over-temp enrichment lambda (richer-clamped) | CONFIRMED mechanism; GSHJ `lambts_w "Lambda BTS Value"` [NAME-XDF] |

> **Correction (carry over from fueling.md):** `0x19B5A` is **DTXKS3**, not the KFLBTS
> z-table. KFLBTS is read through the page-6 protection-lookup descriptors via the byte
> lookup `sub_419F4`; its z-address is not a direct operand. **[CONFIRMED]**

---

## 5. Highest-confidence bindings (the ones to trust)

These are **CONFIRMED by code role** and corroborated by a sibling-family name; safe to use
as engineering labels in the docs:

- `word_31E484` = **rlsol_w** — relative-load setpoint (KFMIRL output → boost target)
- `word_302E62` = **boost-control setpoint** (load-domain plsol); `word_302E58` = **actual ratio**
- `word_302E60` = **final LDR demand**; `word_302E7C/7E` = **ldtvm** scaled / clamped wastegate duty
- `word_2BF32` = **KFLDIMX** I-gain/limit; `word_2BF4A` = **KFLDIMX enable/authority threshold**
- `word_2BF4E`/`word_2BF50` = **wastegate duty MIN/MAX**; `word_2BF48` = **over-boost rpm trip (6000)**
- `word_2BECA` = **KFLDRX** feed-forward map; `word_2BEAC` = **KFLDRL** linearization map
- `byte_F3FA` = **global knock retard** (wkr); `0x30B24C[cyl]` = **dwkrz[cyl]** per-cyl retard accumulator
- `byte_30132E` = **base ignition advance** (zwbas); `0x309317[cyl]` = **zwout** emitted spark advance
- `word_3029A4` = **lamfa_w** (driver lambda); `word_30297C` = **commanded fuel multiplier**
- `word_3029A0:A2` = **fr_w** lambda fuel-trim integrator state

**Two corrections to the existing docs:**
1. `word_F410` = **nmot_w (engine speed)**, not `rl`. The actual `rl_w` is a separate cell
   (GSHJ `0xF478`), un-pinned in this bin. Structure unchanged; only the label is wrong.
2. `0x19B5A` = **DTXKS3** (knock), not the KFLBTS z-table.

**Lowest confidence (name = role-inferred only, no external corroboration):** the LDR
intermediate cells `word_302E3C/3E/34`, the 2nd-integrator path (`word_2BF2E/30`,
`word_302E50/5A/70/72`), `word_302496`/`word_30294A` (ratio numerator/divisor), and the
per-cyl knock offset table `0x309545`. Their *function* is confirmed; only the ME7 *token*
is a best guess.
