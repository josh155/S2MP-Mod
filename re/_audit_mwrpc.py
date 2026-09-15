import json, os, collections
RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
def main():
    import idautils, ida_name, ida_funcs, ida_segment
    lo = hi = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if seg.perm & ida_segment.SEGPERM_EXEC and lo is None:
            lo, hi = seg.start_ea, seg.end_ea
    rows = []
    for ea in idautils.Functions():
        if not (lo <= ea < hi): continue
        n = ida_name.get_name(ea)
        if not n or n.startswith("sub_") or n.startswith("nullsub_") or n.startswith("j_"):
            continue
        f = ida_funcs.get_func(ea)
        c = ida_funcs.get_func_cmt(f, 1) or ""
        rows.append([hex(ea), n, c, f.end_ea - f.start_ea])
    json.dump(rows, open(os.path.join(RE_DIR, "mwrpc_audit_rows.json"), "w", encoding="utf-8"))
    return len(rows)
main()
