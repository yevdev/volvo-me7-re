"""IDA Python setup for Volvo ME7 C166/ST10 raw binaries.

Run from IDA/idat after loading a raw 1MB Volvo ME7 bin with:
  -pC166 -TBinary -b0

This script is intentionally conservative. It sets Volvo DPP assumptions,
creates a RAM segment at 0x300000, imports calibration symbol names from the
local text definition, and writes a setup report. It does not bulk-create code
or functions across the ROM.
"""

from __future__ import annotations

import csv
import os
import re
from pathlib import Path

import ida_auto
import ida_bytes
import ida_funcs
import ida_ida
import ida_idp
import ida_loader
import ida_name
import ida_nalt
import ida_pro
import ida_segment
import idc


# Paths are repo-relative by default; override any of these via environment:
#   ME7_REPO : repo root  (default: auto-detected from this file's location)
#   ME7_OUT  : output dir  (default: <repo>/out; this script writes to $ME7_OUT/ida; also arg 1)
#   ME7_DEF  : optional Volvo ME7 symbol def file ('NAME "desc" 0xADDR'); NOT bundled.
#              Symbol import is skipped when ME7_DEF is unset or the file is missing.
ROOT = Path(os.environ.get("ME7_REPO", Path(__file__).resolve().parents[2]))
DEFAULT_OUT = Path(os.environ.get("ME7_OUT", ROOT / "out")) / "ida"
DEF_FILE = Path(os.environ["ME7_DEF"]) if os.environ.get("ME7_DEF") else ROOT / "VolvoME7def.txt"

DPP_VALUES = {
    "DPP0": 0x4,
    "DPP1": 0x5,
    "DPP2": 0xC0,
    "DPP3": 0x3,
}

RAM_START = 0x300000
RAM_END = 0x310000
ID_WINDOW_START = 0x18780
ID_WINDOW_END = 0x18980


def script_args() -> list[str]:
    argv = getattr(idc, "ARGV", [])
    try:
        return [str(argv[i]) for i in range(1, len(argv))]
    except Exception:
        return []


def printable(data: bytes) -> str:
    return "".join(chr(b) if 32 <= b <= 126 else "." for b in data)


def squish(text: str, limit: int = 360) -> str:
    text = " ".join(text.split())
    return text if len(text) <= limit else text[: limit - 3] + "..."


def safe_name(raw: str, prefix: str = "cal") -> str:
    name = re.sub(r"[^A-Za-z0-9_]", "_", raw).strip("_")
    if not name:
        name = prefix
    if name[0].isdigit():
        name = f"{prefix}_{name}"
    return name[:120]


def get_identity() -> dict[str, str]:
    data = ida_bytes.get_bytes(ID_WINDOW_START, ID_WINDOW_END - ID_WINDOW_START) or b""
    text = printable(data)
    code = re.search(r"\b\d{2}[A-Z0-9]{4}\.a2l\b", text)
    sw = re.search(r"sw:[A-Za-z0-9]+", text)
    family = re.search(r"ME7_500\s+[0-9A-Z]{4}", text)
    market = "EU" if "AWD EU" in text else "US" if "AWD US" in text else ""
    return {
        "ecu_code": code.group(0) if code else "",
        "sw_part": sw.group(0)[3:] if sw else "",
        "family": family.group(0) if family else "",
        "market": market,
        "id_window": squish(text),
    }


def ensure_processor(report: list[str]) -> None:
    current = ida_ida.inf_get_procname()
    if current.lower() == "c166":
        report.append("processor already c166")
        return
    ok = ida_idp.set_processor_type("c166", ida_idp.SETPROC_USER)
    report.append(f"processor was {current}, set_processor_type('c166')={ok}")


def ensure_ram_segment(report: list[str]) -> None:
    seg = ida_segment.getseg(RAM_START)
    if seg and seg.start_ea <= RAM_START < seg.end_ea:
        report.append(f"RAM segment already present: 0x{seg.start_ea:X}-0x{seg.end_ea:X}")
        return
    ok = ida_segment.add_segm(RAM_START >> 4, RAM_START, RAM_END, "VOLVO_RAM_300000", "DATA")
    report.append(f"add RAM segment 0x{RAM_START:X}-0x{RAM_END:X}: {ok}")


def set_dpps(report: list[str]) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    for index in range(ida_segment.get_segm_qty()):
        seg = ida_segment.getnseg(index)
        seg_name = ida_segment.get_segm_name(seg)
        for reg, value in DPP_VALUES.items():
            default_ok = idc.set_default_sreg_value(seg.start_ea, reg, value)
            split_ok = idc.split_sreg_range(seg.start_ea, reg, value, idc.SR_user)
            rows.append(
                {
                    "segment": seg_name,
                    "start": f"0x{seg.start_ea:X}",
                    "end": f"0x{seg.end_ea:X}",
                    "register": reg,
                    "value": f"0x{value:X}",
                    "default_ok": default_ok,
                    "split_ok": split_ok,
                }
            )
    report.append(f"set DPP defaults/splits on {ida_segment.get_segm_qty()} segments")
    return rows


