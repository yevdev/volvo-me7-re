# Enumerate every caller of the ME7 map-lookup routine sub_41A68 and the (offset,page)
# map pointer loaded just before each call -> master (physical map addr -> caller func) table.
# Usage: idat.exe -A -S"ida_lookup_callers.py <out.txt> [lookup_hex]" <db.i64>
import ida_auto, idc, idautils, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "lookup_callers.txt"
LOOKUP = int(argv[2], 16) if len(argv) > 2 else 0x41A68

rows = []
for x in idautils.XrefsTo(LOOKUP):
    frm = x.frm
    if not idc.is_code(idc.get_full_flags(frm)):
        continue
    off = page = None
    ea = frm
    for _ in range(10):
        ea = idc.prev_head(ea, 0)
        if ea == idc.BADADDR:
            break
        if idc.print_insn_mnem(ea) == "mov":
            o0 = idc.print_operand(ea, 0)
            if idc.get_operand_type(ea, 1) == idc.o_imm:
                if o0 == "r12" and off is None:  off = idc.get_operand_value(ea, 1) & 0xFFFF
                if o0 == "r13" and page is None: page = idc.get_operand_value(ea, 1) & 0xFFFF
        if off is not None and page is not None:
            break
    fn = idc.get_func_name(frm)
    if off is not None and page is not None:
        rows.append(((page << 14) | off, off, page, frm, fn))
rows.sort()
lines = ["# phys_addr  offset  page  caller_ea  caller_func   (lookup=0x%X, %d resolved calls)" % (LOOKUP, len(rows))]
for phys, off, page, frm, fn in rows:
    lines.append("0x%05X  0x%04X  %X  0x%05X  %s" % (phys, off, page, frm, fn))
open(OUT, "w").write("\n".join(lines))
print("LOOKUP_CALLERS_DONE count=%d total_xrefs=%d" % (len(rows), len(list(idautils.XrefsTo(LOOKUP)))))
ida_pro.qexit(0)
