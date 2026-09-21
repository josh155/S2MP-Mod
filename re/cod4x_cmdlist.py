"""RUNS INSIDE IDA (CoD4X). Walk the LIVE command linked-lists in the dump.

iw3mp_dump.exe is a dump of a RUNNING process, so the command tables in .data are
already populated. That makes this the strongest possible evidence: the running
game itself pairs each command name with its handler.

Layout, read from Cmd_AddServerCommandInternal @0x4f9140 (which names itself in
its own error string "Cmd_AddServerCommand: %s already defined"):

    a3[0] = next        cmd_function_s +0
    a3[1] = name        cmd_function_s +4
    a3[4] = function    cmd_function_s +16

List heads, from that function and from the inlined Cmd_AddCommand in
SV_AddOperatorCommands:

    dword_14099DC   server/operator command list
    off_1410B3C     client command list

Handlers are named "<command>_f" - the engine's own convention, independently
confirmed by SV_Status_f / CL_PlayDemo_f which the anchor pass established.

    python re/cod4x_cmdlist.py [--apply]
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")
APPLY = "--apply" in sys.argv

CODE = r'''
def main():
    import json, os, idautils, ida_bytes, ida_funcs, ida_name, ida_segment

    HEADS = {"server_0x14099DC": 0x14099DC, "client_0x1410B3C": 0x1410B3C}
    starts = set(idautils.Functions())

    lo = hi = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if ida_segment.get_segm_name(seg) == ".text":
            lo, hi = seg.start_ea, seg.end_ea

    def rd32(ea):
        try:
            return ida_bytes.get_wide_dword(ea)
        except Exception:
            return None

    def cstr(ea):
        if not ea:
            return None
        b = ida_bytes.get_bytes(ea, 96)
        if not b:
            return None
        i = b.find(b"\x00")
        if i < 1:
            return None
        s = b[:i]
        if not all(32 <= c < 127 for c in s):
            return None
        try:
            return s.decode("ascii")
        except Exception:
            return None

    out = {}
    for label, head in HEADS.items():
        rows, seen, node = [], set(), rd32(head)
        while node and node not in seen and len(rows) < 2000:
            seen.add(node)
            nm = cstr(rd32(node + 4))
            fn = rd32(node + 16)
            rows.append({"node": node, "name": nm, "fn": fn,
                         "fn_is_func": bool(fn and fn in starts),
                         "fn_in_text": bool(fn and lo and lo <= fn < hi),
                         "fn_name": ida_name.get_name(fn) if fn else None})
            node = rd32(node)
        out[label] = rows

    path = os.path.join(r"__RE_DIR__", "cod4x_cmdlist.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(out, fh)
    return {k: {"entries": len(v),
                "named": sum(1 for r in v if r["name"]),
                "handler_is_func": sum(1 for r in v if r["fn_is_func"])}
            for k, v in out.items()}
main()
'''.replace("__RE_DIR__", RE_DIR)

print(pyeval(PORTS["cod4x"], CODE, timeout=900))

d = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "cod4x_cmdlist.json"), encoding="utf-8"))

agree, differ, plan = 0, [], {}
for label, rows in d.items():
    print(f"\n===== {label}: {len(rows)} entries =====")
    for r in rows:
        cur = r["fn_name"] or "-"
        mark = ""
        if r["name"] and r["fn_is_func"]:
            want = "".join(c if (c.isalnum() or c == "_") else "_"
                           for c in r["name"]) + "_f"
            named = not cur.startswith(("sub_", "nullsub", "j_", "unknown_", "-"))
            if named:
                if cur.lower() == want.lower():
                    agree += 1
                    mark = "  <= AGREES with the anchor pass"
                else:
                    differ.append((r["name"], cur, want))
                    mark = f"  <= already {cur}, expected {want}"
            else:
                plan.setdefault(str(r["fn"]), {"name": want, "cmd": r["name"],
                                               "node": r["node"], "list": label})
        print(f"  {str(r['name']):<26} "
              f"{('0x%x' % r['fn']) if r['fn'] else '-':<11} {cur:<26}{mark}")

print(f"\nhandlers already named that AGREE with <cmd>_f : {agree}")
print(f"handlers already named that DIFFER            : {len(differ)}")
for c, cur, want in differ:
    print(f"   cmd {c!r}: already {cur}, convention would be {want}")
print(f"new names available                            : {len(plan)}")

json.dump(plan, open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                  "cod4x_cmd_plan_raw.json"), "w",
                     encoding="utf-8"))
