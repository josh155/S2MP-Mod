import json, os
RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
def main():
    import ida_name, ida_funcs
    rows = json.load(open(os.path.join(RE_DIR, "mwrpc_propagated2.json"), encoding="utf-8"))
    applied, failed = [], []
    for r in rows:
        ea, name = r["pc"], r["name"]
        cur = ida_name.get_name(ea)
        if cur and not (cur.startswith("sub_") or cur.startswith("nullsub_") or cur.startswith("j_")):
            continue
        if not ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK):
            failed.append([hex(ea), name]); continue
        cmt = (f"{name}\n"
               f"BASIS: same-game CALL-GRAPH propagation from MWR-PS4 (port 9999), round 2.\n"
               f"  {r['support']} independently-mapped neighbour(s) intersect to exactly ONE\n"
               f"  PS4 candidate: {hex(r['ps4'])}. Uses NO string evidence.\n"
               f"  seeds for this round: string anchors + round-1 propagation + binding tables.\n"
               f"  measured precision of this method on a held-out slice: 98.4% (123/125).\n"
               f"  sizes pc={r['pc_size']} ps4={r['ps4_size']} - size is NOT a validity signal\n"
               f"  (debug-vs-release; gating on it measurably LOWERS precision).\n"
               f"NOTE: cross-binary port - only the NAME transfers, addresses differ.")
        ida_funcs.set_func_cmt(ida_funcs.get_func(ea), cmt, 1)
        applied.append([hex(ea), name])
    json.dump({"applied": applied, "failed": failed},
              open(os.path.join(RE_DIR, "mwrpc_applied_prop2.json"), "w", encoding="utf-8"))
    return {"applied": len(applied), "failed": len(failed)}
main()
