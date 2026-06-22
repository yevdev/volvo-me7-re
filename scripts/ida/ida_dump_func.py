# Dump full C166 disassembly of one or more functions, annotated with resolved
# calibration data refs (CAL->) and call targets (CALL), plus callers.
# Usage: idat.exe -A -S"ida_dump_func.py <out.txt> <hexaddr> [hexaddr...]" <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "ida_dump.txt"
ADDRS = [int(a, 16) for a in argv[2:]]
o = []

def dump(ea):
    f = ida_funcs.get_func(ea)
    if not f:
        o.append("NO FUNC at 0x%X" % ea); return
    callers = sorted(set(idc.get_func_name(x.frm) for x in idautils.XrefsTo(f.start_ea) if x.frm and idc.get_func_name(x.frm)))
    o.append("\n===== sub_%05X  (0x%05X-0x%05X) =====" % (f.start_ea, f.start_ea, f.end_ea))
    o.append("CALLERS: " + ", ".join(callers)[:400])
    cur = f.start_ea
    while cur < f.end_ea:
        dis = idc.generate_disasm_line(cur, 0) or ""
        drefs = [hex(x) for x in idautils.DataRefsFrom(cur) if 0x10000 <= x < 0x2D000]
        crefs = [idc.get_func_name(x) for x in idautils.CodeRefsFrom(cur, 0) if x < f.start_ea or x >= f.end_ea]
        ex = ""
        if drefs: ex += "   ; CAL->" + ",".join(drefs)
        crefs = [c for c in crefs if c]
        if crefs: ex += "   ; CALL " + ",".join(crefs)
        o.append("  0x%05X  %s%s" % (cur, dis, ex))
        nh = idc.next_head(cur, f.end_ea)
        cur = nh if nh > cur else cur + 2

for a in ADDRS:
    dump(a)
open(OUT, "w").write("\n".join(o))
print("DUMP_DONE", OUT, "funcs=%d" % len(ADDRS))
ida_pro.qexit(0)
