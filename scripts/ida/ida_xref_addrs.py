# Find code xrefs to a set of data addresses, and callers of a set of funcs.
# Usage: idat.exe -A -S"ida_xref_addrs.py <out.txt> X:<hexaddr>... C:<hexfunc>..." <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "ida_xref.txt"
o = []
for a in argv[2:]:
    kind, val = a[0], int(a[2:], 16)
    if kind == 'X':
        o.append("\n=== XREFS TO data 0x%05X ===" % val)
        for x in idautils.XrefsTo(val):
            fn = idc.get_func_name(x.frm)
            o.append("  from 0x%05X  %s   %s" % (x.frm, fn or "?", idc.generate_disasm_line(x.frm,0) or ""))
    elif kind == 'C':
        f = ida_funcs.get_func(val)
        o.append("\n=== CALLERS of sub_%05X ===" % val)
        for x in idautils.XrefsTo(val):
            fn = idc.get_func_name(x.frm)
            o.append("  from 0x%05X  %s   %s" % (x.frm, fn or "?", idc.generate_disasm_line(x.frm,0) or ""))
open(OUT,"w").write("\n".join(o))
print("XREF_DONE", OUT)
ida_pro.qexit(0)
