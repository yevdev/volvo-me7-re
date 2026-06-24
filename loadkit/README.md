# ME7 50GPHJ — IDA load kit

Get a high-fidelity, annotated IDA view of a Volvo ME7.0 **50GPHJ** ROM from a raw bin.
Names here are **GPHJ-specific** (addresses match the 50GPHJ layout). For other ME7 calibration
IDs the control *structure* is identical but addresses differ — use `../scripts/ida/` to rebuild,
and see the FLIRT note below for cross-bin function naming.

## One-shot (recommended)
```
idat.exe -A -c -pC166 -TBinary -b0 -S"ida_me7_load.py <this-loadkit-folder>" your_50gphj.bin
```
Writes `me7_annotated.i64` with: DPP regs seeded, RAM segment added, code carved (~3,400 functions),
**1,620 calibration maps labeled**, the control/lookup functions named, and key RAM cells named + commented.

## Or apply names to an existing carved database
```
idat.exe -A -S"ida_apply_names.py <this-folder>" your_carved.i64
```

## Files
| File | What |
|---|---|
| `map_names.csv` | 1,620 GPHJ calibration map/axis names (`addr,name,comment`) |
| `function_names.csv` | 72 named functions — control path + 5 OBD diagnostics + lookup/integrator helpers |
| `ram_names.csv` | 55 key RAM/cal cells (rl/rlsol, nmot, cam phase, lambda trim, EGT, knock retard, KFLDIMX, …) |
| `ida_me7_load.py` | one-shot: setup + carve + apply |
| `ida_apply_names.py` | apply names to an already-carved db |

**Gotcha:** `idat -A` leaves `.id0/.id1/.nam/.til` working files that block re-open — delete them before each run; one IDA process per database.

## Cross-bin (other ME7 families)
The function names are GPHJ code addresses. To auto-name the common library routines (the lookup
family, integrators) across *different* ME7 bins, build IDA **FLIRT** signatures from these
functions (`sigmake`) — a good community follow-up, not included here.
