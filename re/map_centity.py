#!/usr/bin/env python3
"""
map_centity.py -- derive S2's centity_s field offsets from S2's own code.

METHOD
    sub_13A00(localClient, entnum) returns a centity*. Every dereference of that
    return value is therefore a field access, and the SET of offsets touched
    across all 306 callers IS the struct's used layout.

    Per caller: decompile, find the variable the call result lands in, then
    collect every `*(TYPE *)(var + N)` against it, plus the inline
    `sub_13A00(...) + N` form.

    Evidence FROM S2. Advanced Warfare's centity_s supplies field NAMES and
    ordering, but its offsets do NOT transfer -- AW is 32-bit PPC, five years
    older, 524 bytes against S2's 1808. Where they disagree, S2 is right.

TWO TRANSPORT CONSTRAINTS, BOTH LEARNED THE HARD WAY
    - the MCP plugin enforces a hard 60 s internal timeout (RULE A24), so the
      work is batched;
    - the reply is TRUNCATED past ~60 KB, so decompiled text must never cross the
      wire. The regex runs INSIDE IDA and only counts come back.

USAGE
    python re/map_centity.py [--port 13337] [--batch 25]
"""

from __future__ import annotations

import argparse
import ast
import collections
import json
import sys
import urllib.request
from pathlib import Path

RE_DIR = Path(__file__).resolve().parent

CALLERS = r'''
def main():
    import idautils, ida_funcs
    out = sorted({ida_funcs.get_func(x.frm).start_ea
                  for x in idautils.XrefsTo(0x13A00, 0)
                  if ida_funcs.get_func(x.frm)})
    return [hex(a) for a in out]
main()
'''

# Runs inside IDA. Returns ONLY {offset: {type: count}} plus a function list --
# never the pseudocode itself.
SCAN = r'''
def main():
    import ida_hexrays, ida_funcs, re

    ASSIGN = re.compile(r"(\w+)\s*=\s*(?:\([^)]*\))?\s*sub_13A00\(")
    INLINE = re.compile(r"sub_13A00\([^;]*?\)\s*\+\s*(\d+)")

    hits = {}
    funcs = {}
    ok = 0
    for h in BATCH:
        ea = int(h, 16)
        try:
            code = str(ida_hexrays.decompile(ea))
        except Exception:
            continue
        ok += 1
        nm = ida_funcs.get_func_name(ea)

        def note(off, ty):
            if 0 <= off <= 1808:
                hits.setdefault(off, {})
                hits[off][ty] = hits[off].get(ty, 0) + 1
                funcs.setdefault(off, set()).add(nm)

        for off in INLINE.findall(code):
            note(int(off), "(inline)")

        for var in set(ASSIGN.findall(code)):
            d = re.compile(r"\*\(\s*([_A-Za-z0-9]+)\s*\*\s*\)\(\s*"
                           + re.escape(var) + r"\s*\+\s*(\d+)\s*\)")
            for ty, off in d.findall(code):
                note(int(off), ty)
            # bare deref of the base: *(TYPE *)var
            b = re.compile(r"\*\(\s*([_A-Za-z0-9]+)\s*\*\s*\)" + re.escape(var) + r"\b")
            for ty in b.findall(code):
                note(0, ty)

    return {"ok": ok,
            "hits": {str(k): v for k, v in hits.items()},
            "funcs": {str(k): sorted(v)[:6] for k, v in funcs.items()}}
main()
'''

WIDTH = {"_BYTE": 1, "char": 1, "unsigned __int8": 1, "__int8": 1, "bool": 1,
         "_WORD": 2, "__int16": 2, "unsigned __int16": 2,
         "_DWORD": 4, "int": 4, "unsigned int": 4, "float": 4,
         "_QWORD": 8, "__int64": 8, "double": 8}


def rpc(port, code, timeout=600):
    body = json.dumps({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
                       "params": {"name": "py_eval", "arguments": {"code": code}}}).encode()
    req = urllib.request.Request(f"http://127.0.0.1:{port}/mcp", body,
                                 {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        text = json.load(r)["result"]["content"][0]["text"]
    env = json.loads(text)
    if env.get("stderr"):
        raise RuntimeError(env["stderr"][:300])
    return ast.literal_eval(env["result"]) if env.get("result") else None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=13337)
    ap.add_argument("--batch", type=int, default=25)
    ap.add_argument("--out", default=str(RE_DIR / "s2_centity_offsets.json"))
    a = ap.parse_args()

    callers = rpc(a.port, CALLERS)
    print(f"callers of sub_13A00: {len(callers)}")

    hits = collections.defaultdict(collections.Counter)
    funcs = collections.defaultdict(set)
    done = 0

    for i in range(0, len(callers), a.batch):
        batch = callers[i:i + a.batch]
        try:
            res = rpc(a.port, f"BATCH = {json.dumps(batch)}\n" + SCAN)
        except Exception as e:
            print(f"  batch {i//a.batch+1} failed: {e}")
            continue
        done += res["ok"]
        for off, tys in res["hits"].items():
            for ty, n in tys.items():
                hits[int(off)][ty] += n
        for off, fs in res["funcs"].items():
            funcs[int(off)].update(fs)
        print(f"  {done}/{len(callers)} decompiled, {len(hits)} distinct offsets")

    rows = []
    for off in sorted(hits):
        c = hits[off]
        ty = c.most_common(1)[0][0]
        rows.append({"offset": off, "hex": hex(off), "type": ty,
                     "width": WIDTH.get(ty, 0), "hits": sum(c.values()),
                     "types": dict(c), "funcs": sorted(funcs[off])[:6]})
    Path(a.out).write_text(json.dumps(rows, indent=1))

    print(f"\n{'offset':>7} {'hex':>7} {'w':>2} {'hits':>5}  type           seen in")
    print("-" * 96)
    for r in rows:
        print(f"{r['offset']:>7} {r['hex']:>7} {r['width']:>2} {r['hits']:>5}  "
              f"{r['type']:<14} {', '.join(r['funcs'][:3])[:46]}")
    print(f"\n{len(rows)} distinct field offsets from {done} functions -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
