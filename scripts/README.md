# Scripts

Three kinds of script:

- **`ida/*.py`** — run *inside* IDA's Python (headless `idat`), against a loaded ME7 database.
- **`a2l/parse-a2l.py`** — plain Python (`py`); turns an ASAP2 `.a2l` into a map-dictionary CSV.
- **`ghidra/*.java`** — Ghidra scripts: DPP seeding, carve, `DecompKeyFns` (decompile to pseudo-C), and **`ApplyMe7Names`** — stamps the loadkit `function_names.csv`/`ram_names.csv` onto the Ghidra DB (the Ghidra counterpart of `../loadkit/ida_apply_names.py`).

Nothing here hardcodes a machine path. Inputs and outputs come from script arguments, with
environment variables as the fallback so you can point the kit at your own files:

| Var | Used by | Meaning | Default |
|---|---|---|---|
| `ME7_REPO` | a2l, ida setup | repo root | auto-detected from the script's location |
| `ME7_OUT` | a2l, ida setup | output directory | `<repo>/out` |
| `ME7_A2L` | `parse-a2l.py` | path to your `.a2l` (not bundled) | — pass as arg 1, or set this |
| `ME7_DEF` | `ida_volvo_c166_setup.py` | optional symbol def file (`NAME "desc" 0xADDR`) | unset → symbol import skipped |

The IDA dump/xref helpers (`ida_dump_func.py`, `ida_lookup_callers.py`, …) write to the path you
pass as their **first argument**; with no argument they write a plain filename in the current
directory. Pass the output path explicitly for headless runs.

## Typical run

```
# carve a raw GPHJ ROM into an annotated database (or use ../loadkit for the one-shot)
idat.exe -A -c -pC166 -TBinary -b0 -S"ida/build_carved_c166_db.py" your_50gphj.bin

# dump one function with resolved CAL-> refs and callers
idat.exe -A -S"ida/ida_dump_func.py boost.txt 0xDBB04" me7_carve.i64

# map dictionary from your own a2l
set ME7_A2L=C:\path\to\your.a2l
py a2l/parse-a2l.py
```

See [`../docs/methodology.md`](../docs/methodology.md) for the full toolchain and the IDA/Ghidra gotchas.
