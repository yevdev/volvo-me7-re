"""Parse an ASAP2 .a2l into a map-dictionary CSV (name, address, shape, datatype, scaling, unit).

An ME7 .a2l is the richest map *dictionary* around: authoritative shape / datatype / scaling /
unit / description per CHARACTERISTIC. The addresses inside it are for *its own* bin, so use it for
map MEANING, not for GPHJ offsets (GPHJ offsets come from the WinOLS / XDF defs). One CSV row per map.

The .a2l is not bundled (size / licensing) — point the script at your own copy:
    py scripts/a2l/parse-a2l.py path/to/your.a2l        # or set ME7_A2L=path/to/your.a2l
Output: $ME7_OUT/a2l/gphj_a2l_maps.csv   (default <repo>/out/a2l/).
"""
import os, re, csv, sys
from pathlib import Path

REPO = Path(os.environ.get("ME7_REPO", Path(__file__).resolve().parents[2]))
A2L_PATH = Path(sys.argv[1]) if len(sys.argv) > 1 else (
    Path(os.environ["ME7_A2L"]) if os.environ.get("ME7_A2L") else None)
if A2L_PATH is None or not A2L_PATH.exists():
    sys.exit("parse-a2l: no .a2l found — pass a path as arg 1 or set ME7_A2L (the .a2l is not bundled)")
OUT = Path(os.environ.get("ME7_OUT", REPO / "out")) / "a2l"; OUT.mkdir(parents=True, exist_ok=True)

A2L = A2L_PATH.read_text(errors="replace")
def toks(s): return re.findall(r'"[^"]*"|\S+', s)
def hx(v):
    try: return int(v, 16) if v.lower().startswith("0x") else int(v)
    except Exception: return None

# COMPU_METHOD: name -> (type, unit, coeffs, linear_factor)
compu = {}
for m in re.finditer(r'/begin COMPU_METHOD(.*?)/end COMPU_METHOD', A2L, re.S):
    t = toks(m.group(1))
    if not t: continue
    name, ctype = t[0], (t[2] if len(t) > 2 else "")
    unit = t[4].strip('"') if len(t) > 4 else ""
    co = []
    for kw in ("COEFFS_LINEAR", "COEFFS"):
        if kw in t:
            i = t.index(kw); co = t[i+1:i+1+(2 if kw == "COEFFS_LINEAR" else 6)]; break
    factor = None
    try:
        if "COEFFS_LINEAR" in t: factor = float(co[0])
        elif len(co) == 6:
            a, b, c, d, e, f = map(float, co)
            if a == 0 and d == 0 and e == 0 and b != 0: factor = f / b
    except Exception: pass
    compu[name] = (ctype, unit, co, factor)

# RECORD_LAYOUT: name -> fnc datatype
rl = {}
for m in re.finditer(r'/begin RECORD_LAYOUT\s+(\S+)(.*?)/end RECORD_LAYOUT', A2L, re.S):
    body = m.group(2)
    d = re.search(r'FNC_VALUES\s+\d+\s+(\w+)', body) or re.search(
        r'\b(UBYTE|UWORD|SBYTE|SWORD|ULONG|SLONG|FLOAT32_IEEE|FLOAT64_IEEE)\b', body)
    rl[m.group(1)] = d.group(1) if d else "?"
DSIZE = {"UBYTE":1,"SBYTE":1,"UWORD":2,"SWORD":2,"ULONG":4,"SLONG":4,"FLOAT32_IEEE":4,"FLOAT64_IEEE":8,"?":1}

# AXIS_PTS: name -> address
axispts = {}
for m in re.finditer(r'/begin AXIS_PTS(.*?)/end AXIS_PTS', A2L, re.S):
    t = toks(m.group(1))
    if len(t) > 3: axispts[t[0]] = hx(t[3])

rows = []
for m in re.finditer(r'/begin CHARACTERISTIC(.*?)/end CHARACTERISTIC', A2L, re.S):
    body = m.group(1); t = toks(body)
    if len(t) < 7: continue
    name, desc, ctype, addr, reclay, _maxdiff, cm = t[0], t[1].strip('"'), t[2], t[3], t[4], t[5], t[6]
    a = hx(addr)
    if a is None: continue
    axdims, axaddr = [], []
    for am in re.finditer(r'/begin AXIS_DESCR(.*?)/end AXIS_DESCR', body, re.S):
        at = toks(am.group(1))
        if len(at) >= 4:
            axdims.append(hx(at[3]) or 0)
            ref = at[at.index("AXIS_PTS_REF")+1] if "AXIS_PTS_REF" in at else None
            axaddr.append(axispts.get(ref) if ref else None)
    dt = rl.get(reclay, "?"); esz = DSIZE.get(dt, 1)
    ncells = 1
    for d in axdims: ncells *= (d or 1)
    _ct, unit, _co, factor = compu.get(cm, ("", "", [], None))
    rows.append({
        "name": name, "type": ctype, "address_hex": f"0x{a:05X}", "address_dec": a,
        "rows": axdims[1] if len(axdims) > 1 else 1, "cols": axdims[0] if axdims else 1,
        "cells": ncells, "datatype": dt, "elem_bytes": esz, "byte_len": ncells*esz,
        "end_hex": f"0x{a+ncells*esz-1:05X}", "scale_factor": (f"{factor:.6g}" if factor else ""),
        "unit": unit, "compu": cm,
        "x_axis_hex": f"0x{axaddr[0]:05X}" if axaddr and axaddr[0] else "",
        "y_axis_hex": f"0x{axaddr[1]:05X}" if len(axaddr) > 1 and axaddr[1] else "",
        "desc": desc[:80],
    })
rows.sort(key=lambda r: r["address_dec"])
cols = ["name","type","address_hex","end_hex","rows","cols","cells","datatype","elem_bytes",
        "byte_len","scale_factor","unit","x_axis_hex","y_axis_hex","compu","desc"]
with (OUT / "gphj_a2l_maps.csv").open("w", newline="", encoding="utf-8") as f:
    w = csv.DictWriter(f, fieldnames=cols, extrasaction="ignore"); w.writeheader(); w.writerows(rows)
print(f"parsed {len(rows)} maps from {A2L_PATH.name} -> {OUT/'gphj_a2l_maps.csv'}")
