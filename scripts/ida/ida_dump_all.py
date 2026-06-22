# Dump annotated disassembly of EVERY function in the database (CAL-> data refs,
# CALL targets, callers). Big output; gzip it after. This is the full-image listing.
# Run: idat.exe -A -S"ida_dump_all.py <out.txt>" <me7_carve.i64>
import ida_auto, idc, idautils, ida_funcs, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else r"all_functions.txt"
o = []
for f in idautils.Functions():
    end = idc.find_func_end(f)
    callers = sorted(set(idc.get_func_name(x) for x in idautils.CodeRefsTo(f, 0) if idc.get_func_name(x)))
    o.append("\n===== %s  (0x%05X-0x%05X)  callers=%d =====" % (idc.get_func_name(f), f, end, len(callers)))
    cur = f
    while cur < end:
        dis = idc.generate_disasm_line(cur, 0) or ""
        drefs = [hex(x) for x in idautils.DataRefsFrom(cur) if 0x10000 <= x < 0x2D000]
        crefs = [idc.get_func_name(x) for x in idautils.CodeRefsFrom(cur, 0) if (x < f or x >= end)]
        ex = ""
        if drefs: ex += "  ; CAL->" + ",".join(drefs)
        crefs = [c for c in crefs if c]
        if crefs: ex += "  ; CALL " + ",".join(crefs)
        o.append("  0x%05X  %s%s" % (cur, dis, ex))
        nh = idc.next_head(cur, end)
        cur = nh if nh > cur else cur + 2
    if len(o) > 1500000:
        o.append("... (output cap reached)"); break
open(OUT, "w").write("\n".join(o))
print("DUMP_ALL_DONE lines=%d" % len(o))
ida_pro.qexit(0)
