# ONE-SHOT high-fidelity loader for a Volvo ME7.0 (50GPHJ) C166 ROM in IDA.
# Sets DPP page regs + RAM segment, carves code, then applies the name/comment DB
# (map_names/function_names/ram_names .csv in this folder) -> a richly annotated db.
#
# Run on a RAW bin:
#   idat.exe -A -c -pC166 -TBinary -b0 -S"ida_me7_load.py <loadkit_dir>" <me7_rom.bin>
# (loadkit_dir = folder holding the three *_names.csv; defaults to the script's folder)
import ida_auto, idc, idautils, ida_funcs, ida_bytes, ida_ua, ida_segment, ida_loader, ida_name, ida_pro, csv, os
ida_auto.auto_wait()
argv = idc.ARGV
D = argv[1] if len(argv) > 1 else os.path.dirname(__file__)

# 1) DPP page regs + RAM window
for reg, val in (("DPP0", 4), ("DPP1", 5), ("DPP2", 0xC0), ("DPP3", 3)):
    idc.set_default_sreg_value(0x0, reg, val)
if not ida_segment.getseg(0x300000):
    ida_segment.add_segm(0x30000, 0x300000, 0x310000, "RAM", "DATA")

# 2) carve code outside the calibration band
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

# 3) apply names + comments
def apply(fn):
    p = os.path.join(D, fn)
    if not os.path.exists(p):
        return 0
    n = 0
    with open(p, newline='') as f:
        for row in csv.DictReader(f):
            try:
                a = int(row["addr"], 16)
            except Exception:
                continue
            nm = (row.get("name") or "").strip()
            if nm and ida_name.set_name(a, nm, ida_name.SN_CHECK | ida_name.SN_FORCE):
                n += 1
            cmt = (row.get("comment") or "").strip()
            if cmt:
                idc.set_cmt(a, cmt, False)
    return n
named = sum(apply(f) for f in ("function_names.csv", "ram_names.csv", "map_names.csv"))

ida_auto.auto_wait()
ida_loader.save_database(r"me7_annotated.i64", 0)
print("ME7_LOAD_DONE functions=%d names_applied=%d" % (len(list(idautils.Functions())), named))
ida_pro.qexit(0)
