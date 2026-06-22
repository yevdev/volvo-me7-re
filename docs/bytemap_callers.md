# ME7 (50GPHJ) C166 — BYTE-map lookup callers (map → reader-function master table)

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

Completes the map→function linkage for the **byte-resolution** lookups, the counterpart to
`lookup_callers.txt` (which covers the word lookup `sub_41A68`). Worked in IDA on
`<work>\me7_stock_lookup.i64`. Code is byte-identical across calibration revisions.

Enumerator: `scripts/ida/ida_bytemap_callers.py` (two address-resolution modes — see §1).
Source dumps: `dump_lookups.txt` (the routines), `dump_411F4callers.txt`,
`cm_411F4.txt`, `cm_419F4.txt`.

Legend: **[C]** = confirmed from the cited disassembly; **[I]** = inferred / structural.
All physical addresses are `(page<<14)|offset`.

---

## 1. Resolved calling conventions (the two byte lookups differ)

### `sub_411F4` — 2-D **SBYTE** bilinear map  **[C]**
No `extp` anywhere in the body: r12 and r13 are *near* data pointers resolved through the
**DPP segment registers** (`DPP0=4, DPP1=5, DPP2=0xC0, DPP3=3` from startup — see findings.md).
```
r12 = map z-data near-pointer  (16-bit; DPP-resolved)
r13 = pointer to the shared AXIS-DESCRIPTOR block (NOT a page)   ; first byte = #cols = row stride
r14 = packed ROW axis word : high byte = row index, low byte = row fraction*2
r15 = packed COL axis word : high byte = col index, low byte = col fraction*2
      -> result = bilinearly-interpolated SBYTE, sign-extended in r4
```
Body (0x411F4–0x41248): `movb rl2,[r13]` → row stride; `r12 += rowidx*stride + colidx`;
`z00 = sbyte[r12]`; interp along cols (low row) then high row, then between rows. **[C]**

**Physical-address rule.** Every observed z-pointer is in DPP0 (`0x0000–0x3FFF`) or DPP1
(`0x4000–0x7FFF`). Because **DPP1 = DPP0 + 1**, both collapse to the same arithmetic:
```
phys = 0x10000 + r12_imm          (equivalently (4<<14)|r12 ; works for r12 < 0x8000)
```
So the table below uses page 4 base; an r12 with bit-14 set (e.g. 0x4152) lands in the
DPP1 page 5 region (0x14152) automatically. **[C]**

> The axis-descriptor block in r13 (e.g. `#502A` for KFZW) is shared per map-family, holding
> column count + the pre-computed row/col index+fraction. The RPM/load axis prep is done by a
> separate routine (`word_3019B6[`/`](/)word_3019CA` = KFZW RPM/load packed-axis words). **[C]**

### `sub_419F4` — 1-D **byte** table  **[C]**
Uses `extp r13, #1` before every data fetch (0x419F6, 0x41A04, …): **r13 IS the page**, r12 the
offset — identical convention to `sub_41A68`. Layout `[len:byte][X[]:byte][Z[]:byte]`,
truncating interp, clamps both ends.
```
r12 = table offset,  r13 = page  ->  phys = (r13<<14)|r12
r14 = input -> r4 = interpolated byte (zero-extended)
```
**[C]**  Enumeration uses the same logic as `ida_lookup_callers.py` (mode `page`).

---

## 2. `sub_411F4` (2-D SBYTE) — map → reader master table  **[C]**

21 of 23 xrefs resolve to an immediate z-pointer. The 2 unresolved (`sub_4149C` @0x414C4,
`sub_41682` @0x416AA) load `r12=[r0]` — generic **forwarding wrappers** that pass a
caller-supplied map pointer; not direct readers.

