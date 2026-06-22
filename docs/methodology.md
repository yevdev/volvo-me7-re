# Volvo ME7 (50GPHJ) C166 reverse engineering — working findings

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

How the 50GPHJ firmware (Infineon C167CR / C166) was taken apart — the toolchain, the IDA/Ghidra
setup, and the gotchas — so anyone can reproduce or extend it. The aim throughout: read the actual
control logic out of the code, not infer it from the A2L.

**Baseline image.** All of this is read off a **clean stock** 50GPHJ bin (`car/bins/me7_stock.bin`,
identity `B5254RT 25RT MAN AWD EU`, cal-rev `21GPPVDC`, sha1 `a900d139…`). The code is byte-identical
across calibration revisions — only the calibration data differs — so the analysis holds for any GPHJ
tune. **Tuner-hacked bins are deliberately excluded:** no-lift-shift / cruise-map-switch builds inject
code around `0x0D3F0`, `0xE4240` and `0xF0800` and hook the stock ignition/boost routines (`sub_518B8`,
the LDR cluster). None of that is stock behaviour, so none of it is documented here. (Quick tell: a clean
stock bin reads `0x44` fill at those injection offsets; a hacked one has code there.)

---

## Toolchain (what works, what doesn't)

- **Ghidra + the keyhana C166 SLEIGH module** decompiles C166 to pseudo-C, BUT it
  resolves DPP/EXTP/EXTS only inside the decompiler (pcode) — it creates **no listing
  xrefs**, so "which function reads map X" is invisible. Dead end for linkage.
- **IDA + its C166 processor module IS the tool.** With the DPP segment registers
  seeded, IDA's analysis **resolves segmented data accesses into real listing xrefs** —
  6,535 code→calibration references. This is the linkage Ghidra couldn't give.

### IDA setup (reproducible)
- Load raw 1 MB bin: `-pC166 -TBinary -b0` (ROM at `0x0`; maps at their file offsets).
- DPP segment regs: `DPP0=4, DPP1=5, DPP2=0xC0, DPP3=3` (startup values).
- RAM segment at `0x300000` (DPP2=0xC0 → `0xC0<<14 = 0x300000`).
- Auto-analysis alone finds ~80–129 functions. **Aggressive carving** (force-disassemble
  the code segments, skip the calibration band `~0x10000–0x2D000`) yields **~3,400 functions**.
- Working DB: `<work>\me7_carve.i64`.
- **Gotcha:** `idat.exe` with `-A` doesn't repack on `qexit`; it leaves `.id0/.id1/.nam/.til`
  working files that block re-open. **Delete them before each headless run.** Run scripts
  on a **private copy** of the `.i64` (one IDA process per DB).
- Headless: `idat.exe -A -S"<script.py> <args>" <db.i64>` (args via `idc.ARGV`).
- No Hex-Rays decompiler for C166 → output is **annotated disassembly**, interpreted by hand.

### Reusable scripts (in `scripts/ida/`)
- `ida_lookup_callers.py` — enumerate callers of a lookup routine + the (offset,page) map
  pointer each loads → master (map addr → caller) table.
- `ida_dump_func.py` — dump a function's disassembly annotated with `CAL->` data refs and
  `CALL` targets, plus callers.

---

## Key discovery #1 — the universal map lookup `sub_41A68`

Every 2D word-map access goes through one interpolation routine. Calling convention:
```
mov   r12, #<offset>     ; map pointer low (14-bit)
mov   r13, #<page>       ; map page    -> physical = (page<<14)|offset
mov   r14, <input>       ; axis/input value
calls 4, sub_41A68       ; -> interpolated result in r4
```
**`sub_41A68(offset, page, input) → value`.** Enumerating its callers gives the master
map→function linkage: **96 resolved calls** (see `lookup_callers.txt`). Byte maps (KFZW,
KFLBTS) and 1-D tables use *other* lookup variants — finding those is an open task.

## Key discovery #1b — the byte-map lookup `sub_411F4`

The byte (SBYTE) 2D-map interpolator is **`sub_411F4` (0x411F4–0x4124A)** — bilinear,
4-corner. Convention: `r12=z-offset, r13=axis-descriptor-block ptr (e.g. #502A, first
byte = column count/row stride), r14=packed ROW axis word (hi=idx, lo=frac), r15=packed
COL axis word → rl4 = interpolated sbyte`. Callers: sub_4149C, sub_41682, sub_4F4BC,
sub_50ED2, sub_5172C, sub_518B8, sub_7177C, sub_A0000. This is the KFZW lookup. See
`ignition.md` for the full ignition/knock algorithm built on it.

## Key discovery #2 — the boost controller (LDR)

`sub_DBB04` is the LDR boost-control arithmetic; `sub_DBF44` is its enable/limit state machine.
From the disassembly:
- `sub_DBB04`: `gain const (word_2BE38) × measured signal (word_F410)` → fixed-point rescale →
  `sub_41A68` map lookups (LDR maps @ page 0xA) → a **division (`divlu`) producing a ratio** →
  **`sub_43904` integrator/PT1 filter** (carries 32-bit state) → sum + saturate. Classic
  feed-forward + PI boost loop. Reads **KFLDIMX** region (`word_2BF32`).
- `sub_DBF44`: compares a measured value against the **KFLDIMX threshold (`word_2BF4A`)**,
  sets/clears enable+limit bits in `byte_301869` with hysteresis + a debounce counter
  (`byte_30186B`). This is *why* raising KFLDIMX extends controller authority — the code gates here.
- `sub_43904` = integrator/limiter helper (value + 32-bit state → updated state).

## Map → function linkage (confirmed)

| Map(s) | Reader function(s) | Subsystem |
|---|---|---|
| KFLDIMX, KFLDRL, KFLDHBN, KFLDRX | sub_DBB04, sub_DBF44, sub_DC31A, sub_D9EA0, sub_D9688, sub_D5E80 | LDR boost (0xD5–0xDC) |
| KFMIRL, KFMIOP | sub_4F97A, sub_4F95E, sub_4F4BC | torque/load model (0x4F) |
| KFPED | sub_4E6F6 | pedal→torque |
| LAMFA | sub_894C0, sub_8981C, sub_775C8 | fueling (0x77–0x89) |
| KFLBTS | sub_86318 | component-protect fueling |

---

## Open / extension tasks

1. **Lookup internals** — decode `sub_41A68` exact interpolation math (breakpoint search,
   fractional interpolation, rounding/clamp). Find the byte/1-D lookup variants (for KFZW, KFLBTS).
2. **Boost/LDR** — finish `sub_DBB04` / `sub_DBF44` / `sub_D9EA0` / `sub_43904`: identify
   setpoint vs actual, the PI terms, and how KFLDRX (ceiling) / KFLDRL (WGDC feed-forward) feed in.
3. **Ignition + knock** — DONE, see `ignition.md`. Byte-map lookup = `sub_411F4`;
   base = `sub_518B8`; knock = `sub_7BA8C[`/`](/)sub_7BD04` (global retard `byte_F3FA`,
   per-cyl retard table `0x30B24C`); output/zwout = `sub_50984`.
4. **Fueling** — LAMFA (`sub_894C0`) + KFLBTS (`sub_86318`) → commanded lambda → injection.
5. **Torque/load model** — KFMIRL/KFMIOP/KFPED: pedal → requested torque → required load → boost request.

Each task: dump the functions, follow the call tree, and write the subsystem algorithm
grounded in the disassembly + the map linkage.
