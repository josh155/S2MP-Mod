"""RUNS INSIDE IDA (CoD4X). Inspect the call sites of candidate registrars.

x86 cdecl pushes arguments right-to-left, so a registrar call looks like

    push offset cmd_struct
    push offset handler_fn      <- a CODE pointer
    push offset aCmdName        <- a STRING
    call  Cmd_AddCommandInternal

Classifying the pushed operands settles two things at once:
  * WHICH candidate is the command registrar (only it is handed a code pointer)
  * the {name, handler} pairs themselves - tier-1 self-naming evidence, the
    strongest tier there is, because the target binary asserts the pairing

    python re/cod4x_callsites.py 0x4f9950 0x4fcbc0 0x56c350
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, idc, ida_bytes, ida_funcs, ida_name, ida_ua
    targets = __TARGETS__
    starts = set(idautils.Functions())

    def as_string(ea):
        if ea is None:
            return None
        b = ida_bytes.get_bytes(ea, 96)
        if not b:
            return None
        i = b.find(b"\x00")
        if i < 4:
            return None
        s = b[:i]
        try:
            t = s.decode("ascii")
        except Exception:
            return None
        if all(32 <= c < 127 for c in s):
            return t
        return None

    out = {}
    for T in targets:
        rows = []
        for xr in idautils.XrefsTo(T, 0):
            frm = xr.frm
            if not idc.print_insn_mnem(frm).lower().startswith("call"):
                continue
            owner = ida_funcs.get_func(frm)
            pushes = []
            ea = frm
            for _ in range(12):
                ea = idc.prev_head(ea)
                if ea == idc.BADADDR:
                    break
                m = idc.print_insn_mnem(ea).lower()
                if m.startswith("call"):
                    break
                if m == "push":
                    v = idc.get_operand_value(ea, 0)
                    ty = idc.get_operand_type(ea, 0)
                    pushes.append((v, ty))
            args = []
            for v, ty in pushes:
                kind = "imm"
                if v in starts:
                    kind = "func"
                else:
                    s = as_string(v)
                    if s is not None:
                        kind = "str"
                args.append({"v": v, "kind": kind,
                             "s": as_string(v) if kind == "str" else None,
                             "fn": (ida_name.get_name(v) if kind == "func" else None)})
            rows.append({"call": frm,
                         "owner": owner.start_ea if owner else None,
                         "owner_name": ida_name.get_name(owner.start_ea) if owner else None,
                         "args": args})
        out["%x" % T] = rows

    path = os.path.join(r"__RE_DIR__", "cod4x_callsites.json")
    with open(path, "w", encoding="utf-8") as f:
        json.dump(out, f)
    return {k: {"sites": len(v),
                "with_func_arg": sum(1 for r in v
                                     if any(a["kind"] == "func" for a in r["args"])),
                "with_str_arg": sum(1 for r in v
                                    if any(a["kind"] == "str" for a in r["args"]))}
            for k, v in out.items()}
main()
'''

targets = [int(a, 16) for a in sys.argv[1:]]
code = CODE.replace("__TARGETS__", repr(targets)).replace("__RE_DIR__", RE_DIR)
r = pyeval(PORTS["cod4x"], code, timeout=900)
print(json.dumps(r, indent=2) if not isinstance(r, str) else r[:2000])

d = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "cod4x_callsites.json"), encoding="utf-8"))
for t, rows in d.items():
    print(f"\n===== 0x{t} : {len(rows)} call sites =====")
    for row in rows[:6]:
        desc = " | ".join(
            (f"str {a['s']!r}" if a["kind"] == "str" else
             f"FUNC {a['fn']}" if a["kind"] == "func" else
             f"imm 0x{a['v']:x}") for a in row["args"])
        print(f"  from {row['owner_name']}: {desc}")
