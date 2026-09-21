"""Cross-check re/demangle_itanium.py against IDA's own demangler.

Never trust a hand-written parser alone. IDA dumps {mangled: demangled} for
every function in the reference IDB; we compare the leading name component.
"""
import sys, os, json, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS
from demangle_itanium import demangle

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, idautils, ida_name, ida_ida
    out = {}
    try:
        dn = ida_ida.inf_get_long_demnames()
    except Exception:
        dn = 0x0006
    for ea in idautils.Functions():
        n = ida_name.get_name(ea) or ""
        if not n:
            continue
        d = ida_name.demangle_name(n, dn)
        if d:
            out[n] = d
    path = os.path.join(r"__RE_DIR__", "cod4_demangled.json")
    with open(path, "w", encoding="utf-8") as f:
        json.dump(out, f)
    return {"demangled": len(out), "path": path}
main()
'''.replace("__RE_DIR__", RE_DIR)

print(pyeval(PORTS["cod4"], CODE, timeout=600))

ida = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                  "cod4_demangled.json"), encoding="utf-8"))


def head(sig):
    """IDA gives 'Class::method(int, char *)' -> leading qualified name."""
    s = sig
    # strip a trailing parameter list, respecting nesting
    depth = 0
    cut = len(s)
    for i, ch in enumerate(s):
        if ch == "(" and depth == 0:
            cut = i
            break
    s = s[:cut].strip()
    # some forms carry a return type prefix "void foo" - take the last token
    if " " in s and "::" not in s.split(" ")[-1]:
        s = s.split(" ")[-1]
    elif " " in s:
        s = s.split(" ")[-1]
    return s.strip("*& ")


agree = disagree = mine_none = 0
examples = []
for mangled, sig in ida.items():
    mine = demangle(mangled)
    theirs = head(sig)
    if mine is None:
        mine_none += 1
        continue
    if mine == theirs:
        agree += 1
    else:
        disagree += 1
        if len(examples) < 25:
            examples.append((mangled, mine, theirs))

print(f"\nIDA demangled            : {len(ida):,}")
print(f"  mine agrees            : {agree:,}")
print(f"  mine disagrees         : {disagree:,}")
print(f"  mine returned None     : {mine_none:,}  (vtables/thunks/typeinfo/C syms)")
if len(ida):
    cov = 100.0 * agree / max(1, agree + disagree)
    print(f"  agreement where both produced a name: {cov:.2f}%")
print("\ndisagreements:")
for m, a, b in examples:
    print(f"  {m[:56]:56}\n      mine={a!r}\n      ida ={b!r}")