def parse_def_symbols() -> list[tuple[int, str, str]]:
    symbols: list[tuple[int, str, str]] = []
    pattern = re.compile(r'\s*(\S+)\s+"([^"]*)"\s+0x([0-9A-Fa-f]+)')
    if not DEF_FILE.exists():
        return symbols
    for line in DEF_FILE.read_text(errors="replace").splitlines():
        match = pattern.match(line)
        if not match:
            continue
        symbols.append((int(match.group(3), 16), match.group(1), match.group(2)))
    return symbols


def import_symbols(report: list[str]) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    renamed = 0
    commented = 0
    max_ea = ida_ida.inf_get_max_ea()
    for ea, name, desc in parse_def_symbols():
        if ea >= max_ea:
            continue
        flags = idc.get_full_flags(ea)
        existing = idc.get_name(ea)
        is_code = ida_bytes.is_code(flags)
        safe = safe_name(name)
        set_name_ok = False
        if not existing:
            set_name_ok = ida_name.set_name(ea, safe, ida_name.SN_CHECK)
            if set_name_ok:
                renamed += 1
        if desc and not is_code:
            if idc.set_cmt(ea, f"{name}: {desc}", False):
                commented += 1
        rows.append(
            {
                "ea": f"0x{ea:05X}",
                "name": name,
                "safe_name": safe,
                "description": desc,
                "existing_name": existing,
                "is_code": is_code,
                "set_name_ok": set_name_ok,
            }
        )
    report.append(f"imported symbol hints: names_set={renamed}, comments_set={commented}, source={DEF_FILE}")
    return rows


def segment_rows() -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    for index in range(ida_segment.get_segm_qty()):
        seg = ida_segment.getnseg(index)
        rows.append(
            {
                "name": ida_segment.get_segm_name(seg),
                "start": f"0x{seg.start_ea:X}",
                "end": f"0x{seg.end_ea:X}",
                "class": ida_segment.get_segm_class(seg),
                "bitness": seg.bitness,
            }
        )
    return rows


def write_csv(path: Path, fieldnames: list[str], rows: list[dict[str, object]]) -> None:
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def main() -> None:
    args = script_args()
    out_dir = Path(args[0]) if args else DEFAULT_OUT
    out_dir.mkdir(parents=True, exist_ok=True)
    stem = Path(ida_nalt.get_input_file_path() or ida_nalt.get_root_filename()).stem
    prefix = safe_name(stem, "bin")

    report: list[str] = []
    ida_auto.auto_wait()
    ensure_processor(report)
    ensure_ram_segment(report)
    dpp_rows = set_dpps(report)
    symbol_rows = import_symbols(report)

    ida_auto.auto_wait()
    ida_loader.save_database(str(out_dir / f"{prefix}.i64"), 0)

    identity = get_identity()
    segments = segment_rows()
    functions = list(idautils.Functions()) if "idautils" in globals() else []
    try:
        import idautils as _idautils
        functions = list(_idautils.Functions())
    except Exception:
        functions = []

    write_csv(out_dir / f"{prefix}_segments.csv", ["name", "start", "end", "class", "bitness"], segments)
    write_csv(out_dir / f"{prefix}_dpp_setup.csv", ["segment", "start", "end", "register", "value", "default_ok", "split_ok"], dpp_rows)
    write_csv(out_dir / f"{prefix}_symbol_import.csv", ["ea", "name", "safe_name", "description", "existing_name", "is_code", "set_name_ok"], symbol_rows)

    lines = [
        "# Volvo C166 IDA Setup Report",
        "",
        f"- input: `{ida_nalt.get_input_file_path()}`",
        f"- database: `{out_dir / (prefix + '.i64')}`",
        f"- processor: `{ida_ida.inf_get_procname()}`",
        f"- address range: `0x{ida_ida.inf_get_min_ea():X}-0x{ida_ida.inf_get_max_ea():X}`",
        f"- functions after auto-analysis: {len(functions)}",
        f"- ecu_code: `{identity['ecu_code']}`",
        f"- sw_part: `{identity['sw_part']}`",
        f"- family: `{identity['family']}`",
        f"- market: `{identity['market']}`",
        "",
        "## Actions",
        "",
    ]
    lines.extend(f"- {item}" for item in report)
    lines.extend(
        [
            "",
            "## Identity Window",
            "",
            identity["id_window"],
            "",
            "## Generated Files",
            "",
            f"- `{prefix}.i64`",
            f"- `{prefix}_segments.csv`",
            f"- `{prefix}_dpp_setup.csv`",
            f"- `{prefix}_symbol_import.csv`",
            "",
            "## Caution",
            "",
            "This script does not bulk-create functions. Use function creation only on known code starts, not maps/data.",
            "",
        ]
    )
    (out_dir / f"{prefix}_setup_report.md").write_text("\n".join(lines), encoding="utf-8")
    print("VOLVO_C166_SETUP_DONE")
    print(str(out_dir / f"{prefix}_setup_report.md"))
    ida_pro.qexit(0)


if __name__ == "__main__":
    main()
