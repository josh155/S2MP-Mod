#!/usr/bin/env python3
"""
export_ordered.py -- export a function graph with callees in CALL ORDER.

WHY THIS AND NOT s2_export_idb.py
    That exporter sorts callees by address, which is fine for set-based work but
    destroys the one signal that can crack the big engine functions: ORDER.

    CL_/SV_/CG_ functions are mostly called by other unnamed CL_/SV_/CG_
    functions, so caller-intersection cannot bootstrap there. But these binaries
    share a source lineage, so a matched pair calls broadly the same things in
    broadly the same sequence. Callees whose names are already known act as
    ANCHORS, and unknowns sitting between the same two anchors on both sides can
    be aligned.

    Order is taken from the address of the CALL INSTRUCTION, walking the function
    body -- not from the callee's own address.

USAGE
    python re/export_ordered.py <port> <out.json>
"""

from __future__ import annotations

import json
import sys
import urllib.request

EXPORT = r'''
def main():
    import idautils, ida_funcs, json

    starts = set(idautils.Functions())
    out = {}
    for fea in starts:
        f = ida_funcs.get_func(fea)
        if not f:
            continue
        seq = []
        for head in idautils.FuncItems(fea):
            for xr in idautils.XrefsFrom(head, 0):
                # 16/17 = call near/far. Jumps are excluded: a tail-jump is not a
                # position in the call sequence.
                if xr.type not in (16, 17):
                    continue
                if xr.to in starts and xr.to != fea:
                    seq.append(xr.to)
        out[hex(fea)] = [f.size(), ida_funcs.get_func_name(fea),
                         [hex(c) for c in seq]]

    with open(OUT, "w") as fh:
        json.dump(out, fh)
    return {"functions": len(out),
            "call_sites": sum(len(v[2]) for v in out.values()),
            "out": OUT}
main()
'''


def main() -> int:
    if len(sys.argv) != 3:
        print(__doc__)
        return 2
    port, out = int(sys.argv[1]), sys.argv[2].replace("\\", "/")
    body = json.dumps({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
                       "params": {"name": "py_eval",
                                  "arguments": {"code": f"OUT = {out!r}\n" + EXPORT}}}).encode()
    req = urllib.request.Request(f"http://127.0.0.1:{port}/mcp", body,
                                 {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=2400) as r:
        print(json.load(r)["result"]["content"][0]["text"])
    return 0


if __name__ == "__main__":
    sys.exit(main())
