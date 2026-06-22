# Resolve names + repeatable comments at given addresses; also dump a caller function.
import ida_auto, idc, idautils, ida_funcs, ida_bytes, ida_name, ida_pro
ida_auto.auto_wait()
argv = idc.ARGV
OUT = argv[1]
ADDRS = [int(a,16) for a in argv[2:]]
o=[]
for a in ADDRS:
    nm = ida_name.get_name(a) or ""
    cmt = idc.get_cmt(a,1) or idc.get_cmt(a,0) or ""
    # try word value at addr (calibration little-endian word)
    try:
        w = ida_bytes.get_word(a)
    except Exception:
        w = -1
    o.append("0x%05X  name=%-18s word=0x%04X(%d)  cmt=%s" % (a, nm, w & 0xFFFF, w, cmt))
open(OUT,"w").write("\n".join(o))
print("RESOLVE_DONE")
ida_pro.qexit(0)
