# Find code xrefs to a range of data addresses (for locating map readers).
# Usage: idat.exe -A -S"ida_find_xrefs.py <out.txt> <lo> <hi> [extra_addr...]" <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "ida_xrefs.txt"
LO = int(argv[2], 16)
HI = int(argv[3], 16)
EXTRA = [int(a, 16) for a in argv[4:]]
o = []

def report(target):
    for x in idautils.XrefsTo(target, 0):
        frm = x.frm
        f = ida_funcs.get_func(frm)
        fn = idc.get_func_name(frm) or "?"
        dis = idc.generate_disasm_line(frm, 0) or ""
        o.append("  target=0x%05X  from=0x%05X  func=%s  | %s" % (target, frm, fn, dis))

o.append("=== xrefs into range 0x%05X..0x%05X ===" % (LO, HI))
ea = LO
seen = 0
while ea < HI:
    # any xref to this exact address
    has = False
    for x in idautils.XrefsTo(ea, 0):
        has = True
        break
    if has:
        report(ea)
        seen += 1
    ea += 1
o.append("(addresses-with-xrefs in range: %d)" % seen)

for t in EXTRA:
    o.append("=== xrefs to extra 0x%05X ===" % t)
    report(t)

open(OUT, "w").write("\n".join(o))
print("XREF_DONE", OUT)
ida_pro.qexit(0)
