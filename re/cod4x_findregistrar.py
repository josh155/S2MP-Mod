"""RUNS INSIDE IDA (CoD4X). Find registrars by SIGNATURE, not by name mapping.

A registrar is handed a callback. So scan every `push offset <function-start>`
and tally which function is called just after it. The winner takes function
pointers for a living - Cmd_AddCommandInternal, Cmd_SetAutoComplete, thread
starts, and so on.

This is target-only evidence: it does not depend on the reference build at all,
and the {name, handler} pairs it recovers are tier-1 self-naming - the target
binary asserts the pairing itself.

    python re/cod4x_findregistrar.py
writes re/cod4x_registrars.json
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, idc, ida_bytes, ida_funcs, ida_name, ida_segment

    starts = set(idautils.Functions())
    code_lo = code_hi = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        if ida_segment.get_segm_name(seg) == ".text":
            code_lo, code_hi = seg.start_ea, seg.end_ea

    def as_string(ea):
        b = ida_bytes.get_bytes(ea, 128)
        if not b:
            return None
        i = b.find(b"\x00")
        if i < 3:
            return None
        s = b[:i]
        if all(32 <= c < 127 or c == 9 for c in s):
            try:
                return s.decode("ascii")
            except Exception:
                return None
        return None

    # 1. every push of a function pointer -> which call follows
    tally = {}
    records = {}
    for f in list(starts):
        for ea in idautils.FuncItems(f):
            if idc.print_insn_mnem(ea).lower() != "push":
                continue
            if idc.get_operand_type(ea, 0) not in (idc.o_imm, idc.o_mem):
                continue
            v = idc.get_operand_value(ea, 0)
            if v not in starts:
                continue
            # look ahead for the call
            nxt = ea
            target = None
            pushes = [v]
            for _ in range(10):
                nxt = idc.next_head(nxt)
                if nxt == idc.BADADDR or nxt >= code_hi:
                    break
                m = idc.print_insn_mnem(nxt).lower()
                if m == "push":
                    pushes.append(idc.get_operand_value(nxt, 0))
                    continue
                if m.startswith("call"):
                    t = idc.get_operand_value(nxt, 0)
                    if t in starts:
                        target = t
                    break
                if m.startswith(("j", "ret")):
                    break
            if target is None:
                continue
            tally[target] = tally.get(target, 0) + 1
            # keep the (string, handler) pairing for this site
            names = [as_string(p) for p in pushes]
            names = [n for n in names if n]
            records.setdefault(target, []).append(
                {"call": nxt, "handler": v,
                 "handler_name": ida_name.get_name(v),
                 "strings": names[:3],
                 "owner": (ida_funcs.get_func(ea).start_ea
                           if ida_funcs.get_func(ea) else None)})

    top = sorted(tally.items(), key=lambda kv: -kv[1])[:15]
    path = os.path.join(r"__RE_DIR__", "cod4x_registrars.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump({"%x" % k: v for k, v in records.items()}, fh)
    return [{"target": "%x" % t, "name": ida_name.get_name(t), "sites": n,
             "with_string": sum(1 for r in records[t] if r["strings"])}
            for t, n in top]
main()
'''.replace("__RE_DIR__", RE_DIR)

r = pyeval(PORTS["cod4x"], CODE, timeout=1800)
if isinstance(r, str):
    print(r[:3000]); sys.exit(1)
print(f"{'target':>10} {'sites':>6} {'w/str':>6}  name")
for row in r:
    print(f"  0x{row['target']:>8} {row['sites']:>6} {row['with_string']:>6}  "
          f"{row['name']}")

d = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "cod4x_registrars.json"), encoding="utf-8"))
for row in r[:4]:
    rows = d[row["target"]]
    print(f"\n===== 0x{row['target']} ({row['name']}) sample sites =====")
    for x in rows[:10]:
        print(f"  {x['strings']}  ->  {x['handler_name']}")
