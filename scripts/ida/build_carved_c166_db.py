# Build a carved IDA C166 database for a Volvo ME7.0 (Infineon C167CR) ROM.
# Loads the raw 1 MB bin at base 0 with the C166 processor, seeds the DPP page
# registers (so segmented data accesses resolve into real listing xrefs), adds the
# RAM segment, then aggressively carves code (skipping the calibration band) so the
# map data-references appear. Output: me7_carve.i64.
#
# Run:  idat.exe -A -c -pC166 -TBinary -b0 -S"build_carved_c166_db.py" <me7_rom.bin>
import ida_auto, idc, idautils, ida_funcs, ida_bytes, ida_ua, ida_segment, ida_loader, ida_pro
ida_auto.auto_wait()
# ME7 startup DPP page values (DPPn -> physical page); confirmed for this family.
for reg, val in (("DPP0", 4), ("DPP1", 5), ("DPP2", 0xC0), ("DPP3", 3)):
    idc.set_default_sreg_value(0x0, reg, val)
# External RAM window (DPP2=0xC0 -> 0xC0<<14 = 0x300000)
if not ida_segment.getseg(0x300000):
    ida_segment.add_segm(0x30000, 0x300000, 0x310000, "RAM", "DATA")
# Carve code outside the calibration/map band (~0x10000-0x2D000 on this image).
CAL_LO, CAL_HI, ROM_END = 0x10000, 0x2D000, 0x100000
ea = 0
while ea < ROM_END:
    if CAL_LO <= ea < CAL_HI:
        ea = CAL_HI; continue
    fl = ida_bytes.get_flags(ea)
    if not ida_bytes.is_code(fl) and not ida_bytes.is_data(fl):
        if ida_ua.create_insn(ea) == 0:
            ea += 2; continue
    if ida_bytes.is_code(ida_bytes.get_flags(ea)):
        if not ida_funcs.get_func(ea):
            ida_funcs.add_func(ea)
        sz = idc.get_item_size(ea)
        ea += sz if sz > 0 else 2
    else:
        ea += 2
ida_auto.auto_wait()
ida_loader.save_database(r"me7_carve.i64", 0)
print("C166_DB_DONE funcs=%d" % len(list(idautils.Functions())))
ida_pro.qexit(0)
