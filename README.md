# Volvo ME7.0 (50GPHJ) ECU — reverse-engineering notes

Reverse-engineering notes for the Bosch **ME7.0** ECU in the **Volvo S60R / V70R** — engine
**B5254T4** (the ~300 PS high-pressure 2.5-litre turbo five; ID-block code **B5254RT**, "25RT"),
calibration family **50GPHJ**, on the Infineon **C167CR / C166**. The point of all this: read the
real engine-control logic *out of the code*, instead of guessing what a map does from its A2L blurb.
Worked up in **IDA** (for the segmented-address xrefs that tie each map to the code that reads it)
and **Ghidra + a C166 module** (for readable pseudo-C). Shared for anyone wrenching on these cars.

**Baseline:** everything here is read off a **clean stock** 50GPHJ image (`B5254RT 25RT MAN AWD EU`,
cal-rev `21GPPVDC`). Tuner-hacked bins — no-lift-shift, cruise map-switch, anti-lag, the kind that
inject code up around `0xF0800` and hook the stock ignition/boost routines — are deliberately left
out. The aim is to document what the *factory* ECU does, so it's a clean base for your own work.

## Scope — what's here, what isn't

- ✅ The full control path, read from the code — air/MAF→load, charge model, torque structure +
  coordinator → load setpoint, LDR boost, ignition (base + knock), VVT cam timing, fuelling (lambda +
  adaptation + injection + component protection + cranking/after-start + purge), idle (air + spark),
  warm-up/cat-heat, and the rev/speed limiters. Subsystem map up front in [docs/ALGORITHM.md](docs/ALGORITHM.md).
- ✅ The lookup machinery, worked out end to end — the six interpolation routines and the map binary layout.
- ✅ A **1,620-entry calibration dictionary** (`loadkit/map_names.csv` — tables, curves, axes and
  constants with addresses + units), with the control-path maps tied to the functions that read
  them. See **[docs/map-inventory.md](docs/map-inventory.md)**.
- ✅ **Function coverage: 174 of the 3,417 carved functions are named / role-identified** across the docs —
  concentrated on the calibration-driven control code (documented end-to-end above) plus five OBD diagnostic
  monitors, each with cited addresses (and **named** Ghidra pseudo-C for 52 of them). A few high-cal
  functions remain named-but-untraced — see [docs/ALGORITHM.md](docs/ALGORITHM.md) → Coverage.
- ❌ Not a function-by-function decompile of all 3,417 carved functions. Diagnostics, KWP2000 comms and a lot
  of leaf routines are carved but not individually written up. C166 has no Hex-Rays decompiler, so the
  IDA output is annotated assembly; Ghidra's module gives the pseudo-C.
- ❌ Not a whole-ROM byte-coverage proof — the dictionary says what a region is *called*, not that
  every byte of the cal band is attributed to a named map.

## Contents
- [`docs/ALGORITHM.md`](docs/ALGORITHM.md) — the end-to-end control algorithm (**start here**)
- `docs/{lookup,boost,ignition,fueling,torque}.md` — per-subsystem detail, cited addresses
- [`docs/map-inventory.md`](docs/map-inventory.md) — the named-map dictionary + map→reader linkage
- [`docs/warmup-idle-thermal.md`](docs/warmup-idle-thermal.md) — warm-up / cat-heating, thermal model, EGT model, idle spark reserve
- [`docs/limiters.md`](docs/limiters.md) — rev limiter (NMAX) + ≈250 km/h vehicle-speed limiter (VMAX)
- [`docs/load-rl.md`](docs/load-rl.md) — MAF/HFM → relative-load `rl` (speed-density model, `KRKTE`)
- [`docs/charge.md`](docs/charge.md) — manifold-pressure → charge model (`sub_AD3D0`; not EGR)
- [`docs/idle-governor.md`](docs/idle-governor.md) — air-side idle governor (LLR, torque-reserve)
- [`docs/cam-timing.md`](docs/cam-timing.md) — VVT / cam-phase controller (dual intake+exhaust, NWS)
- [`docs/ram-names.md`](docs/ram-names.md) — RAM/CAL cell → engineering name (cross-checked against the sibling 50GSHJ A2L/XDF)
- [`docs/bytemap_callers.md`](docs/bytemap_callers.md) — byte-map → reader-function linkage
- [`docs/methodology.md`](docs/methodology.md) — toolchain, IDA/Ghidra setup, the baseline image, gotchas
- [`data/word_map_callers.txt`](data/word_map_callers.txt) — master map→function table (96 word-map lookups via `sub_41A68`)
- [`data/xref/functions.csv`](data/xref/functions.csv) — every carved function (3,417) with caller/callee/cal/RAM counts + the calibration addresses each reads
- [`data/xref/callgraph.csv`](data/xref/callgraph.csv) — caller→callee edges (partial; see scope note)
- `data/disasm/*.txt` — IDA annotated disassembly of the control functions (`CAL->` + `CALL` refs)
- [`data/disasm/all_functions.txt.gz`](data/disasm/all_functions.txt.gz) — annotated disassembly of all 3,417 functions
- [`data/pseudocode/key_functions.c`](data/pseudocode/key_functions.c) — **named** Ghidra pseudo-C of 52 control + diagnostic functions
- [`loadkit/`](loadkit/) — one-shot IDA loader + name DB (1,620 maps + control functions + key RAM) → an annotated `.i64` from a raw 50GPHJ bin (`ida_me7_load.py`)
- [`scripts/`](scripts/) — IDA Python (C166 setup, carve, lookup/byte-map enumeration, dumpers, xref export), Ghidra Java, and the A2L parser. Config + usage in [`scripts/README.md`](scripts/README.md).

