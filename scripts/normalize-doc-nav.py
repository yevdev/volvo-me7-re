#!/usr/bin/env python3
"""Normalize the `> **ME7-RE docs:**` nav line across docs/*.md to the canonical set.

Each subsystem doc carries a one-line nav header linking the others. As docs were added the
list drifted; run this to set every doc's nav line to the same canonical order.

Usage (from anywhere):  py scripts/normalize-doc-nav.py
ASCII-only source (uses \\u escapes for the middot/arrow), so it runs under any console encoding.
"""
import glob
import os

DOCS = [
    ("Algorithm", "ALGORITHM.md"), ("Boost", "boost.md"), ("Ignition", "ignition.md"),
    ("Fueling", "fueling.md"), ("Torque", "torque.md"), ("Load/rl", "load-rl.md"),
    ("Charge", "charge.md"), ("Cam timing", "cam-timing.md"), ("Lookup", "lookup.md"),
    ("Maps", "map-inventory.md"), ("Warm-up/idle", "warmup-idle-thermal.md"),
    ("Idle gov", "idle-governor.md"), ("Limiters", "limiters.md"), ("RAM names", "ram-names.md"),
    ("Byte-maps", "bytemap_callers.md"), ("Methodology", "methodology.md"),
]
SEP = " · "  # middot
NAV = "> **ME7-RE docs:** " + SEP.join(f"[{label}]({fn})" for label, fn in DOCS) \
      + SEP + "[↑ README](../README.md)"

repo = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
changed = []
for path in sorted(glob.glob(os.path.join(repo, "docs", "*.md"))):
    text = open(path, encoding="utf-8").read()
    lines = text.split("\n")
    for i, line in enumerate(lines):
        if line.startswith("> **ME7-RE docs:**"):
            if line != NAV:
                lines[i] = NAV
                open(path, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
                changed.append(os.path.basename(path))
            break
print("normalized nav in:", ", ".join(changed) if changed else "(all already canonical)")
