# Calibration map inventory

> **ME7-RE docs:** [Algorithm](ALGORITHM.md) · [Boost](boost.md) · [Ignition](ignition.md) · [Fueling](fueling.md) · [Torque](torque.md) · [Lookup](lookup.md) · [Maps](map-inventory.md) · [Warm-up/idle](warmup-idle-thermal.md) · [RAM names](ram-names.md) · [Byte-maps](bytemap_callers.md) · [Methodology](methodology.md) · [↑ README](../README.md)

What's actually named in the 50GPHJ image, and which maps are wired to the code that reads them.

## The dictionary — `../loadkit/map_names.csv`

1,620 named calibration objects from the GPHJ definition set. Each row is `addr,name,comment`,
where the comment carries the kind (table / curve / axis / constant) and the unit. Run the loader
([`../loadkit/ida_me7_load.py`](../loadkit/ida_me7_load.py)) and every one of these lands on the
image as a label + comment.

| Where | Count | What |
|---|---:|---|
| Calibration band `0x10000–0x2CFFF` | 1,453 | the tables, curves and constants the ECU runs against |
| `0x2D000+` | 91 | upper-area maps/axes (LDR boost region, etc.) |
| `< 0x10000` | 76 | shared axes + low-ROM constants (39 are bare axis stubs) |
| — of which axes | 586 | shared / re-referenced axis definitions |

This is a *name list* — it tells you what a region is called, address by address. It is not, on its
own, a byte-by-byte proof that the whole band is accounted for (see **Coverage** below).

## Control-path maps → the function that reads each

The maps that actually matter for tuning, tied to their reader (from
[`../data/word_map_callers.txt`](../data/word_map_callers.txt), [`bytemap_callers.md`](bytemap_callers.md),
and the subsystem docs):

| Map | Addr | Reader | Subsystem |
|---|---|---|---|
| KFPED | `0x1E776` | pedal path (`sub_4E6F6`; exact interp site still open) | [torque](torque.md) — pedal → torque |
| KFMIOP | `0x156CC` | `sub_4F4BC` | [torque](torque.md) — optimum-torque model |
| KFMIRL | `0x158A4` | `sub_4F97A` | [torque](torque.md) — torque → load setpoint |
| KFLDIMX | `0x2C000` | `sub_DBB04` / `sub_DBF44` | [boost](boost.md) — I-limit + enable threshold |
| KFLDRX | `0x27EE2` | `sub_DBB04` | [boost](boost.md) — boost ceiling / P-gain |
| KFLDRL | `0x2C152` | `sub_DBB04` | [boost](boost.md) — post-PID WGDC linearization |
| KFZW1–4 | `0x133B1` / `0x13471` / `0x13531` / `0x135F1` | `sub_518B8` via `sub_411F4` | [ignition](ignition.md) — base advance |
| LAMFA | `0x2383E` | `sub_894C0` | [fueling](fueling.md) — driver lambda |
| KFLBTS | `0x19B5A` | `sub_86318` | [fueling](fueling.md) — component-protection enrichment |

96 word-map lookups are resolved to their callers in `word_map_callers.txt`; the byte-map
(KFZW / KFLBTS) linkage is in `bytemap_callers.md`.

## Coverage — what we claim, and what we don't

- **Named:** the 1,620-entry dictionary above is what annotates the image, and it's dense through
  the calibration band.
- **Not claimed:** that every byte of `0x10000–0x2CFFF` is a named map. The dictionary names regions;
  it isn't a whole-band byte attribution.
- **Diff coverage (a separate check, not shipped here):** run against a real GPHJ stage-1 calibration
  change, every *changed* calibration byte landed inside a named map — i.e. the tune only ever touched
  named regions, nothing left unexplained. That validation is tied to a specific tune/owner and is
  kept out of this repo on purpose.
