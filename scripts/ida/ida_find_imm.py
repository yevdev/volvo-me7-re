# Scan all code for instructions referencing given immediate values (map offsets/pages)
# and report the function + surrounding context.
# Usage: idat.exe -A -S"ida_find_imm.py <out.txt> <imm1> [imm2...]" <db.i64>
import ida_auto, idc, idautils, ida_funcs, ida_bytes, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "ida_imm.txt"
IMMS = set(int(a, 16) for a in argv[2:])
o = []
o.append("=== scanning for immediates: %s ===" % ",".join(hex(i) for i in IMMS))

for seg_ea in idautils.Segments():
    seg_end = idc.get_segm_end(seg_ea)
    ea = seg_ea
    while ea < seg_end:
        if idc.is_code(ida_bytes.get_full_flags(ea)):
            for opn in range(4):
                t = idc.get_operand_type(ea, opn)
                if t == idc.o_imm:
                    v = idc.get_operand_value(ea, opn)
                    if v in IMMS:
                        fn = idc.get_func_name(ea) or "?"
                        dis = idc.generate_disasm_line(ea, 0) or ""
                        o.append("  0x%05X  func=%s  imm=0x%X  | %s" % (ea, fn, v, dis))
        nh = idc.next_head(ea, seg_end)
        ea = nh if nh > ea else ea + 1

open(OUT, "w").write("\n".join(o))
print("IMM_DONE", OUT, "lines=%d" % len(o))
ida_pro.qexit(0)
