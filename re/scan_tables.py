#!/usr/bin/env python3
"""
scan_tables.py -- find EVERY {name-string, function-pointer} table in .rdata,
at any stride and any field offset.

WHY A SECOND SCANNER
    The first pass only looked for stride-16 `{const char*, void*}` pairs. That
    found the Lua/HKS binding tables and the OOB dispatchers, but it is blind to
    the shape the engine uses for GSC builtins:

        { "getentitynumber", Scr_GetEntityNumber, 0 },      // stride 24
        { "spawn",           GScr_Spawn,          1 },

    A third field (min-args / dev flag) pushes the stride to 24 or 32, so every
    Scr_* and GScr_* table was invisible. This scanner infers the stride from the
    data instead of assuming it.

METHOD
    Classify every qword slot in .rdata as string-pointer / function-pointer /
    other. For each string slot, find the nearest function slot within 6 slots --
    that gives a candidate (name, fn) delta. Then look for runs where BOTH the
    delta and the slot-to-slot stride are constant. Four or more consecutive
    entries is a table; noise does not repeat at a fixed stride.

    Runs through the MCP with a long timeout because the classification pass over
    ~327k slots exceeds the default (see RULE A24).

USAGE
    python re/scan_tables.py [--port 13337] [--out re/s2_tables_all.json]
"""

from __future__ import annotations

import argparse
import json
import sys
import urllib.request
from pathlib import Path

SCAN = r'''
def main():
    import idautils, ida_bytes, struct, collections, json

    RD_LO, RD_HI = 0xb1b000, 0xd90000
    TX_LO, TX_HI = 0x1000, 0xb0f000
    rd = ida_bytes.get_bytes(RD_LO, RD_HI - RD_LO)
    funcs = set(idautils.Functions())

    n = (RD_HI - RD_LO) // 8
    kind = bytearray(n)
    text = {}
    for i in range(n):
        p = struct.unpack_from('<Q', rd, i * 8)[0]
        if TX_LO <= p < TX_HI:
            if p in funcs:
                kind[i] = 2
        elif RD_LO <= p < RD_HI - 2:
            o = p - RD_LO
            e = rd.find(b'\x00', o, o + 96)
            if e > o:
                s = rd[o:e]
                if 2 <= len(s) <= 64 and all(32 <= c < 127 for c in s):
                    kind[i] = 1
                    text[i] = s.decode('ascii')

    pairs = []
    for i in range(n):
        if kind[i] == 1:
            for d in range(1, 7):
                if i + d < n and kind[i + d] == 2:
                    pairs.append((i, d))
                    break

    byd = collections.defaultdict(list)
    for i, d in pairs:
        byd[d].append(i)

    tables = []
    for d, idxs in byd.items():
        idxs.sort()
        k = 0
        while k < len(idxs):
            best = None
            for stride in (2, 3, 4, 5, 6, 8):
                cnt, j = 1, k
                while j + 1 < len(idxs) and idxs[j + 1] - idxs[j] == stride:
                    j += 1
                    cnt += 1
                if cnt >= 4 and (best is None or cnt > best[0]):
                    best = (cnt, stride, j)
            if best:
                cnt, stride, j = best
                ents = []
                for m in range(cnt):
                    si = idxs[k] + m * stride
                    ents.append([text[si],
                                 hex(struct.unpack_from('<Q', rd, (si + d) * 8)[0])])
                tables.append({"addr": hex(RD_LO + idxs[k] * 8), "n": cnt,
                               "stride": stride * 8, "fn_delta": d * 8,
                               "entries": ents})
                k = j + 1
            else:
                k += 1

    with open(OUT, "w") as fh:
        json.dump(tables, fh)
    known = sum(1 for t in tables if t["stride"] == 16 and t["fn_delta"] == 8)
    return {"tables": len(tables), "entries": sum(t["n"] for t in tables),
            "stride16_known": known, "other_shapes": len(tables) - known,
            "out": OUT}
main()
'''


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=13337)
    ap.add_argument("--out", default="c:/Users/joshu/OneDrive/Documents/GitHub/S2MP-Mod/re/s2_tables_all.json")
    a = ap.parse_args()

    code = f"OUT = {a.out!r}\n" + SCAN
    body = json.dumps({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
                       "params": {"name": "py_eval", "arguments": {"code": code}}}).encode()
    req = urllib.request.Request(f"http://127.0.0.1:{a.port}/mcp", body,
                                 {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=1800) as r:
        print(json.load(r)["result"]["content"][0]["text"])

    tables = json.loads(Path(a.out).read_text())
    other = [t for t in tables if not (t["stride"] == 16 and t["fn_delta"] == 8)]
    other.sort(key=lambda t: -t["n"])
    print(f"\n{'addr':>12} {'n':>5} {'stride':>7} {'fnoff':>6}  first entries")
    print("-" * 88)
    for t in other[:30]:
        names = ", ".join(e[0] for e in t["entries"][:5])
        print(f"{t['addr']:>12} {t['n']:>5} {t['stride']:>7} {t['fn_delta']:>6}  {names[:52]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
