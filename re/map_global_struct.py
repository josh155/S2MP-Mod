#!/usr/bin/env python3
"""
map_global_struct.py -- derive a struct's field offsets when it is reached through
a GLOBAL rather than an accessor function.

WHY A SECOND EXTRACTOR
    map_struct.py keys on an accessor's return value. That works for centity_s and
    cg_s, but the two biggest remaining targets are not reached that way:

        clientDemoPlayback_t   qword_10F340A0   (CL_Demo_GetPlaybackData has only
                                                 15 callers; the demo code reads
                                                 the global directly)
        clientConnection_t     clc @ 0x1BD3D00  (no accessor exists at all -- AW
                                                 has ZERO functions returning
                                                 clientConnection_t*)

    So: find every function referencing the global, decompile it, and collect the
    dereferences applied to it.

THREE ACCESS FORMS, ALL HANDLED
    *(_DWORD *)(g + 24)        -> offset 24        byte offset
    *((_DWORD *)g + 32849)     -> offset 131396    INDEX form; IDA scales by the
                                                   cast width, so this must be
                                                   multiplied back or every clc
                                                   offset comes out ~4x too small
    v = g; ... *(_BYTE *)(v + 10)                  via a local

PER-CLIENT STRIDE
    clc is an ARRAY: clc + STRIDE*client + field. With --stride, any offset larger
    than the stride is reduced modulo it, so client 1's fields land on the same
    field as client 0's instead of appearing as phantom high offsets.

USAGE
    python re/map_global_struct.py --global 0x10F340A0 --name qword_10F340A0 \
        --max 6400000 --out re/s2_demoplayback_offsets2.json
"""

from __future__ import annotations

import argparse
import ast
import collections
import json
import sys
import urllib.request
from pathlib import Path

REFS = r'''
def main():
    import idautils, ida_funcs
    out = sorted({ida_funcs.get_func(x.frm).start_ea
                  for x in idautils.XrefsTo(G, 0)
                  if ida_funcs.get_func(x.frm)})
    return [hex(a) for a in out]
main()
'''

