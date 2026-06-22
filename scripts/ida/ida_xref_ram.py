# Find readers/writers of given RAM/data addresses and callers of given funcs.
# Usage: idat.exe -A -S"ida_xref_ram.py <out.txt> <hexaddr>..." <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1]
ADDRS = [int(a, 16) for a in argv[2:]]
o = []
for a in ADDRS:
    nm = idc.get_name(a) or ("0x%X" % a)
    o.append("\n===== XREFS to 0x%X (%s) =====" % (a, nm))
    seen = []
    for x in idautils.XrefsTo(a):
        fn = idc.get_func_name(x.frm) or "?"
        dis = idc.generate_disasm_line(x.frm, 0) or ""
        o.append("  0x%05X  %-16s %s" % (x.frm, fn, dis))
    # also callers if a is a func
    f = ida_funcs.get_func(a)
    if f and f.start_ea == a:
        callers = sorted(set(idc.get_func_name(x.frm) for x in idautils.XrefsTo(a) if idc.get_func_name(x.frm)))
        o.append("  CALLERS: " + ", ".join(callers))
open(OUT, "w").write("\n".join(o))
print("DONE", OUT)
ida_pro.qexit(0)