| phys z | r12 imm | axis blk (r13) | reader func | call EA | identity |
|--------|---------|----------------|-------------|---------|----------|
| 0x12AA2 | 0x2AA2 | 0x582C | sub_4F4BC | 0x4F4FC | 2-D map A (#582C-axis family) |
| 0x12B52 | 0x2B52 | 0x582C | sub_4F4BC | 0x4F514 | 2-D map B |
| 0x12C02 | 0x2C02 | 0x582C | sub_4F4BC | 0x4F59E | 2-D map C |
| 0x12CB2 | 0x2CB2 | 0x582C | sub_4F4BC | 0x4F5B6 | 2-D map D |
| 0x12F1B | 0x2F1B | 0x322B | sub_50ED2 | 0x51054, 0x5111A | KFZW-family secondary |
| 0x12F2B | 0x2F2B | 0x502A | sub_50ED2 | 0x50FAC | KFZW-family secondary |
| 0x12FEB | 0x2FEB | 0x502A | sub_50ED2 | 0x50F92 | KFZW-family secondary |
| 0x130AB | 0x30AB | 0x502A | sub_50ED2 | 0x50FEC | KFZW-family secondary |
| 0x1316B | 0x316B | 0x502A | sub_50ED2 | 0x50EEA | KFZW-family secondary (→byte_301326) |
| 0x13231 | 0x3231 | 0x502A | sub_5172C | 0x5182A | KFZW-family corrective |
| 0x132F1 | 0x32F1 | 0x502A | sub_5172C | 0x517EA | KFZW-family corrective |
| **0x133B1** | **0x33B1** | **0x502A** | **sub_518B8** | **0x518CE** | **KFZW1** (base timing, sbyte 0.75°/ct) |
| **0x13471** | **0x3471** | **0x502A** | **sub_518B8** | **0x518E4** | **KFZW2** |
| **0x13531** | **0x3531** | **0x502A** | **sub_518B8** | **0x51966** | **KFZW3** |
| **0x135F1** | **0x35F1** | **0x502A** | **sub_518B8** | **0x5197C** | **KFZW4** |
| 0x13835 | 0x3835 | 0x27F3 | sub_7177C | 0x717D6 | single 2-D map (#27F3 axis) → byte_3014C9 |
| 0x14152 | 0x4152 | 0x273E | sub_A0000 | 0xA0B6E | catalyst/misfire monitor map (variant) |
| 0x142E1 | 0x42E1 | 0x273E | sub_A0000 | 0xA0AC8 | catalyst monitor map (variant) |
| 0x143A1 | 0x43A1 | 0x273E | sub_A0000 | 0xA0BD2 | catalyst monitor map → byte_3016E2 |
| 0x143E1 | 0x43E1 | 0x273E | sub_A0000 | 0xA0BEA | catalyst monitor map → byte_3016E3 |

Notes:
- **KFZW1–4** are the four cam-phase-variant base-timing maps, read in `sub_518B8` and blended
  by the two cam fractions `byte_30129C[`/`](/)byte_30129B` into `word_3024A8/AA/AC` (the final base
  advance). Confirmed verbatim in the disassembly (matches ignition.md §1–2). **[C]**
- `sub_50ED2` / `sub_5172C` are the KFZW-family **secondary / corrective** map readers
  (ignition.md §3). Several use the same `#502A` axis block; some use a different block
  (`#322B`). **[C for readers; map roles per ignition.md]**
- `sub_A0000` (catalyst/misfire monitoring, 0xA0000–0xA1A4A) selects one of several variant
  z-pointers per call site via flag tests (e.g. `#42E1[`/`](/)#4321[`/`](/)#42A1[`/`](/)#2A1` then call);
  the table lists the address on the fall-through path. It also reaches **`sub_419F4`** once
  (0xA0468, z @ 0x1A0F3 page 6). **[C]**
- `sub_4F4BC` mixes a `sub_43430` (word 2-D) call with four `sub_411F4` (sbyte 2-D) calls —
  a combined word+byte map evaluator with cam blending. **[C]**

---

## 3. `sub_419F4` (1-D byte) — map → reader master table  **[C]**

**120 of 120 xrefs resolved** (every call loads `r12[`/`](/)r13` immediates). 61 distinct caller
functions. Page distribution: page 6 = 104, page 8 = 8, page 7 = 3, page 9 = 3, page A = 1,
page B = 1. The full row-by-row table is in `cm_419F4.txt`; the **KFLBTS cluster**
and other notable readers are below.

### KFLBTS — component-protection lambda target  **[C]**
KFLBTS ("Nominal/target Lambda for component protection", z-table labelled `0x19B5A`) is **not**
a direct operand. It is reached in `sub_86318` through four page-6 byte-lookup descriptors:

| phys z | r12 imm | page | reader func | call EA |
|--------|---------|------|-------------|---------|
| 0x19A4E | 0x1A4E | 6 | **sub_86318** | 0x86950 |
| 0x19A5B | 0x1A5B | 6 | **sub_86318** | 0x868B6 |
| 0x19A68 | 0x1A68 | 6 | **sub_86318** | 0x869DC |
| 0x19A75 | 0x1A75 | 6 | **sub_86318** | 0x86A68 |

`sub_86318` (0x86318–0x875B4) is the **component-protection / over-temperature lambda
enrichment** state machine. It calls `sub_419F4` (byte output maps, the four above), the word
lookup `sub_41A68`, the word-axis split wrapper `sub_42486`, and slew/integrator helpers
`sub_43904` / `sub_42F16`. The KFLBTS table is consumed via these protection-lookup
descriptors, not via its label address. (Matches fueling.md §4 and lookup.md §2.) **[C]**

### Other notable 1-D byte readers (selection — full list in cm_419F4.txt)
| reader func | example phys z | page | role (inferred) |
|-------------|----------------|------|-----------------|
| sub_8DE10 (cluster) | 0x19DA8–0x19DF6 | 6 | ignition/dwell byte tables (many calls) |
| sub_945C2 | 0x19F49–0x19FE5 | 6 | multi-table reader (8 calls) |
| sub_72C02 / sub_724E2 | 0x18ACE–0x18BAD | 6 | byte-table cluster (many calls) |
| sub_8C636 | 0x19D67–0x19D98 | 6 | byte-table cluster (6 calls) |
| sub_D8DCA | 0x1BB1A–0x27E9C | 6/9 | boost/limit byte tables |
| sub_DB0E8 | 0x2BD0A | A | byte table page A |
| sub_D9EA0 | 0x2C4AE | B | byte table page B |
| sub_86318 | 0x19A4E–0x19A75 | 6 | **KFLBTS** (above) |

---

## 4. Related byte lookups (for completeness)

- **`sub_42082`** (signed-byte 1-D, hi-byte fraction): used by `sub_4E5EC` (sensor scaling).
  Enumerate with the `page` mode if a master table is wanted. **[C, lookup.md §2]**
- **`sub_421F4`** (2-D word, caller-pushed axis fractions): used by `sub_4E5EC`. **[C]**
- **`sub_43430`** (word 2-D, KFMIOP-class): seen in `sub_4F4BC` @0x4F4E4 alongside the
  sbyte maps. **[C]**

These are word/signed variants outside the byte-map scope of this deliverable but share the
DPP / `extp` resolution patterns documented above.

---

## 5. How to regenerate

```
# sub_411F4 (2-D sbyte; r12=offset, page=4 base, r13=axis-block):
idat.exe -A -S"scripts/ida/ida_bytemap_callers.py <out.txt> 0x411F4 fixed 4" me7_stock_lookup.i64
# sub_419F4 (1-D byte; r13=page):
idat.exe -A -S"scripts/ida/ida_bytemap_callers.py <out.txt> 0x419F4 page"     me7_stock_lookup.i64
```
(Clean `.id0/.id1/.nam/.til` before each run; one idat process at a time.)

> A foreign-bin A2L map inventory (e.g. running `scripts/a2l/parse-a2l.py` against a non-GPHJ a2l)
> is a **different ROM revision** and its addresses do **not** align with the GPHJ physical map
> addresses above — don't use it to name these maps. Names here come from the disassembly
> (KFZW1–4, KFLBTS) per ignition.md/fueling.md; un-named entries are labelled by reader.