SCAN = r'''
def main():
    import ida_hexrays, ida_funcs, re

    W = {"_BYTE":1,"char":1,"unsigned __int8":1,"__int8":1,"bool":1,
         "_WORD":2,"__int16":2,"unsigned __int16":2,
         "_DWORD":4,"int":4,"unsigned int":4,"float":4,
         "_QWORD":8,"__int64":8,"double":8}

    G = re.escape(GNAME)
    # GENERAL deref: *(TYPE *)( <expr containing the global> ). The inner
    # expression is parsed afterwards, because real code looks like
    #     *(_DWORD *)((char *)clc + v17 + 262752)
    # where v17 carries the 482656*client term -- a regex demanding "clc + N"
    # directly matches almost nothing.
    DEREF   = re.compile(r"\*\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)\(([^()]*(?:\([^()]*\))?[^()]*)\)")
    # *((TYPE *)g + N) -- INDEX form; IDA scales N by the cast width
    IDXOFF  = re.compile(r"\*\(\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)" + G + r"\s*\+\s*(\d+)\s*\)")
    # v = g;
    ASSIGN  = re.compile(r"(\w+)\s*=\s*(?:\([^)]*\))?\s*" + G + r"\s*;")
    TRAILN  = re.compile(r"\+\s*(\d+)\s*$")
    # v18 = (char *)clc + 482656 * v14 + 262480;
    # The var carries a BASE CONSTANT that every later deref through it is relative
    # to. Without this the dominant clc access form is invisible.
    BASED   = re.compile(r"(\w+)\s*=\s*\(char \*\)" + G + r"\s*\+[^;]*?\+\s*(\d+)\s*;")

    hits, funcs, ok = {}, {}, 0
    for h in BATCH:
        ea = int(h, 16)
        try:
            code = str(ida_hexrays.decompile(ea))
        except Exception:
            continue
        ok += 1
        nm = ida_funcs.get_func_name(ea)

        def note(off, ty):
            if STRIDE and off >= STRIDE:
                off = off % STRIDE
            if 0 <= off <= MAXOFF:
                hits.setdefault(off, {})
                hits[off][ty] = hits[off].get(ty, 0) + 1
                funcs.setdefault(off, set()).add(nm)

        for ty, inner in DEREF.findall(code):
            if GNAME not in inner:
                continue
            m = TRAILN.search(inner.strip())
            if m:
                note(int(m.group(1)), ty.strip())
            elif inner.strip().endswith(GNAME) or inner.strip() == "(char *)" + GNAME:
                note(0, ty.strip())
        for ty, idx in IDXOFF.findall(code):
            t = ty.strip()
            note(int(idx) * W.get(t, 1), t)
        for var, base in set(BASED.findall(code)):
            b = int(base)
            d = re.compile(r"\*\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)\(\s*"
                           + re.escape(var) + r"\s*\+\s*(\d+)\s*\)")
            for ty, off in d.findall(code):
                note(b + int(off), ty.strip())
            bare = re.compile(r"\*\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)" + re.escape(var) + r"")
            for ty in bare.findall(code):
                note(b, ty.strip())
        for var in set(ASSIGN.findall(code)):
            d = re.compile(r"\*\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)\(\s*"
                           + re.escape(var) + r"\s*\+\s*(\d+)\s*\)")
            for ty, off in d.findall(code):
                note(int(off), ty.strip())
            i = re.compile(r"\*\(\(\s*([_A-Za-z0-9 ]+?)\s*\*\s*\)"
                           + re.escape(var) + r"\s*\+\s*(\d+)\s*\)")
            for ty, idx in i.findall(code):
                t = ty.strip()
                note(int(idx) * W.get(t, 1), t)

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
    if not env.get("result"):
        return None
    try:
        return ast.literal_eval(env["result"])
    except (ValueError, SyntaxError):
        return env["result"]


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=13337)
    ap.add_argument("--global", dest="g", required=True)
    ap.add_argument("--name", required=True, help="global's name as it appears in pseudocode")
    ap.add_argument("--max", type=int, required=True)
    ap.add_argument("--stride", type=int, default=0, help="per-client array stride, if any")
    ap.add_argument("--batch", type=int, default=20)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    g = int(a.g, 16)
    refs = rpc(a.port, f"G = {g}\n" + REFS)
    print(f"{a.name} @ {a.g}: {len(refs)} referencing functions"
          + (f", stride {a.stride}" if a.stride else ""))

    hits = collections.defaultdict(collections.Counter)
    funcs = collections.defaultdict(set)
    done = 0
    for i in range(0, len(refs), a.batch):
        batch = refs[i:i + a.batch]
        try:
            res = rpc(a.port, f"BATCH = {json.dumps(batch)}\nMAXOFF = {a.max}\n"
                              f"GNAME = {a.name!r}\nSTRIDE = {a.stride}\n" + SCAN)
        except Exception as e:
            print(f"  batch {i//a.batch+1} failed: {e}")
            continue
        done += res["ok"]
        for off, tys in res["hits"].items():
            for ty, n in tys.items():
                hits[int(off)][ty] += n
        for off, fs in res["funcs"].items():
            funcs[int(off)].update(fs)
        if (i // a.batch) % 5 == 0:
            print(f"  {done}/{len(refs)} decompiled, {len(hits)} offsets")

    rows = []
    for off in sorted(hits):
        c = hits[off]
        ty = c.most_common(1)[0][0]
        rows.append({"offset": off, "hex": hex(off), "type": ty,
                     "width": WIDTH.get(ty, 0), "hits": sum(c.values()),
                     "types": dict(c), "funcs": sorted(funcs[off])[:6]})
    Path(a.out).write_text(json.dumps(rows, indent=1))
    print(f"\n{len(rows)} distinct offsets from {done} functions -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
