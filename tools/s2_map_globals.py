#!/usr/bin/env python3
"""
s2_map_globals.py -- resolve the mod's DATA globals from Steam to the Store build.

THE IDEA, and why it works here specifically
    A data global has no name, no size and no call graph, so none of the function
    matcher's signals apply to it. But it is REFERENCED by instructions, and the
    two builds are the same codegen -- 21 of 22 known-good functions are byte
    identical in size. So an instruction that sits N bytes into a Steam function
    sits N bytes into its Store twin.

    Therefore:
        find a Steam instruction that references the global
        take its offset within its (matched) function
        read the instruction at the SAME offset in the Xbox twin
        its data operand is the same global

    Two guards, because "the offsets line up" is an assumption until checked:
      * the MNEMONIC at that offset must match, or the functions have drifted
      * multiple referencing sites must AGREE on the answer; a global with one
        xref is reported as low-confidence rather than silently trusted

USAGE
    python tools/s2_map_globals.py <build_map.json> <out.json>
"""

from __future__ import annotations

import json
import re
import sys
import urllib.request
from collections import Counter, defaultdict
from pathlib import Path

STEAM, XBOX = 13337, 12346
RE_B = re.compile(r"0x([0-9A-Fa-f]+)_b")
RE_A = re.compile(r"ADDR_[A-Z0-9_]+\s*=\s*0x([0-9A-Fa-f]+)")


def rpc(port: int, code: str, timeout: int = 900):
    body = json.dumps({
        "jsonrpc": "2.0", "id": 1, "method": "tools/call",
        "params": {"name": "py_eval", "arguments": {"code": code}},
    }).encode()
    req = urllib.request.Request(
        f"http://127.0.0.1:{port}/mcp", body, {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        out = json.load(r)
    txt = out["result"]["content"][0]["text"]
    payload = json.loads(txt)
    if payload.get("stderr"):
        raise RuntimeError(payload["stderr"][:2000])
    return eval(payload["result"])


def mod_addresses() -> set[int]:
    found = set()
    for p in (Path(__file__).resolve().parent.parent / "src").rglob("*"):
        if p.suffix not in (".cpp", ".hpp", ".h"):
            continue
        t = p.read_text(encoding="utf-8", errors="replace")
        for m in RE_B.finditer(t):
            found.add(int(m.group(1), 16) + 0x1000)
        for m in RE_A.finditer(t):
            found.add(int(m.group(1), 16) + 0x1000)
    return found


STEAM_SIDE = r'''
import idautils, ida_funcs, ida_ua, ida_bytes
T = TARGETS
out = {}
for d in T:
    sites = []
    for xr in idautils.XrefsTo(d, 0):
        f = ida_funcs.get_func(xr.frm)
        if not f:
            continue
        sites.append([f.start_ea, xr.frm - f.start_ea, ida_ua.print_insn_mnem(xr.frm)])
        if len(sites) >= 8:
            break
    # is the address itself inside a function? then it is mid-function CODE,
    # not a data global, and needs a different treatment.
    inside = ida_funcs.get_func(d)
    out[d] = [sites, inside.start_ea if inside else 0]
out
'''

XBOX_SIDE = r'''
import idautils, ida_funcs, ida_ua
Q = QUERIES          # [[xbox_func_start, offset], ...]
out = []
for fs, off in Q:
    ea = fs + off
    f = ida_funcs.get_func(ea)
    ok = bool(f) and f.start_ea == fs
    refs = sorted(idautils.DataRefsFrom(ea)) if ok else []
    out.append([ida_ua.print_insn_mnem(ea) if ok else "", refs])
out
'''


def main() -> int:
    if len(sys.argv) != 3:
        print(__doc__)
        return 2
    bmap = {int(k, 16): int(v, 16) for k, v in json.loads(Path(sys.argv[1]).read_text()).items()}

    targets = sorted(mod_addresses())
    print(f"mod addresses: {len(targets)}")

    steam = rpc(STEAM, STEAM_SIDE.replace("TARGETS", repr(targets)))

    globals_, midfunc, starts = [], [], []
    for d in targets:
        sites, inside = steam[d]
        if inside == d:
            starts.append(d)
        elif inside:
            midfunc.append(d)
        else:
            globals_.append(d)
    print(f"  function starts     : {len(starts)}")
    print(f"  mid-function (code) : {len(midfunc)}")
    print(f"  data globals        : {len(globals_)}\n")

    # Build the query list: every referencing site whose function we matched.
    queries, owner = [], []
    for d in globals_ + midfunc:
        for fs, off, mnem in steam[d][0]:
            if fs in bmap:
                queries.append([bmap[fs], off])
                owner.append((d, fs, off, mnem))
    print(f"referencing sites in matched functions: {len(queries)}")

    xbox = []
    for i in range(0, len(queries), 400):
        xbox += rpc(XBOX, XBOX_SIDE.replace("QUERIES", repr(queries[i:i + 400])))

    votes = defaultdict(Counter)
    drift = Counter()
    for (d, fs, off, mnem), (xm, refs) in zip(owner, xbox):
        if xm != mnem:
            drift[d] += 1          # the twin has drifted at this offset
            continue
        for r in refs:
            votes[d][r] += 1

    resolved, weak, failed = {}, {}, []
    for d in globals_ + midfunc:
        v = votes.get(d)
        if not v:
            failed.append(d)
            continue
        top, n = v.most_common(1)[0]
        total = sum(v.values())
        if n >= 2 and n / total >= 0.8:
            resolved[d] = top
        else:
            weak[d] = top

    print(f"\n  RESOLVED (>=2 agreeing sites) : {len(resolved)}")
    print(f"  weak (single site / split)    : {len(weak)}")
    print(f"  no usable site                : {len(failed)}")
    if drift:
        print(f"  sites skipped for mnemonic drift: {sum(drift.values())} "
              f"across {len(drift)} globals")

    print("\n  sample:")
    for d in sorted(resolved)[:12]:
        print(f"    steam 0x{d:<9X} -> xbox 0x{resolved[d]:X}")

    Path(sys.argv[2]).write_text(json.dumps({
        "resolved": {hex(k): hex(v) for k, v in sorted(resolved.items())},
        "weak": {hex(k): hex(v) for k, v in sorted(weak.items())},
        "failed": [hex(k) for k in sorted(failed)],
        "function_starts": [hex(k) for k in sorted(starts)],
    }, indent=1))
    print(f"\nwrote {sys.argv[2]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
