# Enumerate callers of the ME7 BYTE map-lookup routines and the map pointer loaded
# before each call. Two conventions:
#   sub_411F4 (2-D sbyte bilinear): r12 = z-offset, page is FIXED (page 4 for KFZW);
#       r13 = axis-descriptor block ptr (NOT a page). phys = (PAGE411F4<<14)|r12.
#   sub_419F4 (1-D byte): uses extp r13 -> r13 IS the page, r12 = offset.
#       phys = (r13<<14)|r12  (same as sub_41A68).
# Usage: idat.exe -A -S"ida_bytemap_callers.py <out.txt> <lookup_hex> <mode> [fixed_page_hex]" <db.i64>
#   mode = "page"  -> r13 is page (sub_419F4 / sub_41A68 style)
#   mode = "fixed" -> r12 is offset, page = fixed_page_hex (sub_411F4 style)
import ida_auto, idc, idautils, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1] if len(argv) > 1 else "bytemap_callers.txt"
LOOKUP = int(argv[2], 16) if len(argv) > 2 else 0x419F4
MODE = argv[3] if len(argv) > 3 else "page"
FIXED_PAGE = int(argv[4], 16) if len(argv) > 4 else 4

rows = []
total = 0
for x in idautils.XrefsTo(LOOKUP):
    if not idc.is_code(idc.get_full_flags(x.frm)):
        continue
    total += 1
    frm = x.frm
    off = page = r13imm = None
    ea = frm
    for _ in range(12):
        ea = idc.prev_head(ea, 0)
        if ea == idc.BADADDR:
            break
        if idc.print_insn_mnem(ea) == "mov":
            o0 = idc.print_operand(ea, 0)
            if idc.get_operand_type(ea, 1) == idc.o_imm:
                v = idc.get_operand_value(ea, 1) & 0xFFFF
                if o0 == "r12" and off is None:    off = v
                if o0 == "r13" and r13imm is None: r13imm = v
        if off is not None and r13imm is not None:
            break
    fn = idc.get_func_name(frm)
    if off is None:
        continue
    if MODE == "fixed":
        page = FIXED_PAGE
        phys = (page << 14) | off
        axisptr = r13imm
    else:
        page = r13imm
        if page is None:
            continue
        phys = (page << 14) | off
        axisptr = None
    rows.append((phys, off, page, axisptr, frm, fn))

rows.sort()
hdr = "# phys_addr  offset  page  %s  caller_ea  caller_func   (lookup=0x%X, mode=%s, %d resolved / %d xrefs)" % (
    ("axisptr" if MODE == "fixed" else "       "), LOOKUP, MODE, len(rows), total)
lines = [hdr]
for phys, off, page, axisptr, frm, fn in rows:
    ap = ("0x%04X " % axisptr) if axisptr is not None else "       "
    lines.append("0x%05X  0x%04X  %X  %s  0x%05X  %s" % (phys, off, page, ap, frm, fn))
open(OUT, "w").write("\n".join(lines))
print("BYTEMAP_DONE count=%d total_xrefs=%d lookup=0x%X mode=%s" % (len(rows), total, LOOKUP, MODE))
ida_pro.qexit(0)
