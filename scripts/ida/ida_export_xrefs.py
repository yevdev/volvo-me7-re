# Export the FULL function inventory + call graph + data touch-points for a carved
# ME7 C166 database. First closes the function set (make a function at every call
# target), then writes: functions.csv (one row/function with caller/callee/cal/ram
# touch-point counts + lists) and callgraph.csv (caller->callee edges).
# Run: idat.exe -A -S"ida_export_xrefs.py <out_dir>" <me7_carve.i64>
import ida_auto, idc, idautils, ida_funcs, ida_bytes, ida_pro, os
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else r"."

CAL_LO, CAL_HI = 0x10000, 0x2D000

# 1) close the function set: make a function at every call target that isn't one yet
added = 1
while added:
    added = 0
    for f in list(idautils.Functions()):
        for item in idautils.FuncItems(f):
            if idc.print_insn_mnem(item).startswith("call"):
                for t in idautils.CodeRefsFrom(item, 0):
                    if t < f or t >= idc.find_func_end(f):
                        if ida_funcs.get_func(t) is None and ida_bytes.is_code(ida_bytes.get_flags(t)):
                            if ida_funcs.add_func(t):
                                added += 1
    ida_auto.auto_wait()

funcs = list(idautils.Functions())
frows = ["ea,name,size,n_callers,n_callees,n_cal_refs,n_ram_refs,cal_refs,callees"]
edges = ["caller_ea,caller,callee_ea,callee"]
for f in funcs:
    name = idc.get_func_name(f)
    end = idc.find_func_end(f)
    callees, cal, ram = set(), set(), set()
    for item in idautils.FuncItems(f):
        for x in idautils.CodeRefsFrom(item, 0):
            if x < f or x >= end:
                callees.add(x)
        for x in idautils.DataRefsFrom(item):
            if CAL_LO <= x < CAL_HI: cal.add(x)
            elif x >= 0xF000: ram.add(x)
    callers = set(x for x in idautils.CodeRefsTo(f, 0))
    for c in callees:
        edges.append("0x%05X,%s,0x%05X,%s" % (f, name, c, idc.get_func_name(c) or ""))
    frows.append("0x%05X,%s,%d,%d,%d,%d,%d,%s,%s" % (
        f, name, max(0, end - f), len(callers), len(callees), len(cal), len(ram),
        " ".join("0x%05X" % a for a in sorted(cal)),
        " ".join((idc.get_func_name(c) or "?") for c in sorted(callees))))
open(os.path.join(OUT, "functions.csv"), "w").write("\n".join(frows))
open(os.path.join(OUT, "callgraph.csv"), "w").write("\n".join(edges))
print("EXPORT_DONE functions=%d edges=%d" % (len(funcs), len(edges) - 1))
ida_pro.qexit(0)
