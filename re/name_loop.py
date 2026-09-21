#!/usr/bin/env python3
"""
name_loop.py -- run caller-intersection propagation to a fixed point.

Each round: refresh S2's names, propagate from every reference, apply what
survives, repeat. Naming X shrinks the unknown set for X's neighbours, so rounds
compound -- WITHOUT ever loosening the evidence rule.

Stops when a round produces nothing new.

USAGE
    python re/name_loop.py [--rounds 6] [--min-callers 2] [--port 13337]
"""

from __future__ import annotations

import argparse
import collections
import json
import subprocess
import sys
import urllib.request
from pathlib import Path

RE_DIR = Path(__file__).resolve().parent
REFS = [("MWR", "mwr_funcs.json"), ("AW", "aw_funcs.json")]

REFRESH = r'''
def main():
    import idautils, ida_funcs, json
    m = {hex(f): ida_funcs.get_func_name(f) for f in idautils.Functions()}
    with open(OUT, "w") as fh:
        json.dump(m, fh)
    return {"named": sum(1 for v in m.values()
                         if not v.startswith(("sub_", "nullsub", "j_")))}
main()
'''

APPLY = r'''
def main():
    import json, collections, idautils, ida_funcs, ida_name, idc

    rows = json.load(open(PLAN))
    taken = {ida_funcs.get_func_name(f) for f in idautils.Functions()}
    applied = 0
    for r in rows:
        ea = int(r["s2_func"], 16)
        if not ida_funcs.get_func_name(ea).startswith(("sub_", "nullsub", "j_")):
            continue
        if r["name"] in taken:
            continue
        if not ida_name.set_name(ea, r["name"], ida_name.SN_NOWARN):
            continue
        taken.add(r["name"]); applied += 1
        idc.set_func_cmt(ea,
            "Caller-intersection propagation: %s  [round %d]\n"
            "Basis: %d NAMED S2 function(s) call this one -- %s.\n"
            "Each of their twins in %s was intersected on what it calls; after removing\n"
            "every name already worn by another S2 function, exactly ONE name survived in\n"
            "all of them. Unrelated callers agreeing by coincidence is not plausible.\n"
            "Cross-binary -- re-check if anything depends on it."
            % (r["name"], r["round"], r["callers"], ", ".join(r["via"][:4]),
               "+".join(r["src"])), 0)
    return {"applied": applied}
main()
'''


def rpc(port, code, timeout=1800):
    body = json.dumps({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
                       "params": {"name": "py_eval", "arguments": {"code": code}}}).encode()
    req = urllib.request.Request(f"http://127.0.0.1:{port}/mcp", body,
                                 {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return json.load(r)["result"]["content"][0]["text"]


def dm(n):
    if n.startswith("?"):
        e = n.find("@@")
        if e > 1:
            return "::".join(reversed([p for p in n[1:e].split("@") if p]))
    return n


def norm(n):
    return dm(n).replace("::", "__").rstrip("_").lower()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--rounds", type=int, default=6)
    ap.add_argument("--min-callers", type=int, default=2)
    ap.add_argument("--port", type=int, default=13337)
    a = ap.parse_args()

    names_p = RE_DIR / "s2_names_now.json"
    plan_p = RE_DIR / "name_loop_plan.json"
    total = 0

    for rnd in range(1, a.rounds + 1):
        print(f"\n===== round {rnd} =====")
        print(" refresh:", rpc(a.port, f"OUT = {str(names_p).replace(chr(92),'/')!r}\n" + REFRESH))

        merged = {}
        for label, fn in REFS:
            out = RE_DIR / f"callers_{label.lower()}.json"
            subprocess.run([sys.executable, str(RE_DIR / "propagate_callers.py"),
                            str(RE_DIR / "s2_steam_funcs.json"), str(names_p),
                            str(RE_DIR / fn), str(out), label],
                           capture_output=True, check=True)
            for r in json.loads(out.read_text()):
                if r["callers"] < a.min_callers:
                    continue
                k = r["s2_func"]
                nm = dm(r["name"])
                if k not in merged:
                    merged[k] = {"s2_func": k, "name": nm, "src": [label],
                                 "callers": r["callers"], "via": r["via"],
                                 "bad": False, "round": rnd}
                    continue
                m = merged[k]
                x, y = norm(m["name"]), norm(nm)
                if x == y or x.endswith(y) or y.endswith(x):
                    # Attribute the CHOSEN name, not the union. If the two
                    # references spell it differently and we keep one spelling,
                    # only the reference that actually contains that spelling
                    # supports it -- claiming both is a false citation, and
                    # audit_names.py's phantom-reference check will catch it.
                    if len(y) > len(x):
                        m["name"] = nm
                        m["src"] = [label]
                    elif x == y:
                        m["src"].append(label)
                    m["callers"] = max(m["callers"], r["callers"])
                else:
                    m["bad"] = True

        byn = collections.Counter(norm(v["name"]) for v in merged.values() if not v["bad"])
        plan = [v for v in merged.values() if not v["bad"] and byn[norm(v["name"])] == 1]
        plan.sort(key=lambda p: -p["callers"])
        plan_p.write_text(json.dumps(plan, indent=1))
        print(f" candidates: {len(plan)} "
              f"(dropped {sum(1 for v in merged.values() if v['bad'])} disagreements)")

        if not plan:
            print(" nothing new -- fixed point reached")
            break
        res = rpc(a.port, f"PLAN = {str(plan_p).replace(chr(92),'/')!r}\n" + APPLY)
        print(" apply:", res)
        # the RPC reply nests a python-repr dict inside JSON; just pull the number
        m = __import__("re").search(r"'applied':\s*(\d+)", res)
        got = int(m.group(1)) if m else 0
        total += got
        if got == 0:
            print(" nothing applied -- stopping")
            break

    print(f"\nTOTAL APPLIED ACROSS ROUNDS: {total}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
