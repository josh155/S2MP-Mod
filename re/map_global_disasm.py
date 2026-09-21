#!/usr/bin/env python3
"""
map_global_disasm.py -- derive struct field offsets from DISASSEMBLY displacements
rather than from decompiler output.

WHY NOT THE DECOMPILER
    map_global_struct.py regexes pseudocode, and for clc that fails badly: IDA
    renders the accesses as

        v18 = (char *)clc + 482656 * v14 + 262480;
        *(_DWORD *)((char *)clc + v17 + 262752) = 2;

    -- the per-client stride hides in one variable and a base constant gets folded
    into another. Chasing that with regexes means chasing every rendering IDA
    might choose. It got 11 offsets out of 122 functions.

    The machine code has no such freedom. `mov [rax+rcx+40260h], edx` states the
    displacement outright, whatever the decompiler later does with it.

METHOD
    Per function: walk instructions, taint the register that receives the global,
    and record the displacement of any memory operand based on a tainted register.
    Untaint on overwrite. A plain def-use scan -- deliberately simple, because the
    goal is offsets, not correctness of the dataflow.

    The per-client stride is handled by reducing modulo it, so client N's fields
    collapse onto client 0's instead of appearing as phantom high offsets.

USAGE
    python re/map_global_disasm.py --global 0x1BD3D00 --stride 482656 \
        --max 482656 --out re/s2_clc_offsets.json
"""

from __future__ import annotations

import argparse
import ast
import collections
import json
import sys
import urllib.request
from pathlib import Path

SCAN = r'''
def main():
    import idautils, ida_funcs, ida_ua, idc, re

    # [base+index*scale+DISP] or [base+DISP] -- hex (IDA suffixes 'h') or decimal
    MEM = re.compile(r"\[([a-z0-9]+)((?:\+[a-z0-9]+(?:\*\d+)?)*)\+([0-9A-Fa-f]+)h\]")
    MEMD = re.compile(r"\[([a-z0-9]+)((?:\+[a-z0-9]+(?:\*\d+)?)*)\+(\d+)\]")

    hits, funcs, ok = {}, {}, 0

    for h in BATCH:
        fea = int(h, 16)
        f = ida_funcs.get_func(fea)
        if not f:
            continue
        ok += 1
        nm = ida_funcs.get_func_name(fea)
        tainted = set()

        def note(off):
            if STRIDE and off >= STRIDE:
                off = off % STRIDE
            if 0 <= off <= MAXOFF:
                hits.setdefault(off, {})
                hits[off]["disp"] = hits[off].get("disp", 0) + 1
                funcs.setdefault(off, set()).add(nm)

        for head in idautils.FuncItems(fea):
            insn = ida_ua.insn_t()
            if not ida_ua.decode_insn(insn, head):
                continue
            text = idc.GetDisasm(head).lower()
            dst = idc.print_operand(head, 0).lower().strip()

            # does this instruction load the global itself?
            loads_global = False
            for i in range(2):
                op = insn.ops[i]
                if op.type in (ida_ua.o_mem, ida_ua.o_imm) and op.addr == G:
                    loads_global = True
                if op.type == ida_ua.o_mem and op.addr == G:
                    loads_global = True
            if not loads_global:
                for xr in idautils.XrefsFrom(head, 0):
                    if xr.to == G:
                        loads_global = True
                        break

            if loads_global and dst and dst.isalnum():
                tainted.add(dst)
                continue

            # record displacements off a tainted base
            for rx in (MEM, MEMD):
                for base, _idx, disp in rx.findall(text):
                    if base in tainted:
                        try:
                            note(int(disp, 16) if rx is MEM else int(disp))
                        except ValueError:
                            pass

            # untaint on overwrite (crude but adequate)
            if dst in tainted and insn.itype not in (ida_ua.o_void,):
                mnem = idc.print_insn_mnem(head).lower()
                if mnem in ("mov", "lea", "xor", "add", "sub", "pop", "call"):
                    if mnem == "call":
                        tainted.discard("rax")
                    elif not (mnem == "add" or mnem == "sub"):
                        tainted.discard(dst)

    return {"ok": ok,
            "hits": {str(k): v for k, v in hits.items()},
            "funcs": {str(k): sorted(v)[:6] for k, v in funcs.items()}}
main()
'''

REFS = r'''
def main():
    import idautils, ida_funcs
    return [hex(a) for a in sorted({ida_funcs.get_func(x.frm).start_ea
                                    for x in idautils.XrefsTo(G, 0)
                                    if ida_funcs.get_func(x.frm)})]
main()
'''


def rpc(port, code, timeout=900):
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
    ap.add_argument("--max", type=int, required=True)
    ap.add_argument("--stride", type=int, default=0)
    ap.add_argument("--batch", type=int, default=25)
    ap.add_argument("--out", required=True)
    a = ap.parse_args()

    g = int(a.g, 16)
    refs = rpc(a.port, f"G = {g}\n" + REFS)
    print(f"global {a.g}: {len(refs)} referencing functions"
          + (f", stride {a.stride}" if a.stride else ""))

    hits = collections.Counter()
    funcs = collections.defaultdict(set)
    done = 0
    for i in range(0, len(refs), a.batch):
        batch = refs[i:i + a.batch]
        try:
            res = rpc(a.port, f"BATCH = {json.dumps(batch)}\nG = {g}\n"
                              f"MAXOFF = {a.max}\nSTRIDE = {a.stride}\n" + SCAN)
        except Exception as e:
            print(f"  batch {i//a.batch+1} failed: {e}")
            continue
        done += res["ok"]
        for off, d in res["hits"].items():
            hits[int(off)] += sum(d.values())
        for off, fs in res["funcs"].items():
            funcs[int(off)].update(fs)
        if (i // a.batch) % 2 == 0:
            print(f"  {done}/{len(refs)} scanned, {len(hits)} offsets")

    rows = [{"offset": o, "hex": hex(o), "hits": hits[o],
             "funcs": sorted(funcs[o])[:6]} for o in sorted(hits)]
    Path(a.out).write_text(json.dumps(rows, indent=1))
    print(f"\n{len(rows)} distinct offsets from {done} functions -> {a.out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
