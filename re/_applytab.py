import json, os
RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
def main():
    import ida_name, ida_funcs
    rows = json.load(open(os.path.join(RE_DIR, "mwrpc_table_names.json"), encoding="utf-8"))
    applied, failed = [], []
    for k, r in rows.items():
        ea = int(k); name = r["name"]
        cur = ida_name.get_name(ea)
        if cur and not (cur.startswith("sub_") or cur.startswith("nullsub_") or cur.startswith("j_")):
            continue
        if not ida_name.set_name(ea, name, ida_name.SN_NOWARN | ida_name.SN_NOCHECK):
            failed.append([hex(ea), name]); continue
        cmt = (f"{name}\n"
               f"BASIS: self-naming binding table, matched table-to-table with MWR-PS4.\n"
               f"  PC table {r["pc_table"]} pairs the binding string {r['binding']!r} "
               f"directly with THIS function ({{const char* name, void* fn}}, stride 16).\n"
               f"  that table corresponds to PS4 table {r['ps4_table']} "
               f"(shared binding names: {r['shared']}, ratio {r['ratio']}), where the same\n"
               f"  binding resolves to the real symbol above.\n"
               f"  entries matched ONLY inside a corresponding table pair, never by bare name.\n"
               f"  alignment settled empirically: name+0/fn+8 agrees with independently\n"
               f"  derived names, the name+8/fn+0 reading agrees 0%.\n"
               f"  method validated 43/43 (100%) against string-anchor and call-graph names.\n"
               f"NOTE: this is a LUA MARSHALLER - it unpacks Lua args and calls the real worker.")
        ida_funcs.set_func_cmt(ida_funcs.get_func(ea), cmt, 1)
        applied.append([hex(ea), name])
    json.dump({"applied": applied, "failed": failed},
              open(os.path.join(RE_DIR, "mwrpc_applied_tables.json"), "w", encoding="utf-8"))
    return {"applied": len(applied), "failed": len(failed)}
main()