## Toolchain (install your own — nothing is bundled)
- **IDA** + its built-in **C166** processor. With the DPP segment registers seeded, IDA resolves the
  C166 DPP/EXTP/EXTS data accesses into **real listing xrefs** — that's the map→function linkage the
  whole thing hangs on.
- **Ghidra** + the **C166 SLEIGH module** by *keyhana*
  ([github.com/keyhana/c166-ghidra-module](https://github.com/keyhana/c166-ghidra-module)) for pseudo-C.
  That module resolves DPP/EXTP in the **decompiler (pcode)** only, so it produces **no listing xrefs** —
  use IDA for linkage, Ghidra for pseudo-C. One import fix: its compiler spec lists a `CP` register the
  SLEIGH doesn't define — delete that `<register name="CP"/>` line in `c166.cspec` or the decompiler won't load.
- Andy Whittaker's [idaproboschme7x](https://github.com/andywhittaker/idaproboschme7x) is the classic ME7 IDA aid.

## Reproduce
1. Load the raw 1 MB ROM in IDA: `-pC166 -TBinary -b0`. Run [`scripts/ida/ida_volvo_c166_setup.py`](scripts/ida/ida_volvo_c166_setup.py)
   (sets `DPP0=4 DPP1=5 DPP2=0xC0 DPP3=3`, RAM seg @`0x300000`), then `scripts/ida/build_carved_c166_db.py` to carve.
2. `scripts/ida/ida_lookup_callers.py` / `ida_bytemap_callers.py` → the map→function tables.
3. `scripts/ida/ida_dump_func.py <out> <addr>...` → annotated disassembly of any function.
4. Ghidra: install the C166 module; import as C166 at base `0x0`; run `SetDPP.java` + `CarveCode.java`,
   then `ApplyMe7Names.java <loadkit>` (stamps the loadkit names onto the Ghidra DB) + `DecompKeyFns.java <out> <addrs>` for **named** pseudo-C.
- Or skip all of that and use [`loadkit/`](loadkit/) — one command takes a raw 50GPHJ bin to a fully annotated `.i64`.
- **Gotcha:** `idat -A` leaves `.id0/.id1/.nam/.til` working files that block re-open — delete them before each headless run; one IDA process per database.

## Credit / license
RE notes shared freely for the community. IDA and Ghidra are third-party tools (not included); the
C166 Ghidra module is © its author (keyhana, MIT). Map names/units are cross-referenced from public
Volvo ME7 A2L/XDF definitions. **No vehicle-specific identity, VIN, tune, or owner data is included.**

## Acknowledgements
This work leaned heavily on these tools — thanks to their authors:

- **[keyhana/c166-ghidra-module](https://github.com/keyhana/c166-ghidra-module)** — the Ghidra C166 processor (SLEIGH) module that made C166 **pseudo-C decompilation** possible (see `data/pseudocode/key_functions.c`). It does the DPP/EXTP/EXTS address translation; essential to this work.
- **[hn/c166-dis](https://github.com/hn/c166-dis)** — standalone C166 disassembler.
- **[andywhittaker/idaproboschme7x](https://github.com/andywhittaker/idaproboschme7x)** — the classic Bosch ME7 IDA helper (function/table signature search).
