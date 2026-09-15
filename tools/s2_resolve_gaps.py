#!/usr/bin/env python3
"""
s2_resolve_gaps.py -- resolve the function addresses the size matcher could not.

WHY THEY ARE LEFT OVER
    s2_match_builds.py forces a pair only when a size is unambiguous on BOTH
    sides. That is deliberately conservative -- it is what buys 99.36% precision --
    but it leaves 5-byte thunks and small functions unmatched, because dozens of
    them share a size.

THE TECHNIQUE
    Same idea the data-global resolver uses, applied to CALL targets instead of
    data operands. For an unmatched Steam function F:

        find a CALLER C that IS matched
        take the byte offset of the call instruction within C
        read the instruction at the SAME offset in C' (the Store twin)
        its call target is F'

    Valid because the two builds share codegen -- 28,391 of 28,428 matched
    functions are identical in size, so instruction offsets line up.

    Guards, since "offsets line up" is an assumption until checked:
      * the mnemonic at that offset must be a call in BOTH
      * multiple callers must AGREE, or the answer is reported as weak
      * the candidate must not already be claimed by another Steam function

USAGE
    python tools/s2_resolve_gaps.py <scratch dir>
"""

from __future__ import annotations

import json
import sys
import urllib.request
from collections import Counter, defaultdict
from pathlib import Path

STEAM, XBOX = 13337, 12346


def rpc(port: int, code: str, timeout: int = 900):
    body = json.dumps({
        "jsonrpc": "2.0", "id": 1, "method": "tools/call",
        "params": {"name": "py_eval", "arguments": {"code": code}},
    }).encode()
    req = urllib.request.Request(
        f"http://127.0.0.1:{port}/mcp", body, {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        out = json.load(r)
    p = json.loads(out["result"]["content"][0]["text"])
    if p.get("stderr"):
        raise RuntimeError(p["stderr"][:2000])
    return eval(p["result"])


STEAM_SIDE = r'''
import idautils, ida_funcs, ida_ua
T = TARGETS
out = {}
for f in T:
    sites = []
    for xr in idautils.XrefsTo(f, 0):
        c = ida_funcs.get_func(xr.frm)
        if not c or c.start_ea == f:
            continue
        m = ida_ua.print_insn_mnem(xr.frm)
        if m != "call":
            continue
        sites.append([c.start_ea, xr.frm - c.start_ea])
        if len(sites) >= 10:
            break
    out[f] = sites
out
'''

XBOX_SIDE = r'''
import idautils, ida_funcs, ida_ua
Q = QUERIES
out = []
for fs, off in Q:
    ea = fs + off
    f = ida_funcs.get_func(ea)
    if not f or f.start_ea != fs or ida_ua.print_insn_mnem(ea) != "call":
        out.append(0)
        continue
    tgt = 0
    for xr in idautils.CodeRefsFrom(ea, 0):
        g = ida_funcs.get_func(xr)
        if g and g.start_ea == xr:
            tgt = xr
            break
    out.append(tgt)
out
'''


def main() -> int:
    if len(sys.argv) != 2:
        print(__doc__)
        return 2
    sc = Path(sys.argv[1])
    bmap = {int(k, 16): int(v, 16)
            for k, v in json.loads((sc / "build_map.json").read_text()).items()}
    taken = set(bmap.values())

    # The function addresses the emitter reported as unresolved.
    targets = [0x90750, 0x9DC60, 0xCF850, 0x1C04E0, 0x1FEB80, 0x318A00, 0x31B6F0,
               0x45DBC0, 0x6D8200, 0x6DBF50, 0x746A50, 0x78AC90, 0x8BBCD0]
    todo = [t for t in targets if t not in bmap]
    print(f"unresolved functions to chase: {len(todo)}")

    steam = rpc(STEAM, STEAM_SIDE.replace("TARGETS", repr(todo)))

    queries, owner = [], []
    for f in todo:
        for cs, off in steam.get(f, []):
            if cs in bmap:
                queries.append([bmap[cs], off])
                owner.append((f, cs, off))
    print(f"call sites inside matched callers: {len(queries)}")

    xbox = []
    for i in range(0, len(queries), 400):
        xbox += rpc(XBOX, XBOX_SIDE.replace("QUERIES", repr(queries[i:i + 400])))

    votes = defaultdict(Counter)
    for (f, _, _), tgt in zip(owner, xbox):
        if tgt:
            votes[f][tgt] += 1

    strong, weak, failed = {}, {}, []
    for f in todo:
        v = votes.get(f)
        if not v:
            failed.append(f)
            continue
        tgt, n = v.most_common(1)[0]
        total = sum(v.values())
        if tgt in taken:
            failed.append(f)                  # already claimed -- refuse rather than guess
        elif n >= 2 and n / total >= 0.8:
            strong[f] = tgt
        else:
            weak[f] = tgt

    print(f"\n  RESOLVED (>=2 agreeing callers) : {len(strong)}")
    for f, t in sorted(strong.items()):
        print(f"      steam 0x{f:<9X} -> xbox 0x{t:X}")
    print(f"  weak (single caller)            : {len(weak)}")
    for f, t in sorted(weak.items()):
        print(f"      steam 0x{f:<9X} -> xbox 0x{t:X}")
    print(f"  still unresolved                : {len(failed)}")
    for f in failed:
        print(f"      steam 0x{f:X}")

    out = sc / "gap_map.json"
    out.write_text(json.dumps({
        "resolved": {hex(k): hex(v) for k, v in sorted(strong.items())},
        "weak": {hex(k): hex(v) for k, v in sorted(weak.items())},
    }, indent=1))
    print(f"\nwrote {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
