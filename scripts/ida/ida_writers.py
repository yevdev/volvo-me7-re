# Find code that writes (and reads) given data addresses. Reports func + disasm.
# Usage: idat.exe -A -S"ida_writers.py <out.txt> <addr1> [addr2...]" <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "ida_w.txt"
ADDRS = [int(a, 16) for a in argv[2:]]
o = []
for t in ADDRS:
    o.append("=== xrefs to 0x%X ===" % t)
    for x in idautils.XrefsTo(t, 0):
        frm = x.frm
        fn = idc.get_func_name(frm) or "?"
        dis = idc.generate_disasm_line(frm, 0) or ""
        o.append("  0x%05X  type=%d func=%s  | %s" % (frm, x.type, fn, dis))
open(OUT, "w").write("\n".join(o))
print("W_DONE", OUT)
ida_pro.qexit(0)
