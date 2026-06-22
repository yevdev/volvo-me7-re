# Apply the ME7 name/comment database (map_names.csv, function_names.csv, ram_names.csv)
# to the currently-open IDA database. Use after building a carved C166 db, or call
# from ida_me7_load.py. Names are 50GPHJ-specific (addresses match the GPHJ ROM layout).
# Run: idat.exe -A -S"ida_apply_names.py <loadkit_dir>" <me7_carve.i64>
import ida_auto, idc, ida_name, ida_pro, csv, os
ida_auto.auto_wait()
argv = idc.ARGV
D = argv[1] if len(argv) > 1 else os.path.dirname(__file__)

def apply(fn):
    p = os.path.join(D, fn)
    if not os.path.exists(p):
        print("MISSING " + p); return 0
    n = 0
    with open(p, newline='') as f:
        for row in csv.DictReader(f):
            try:
                ea = int(row["addr"], 16)
            except Exception:
                continue
            nm = (row.get("name") or "").strip()
            if nm and ida_name.set_name(ea, nm, ida_name.SN_CHECK | ida_name.SN_FORCE):
                n += 1
            cmt = (row.get("comment") or "").strip()
            if cmt:
                idc.set_cmt(ea, cmt, False)
    return n

total = 0
for fn in ("function_names.csv", "ram_names.csv", "map_names.csv"):
    c = apply(fn); total += c; print("applied %d from %s" % (c, fn))
print("APPLY_NAMES_DONE total=%d" % total)
ida_pro.qexit(0)
