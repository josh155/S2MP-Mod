"""Sanity probe: do two IDBs share string literals, and where do they live?

    python re/strprobe.py cod4 cod4x
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

PROBES = [
    "CL_ParseGamestate", "cg_fov", "sv_maxclients", "CL_SystemInfoChanged",
    "com_maxfps", "Com_Error", "SV_SpawnServer", "cl_paused",
    "MSG_ReadBits", "usercmd_t", "clientinfo", "EXE_SERVER_IS_DIFFERENT_VER",
    "Bad cmd string", "Server disconnected", "connect",
]

CODE = r'''
def main():
    import idautils, ida_bytes, ida_segment, ida_funcs
    MIN_LEN = 4
    probes = __PROBES__
    out = {"segs": [], "hits": {}, "distinct": 0}
    strmap = {}
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        nm = ida_segment.get_segm_name(seg)
        size = seg.end_ea - seg.start_ea
        if nm in ("__bss", "__common", "UNDEF", "ABS", ".tls", "HEADER"):
            out["segs"].append((nm, size, "skip-uninit")); continue
        if size > 64*1024*1024:
            out["segs"].append((nm, size, "skip-huge")); continue
        buf = ida_bytes.get_bytes(seg.start_ea, size)
        if not buf:
            out["segs"].append((nm, size, "no-bytes")); continue
        n0 = len(strmap)
        start = None
        for i, b in enumerate(buf):
            if 32 <= b < 127 or b == 9:
                if start is None:
                    start = i
            else:
                if start is not None and b == 0 and i - start >= MIN_LEN:
                    strmap.setdefault(buf[start:i].decode("ascii","replace"),
                                      []).append(seg.start_ea + start)
                start = None
        out["segs"].append((nm, size, "scanned +%d" % (len(strmap)-n0)))
    out["distinct"] = len(strmap)
    for p in probes:
        addrs = strmap.get(p)
        if not addrs:
            # substring fallback so we can tell "absent" from "different framing"
            sub = [k for k in strmap if p in k][:2]
            out["hits"][p] = {"exact": 0, "substr": sub}
            continue
        owners = set()
        for a in addrs:
            for xr in idautils.XrefsTo(a, 0):
                f = ida_funcs.get_func(xr.frm)
                if f:
                    owners.add(f.start_ea)
        out["hits"][p] = {"exact": len(addrs), "owners": len(owners)}
    return out
main()
'''.replace("__PROBES__", repr(PROBES))

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    r = pyeval(port, CODE, timeout=600)
    if isinstance(r, str):
        print(key, "ERROR:", r[:800]); continue
    print(f"===== {key} (port {port}) =====")
    print(f"  distinct strings: {r['distinct']:,}")
    for nm, size, note in r["segs"]:
        print(f"    {nm:16} {size/1048576:8.2f} MB  {note}")
    for p, h in r["hits"].items():
        if h.get("exact"):
            print(f"    OK   {p!r:44} addrs={h['exact']} owners={h['owners']}")
        else:
            print(f"    --   {p!r:44} substr={h['substr']}")
    print()
