#!/usr/bin/env python3
"""
scan_vtables.py -- find runs of consecutive function pointers (vtables and
dispatch tables) in a binary's read-only data.

WHY THIS IS THE BEST ALIGNMENT TARGET LEFT
    Call-sequence alignment has to cope with inlining drift, so it needs anchors
    on both sides of every gap. A vtable does not drift: the C++ ABI fixes slot
    order by declaration order, and both binaries were built from a shared source
    lineage. So if two vtables can be paired at all, EVERY slot lines up by index
    -- two matching entries are enough to name the whole class.

    Dispatch tables built as plain arrays behave the same way.

USAGE
    python re/scan_vtables.py <port> <out.json> [--min 4]
"""

from __future__ import annotations

import argparse
import ast
import json
import sys
import urllib.request

SCAN = r'''
def main():
    import idautils, ida_funcs, ida_segment, ida_bytes, struct, json

    starts = set(idautils.Functions())
    ptr = 8 if PTRSIZE == 8 else 4
    fmt = ("<Q" if LE else ">Q") if ptr == 8 else ("<I" if LE else ">I")

    out = []
    for i in range(ida_segment.get_segm_qty()):
        sg = ida_segment.getnseg(i)
        nm = ida_segment.get_segm_name(sg)
        if nm not in (".rdata", ".data", ".const", "_RDATA"):
            continue
        size = sg.end_ea - sg.start_ea
        if size > 40 * 1024 * 1024:          # skip the giant runtime .data blob
            continue
        buf = ida_bytes.get_bytes(sg.start_ea, size)
        if not buf:
            continue
        n = size // ptr
        run = []
        for k in range(n):
            v = struct.unpack_from(fmt, buf, k * ptr)[0]
            if v in starts:
                run.append(v)
            else:
                if len(run) >= MIN:
                    out.append([hex(sg.start_ea + (k - len(run)) * ptr),
                                [hex(x) for x in run]])
                run = []
        if len(run) >= MIN:
            out.append([hex(sg.start_ea + (n - len(run)) * ptr),
                        [hex(x) for x in run]])

    with open(OUT, "w") as fh:
        json.dump(out, fh)
    return {"tables": len(out), "entries": sum(len(t[1]) for t in out)}
main()
'''


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("port", type=int)
    ap.add_argument("out")
    ap.add_argument("--min", type=int, default=4)
    ap.add_argument("--ptr", type=int, default=0, help="pointer size; 0 = autodetect")
    ap.add_argument("--be", action="store_true", help="big endian")
    a = ap.parse_args()

    ptr = a.ptr
    le = not a.be
    if ptr == 0:
        probe = ("def main():\n import ida_ida\n"
                 " return {'p': 8 if ida_ida.inf_is_64bit() else 4,"
                 " 'be': ida_ida.inf_is_be()}\nmain()")
        info = rpc(a.port, probe)
        ptr, le = info["p"], not info["be"]
        print(f"autodetect: pointer={ptr} endian={'BE' if not le else 'LE'}")

    code = (f"OUT = {a.out.replace(chr(92), '/')!r}\nMIN = {a.min}\n"
            f"PTRSIZE = {ptr}\nLE = {le}\n" + SCAN)
    print(rpc(a.port, code, 1800))
    return 0


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


if __name__ == "__main__":
    sys.exit(main())
