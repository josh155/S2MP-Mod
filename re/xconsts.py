"""RUNS INSIDE IDA. Dump per-function CONSTANT sets for one IDB.

Strings only reach functions that print or parse. Maths, physics, prediction and
render code often has none - but it is full of literal constants, and a source
literal like 0.267 or 1.5708 survives recompilation on any compiler.

Two kinds are collected:
  * integer immediates, excluding anything that could be an ADDRESS (addresses
    differ between builds, so they are noise here) and excluding small values
    that are far too common to carry signal
  * float/double literals reached by a data reference into a read-only segment,
    which is where x86 compilers put them (they are loaded with `fld`, not as
    immediates)

    python re/xconsts.py cod4 cod4x
writes re/<key>_consts.json  {func_ea_hex: [tokens]}
"""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from ida import pyeval, PORTS

RE_DIR = os.path.dirname(os.path.abspath(__file__)).replace("\\", "\\\\")

CODE = r'''
def main():
    import json, os, struct, idautils, idc, ida_bytes, ida_funcs, ida_segment

    # address space, so we can reject address-like immediates
    lo, hi = None, 0
    ro = []
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        nm = ida_segment.get_segm_name(seg)
        lo = seg.start_ea if lo is None else min(lo, seg.start_ea)
        hi = max(hi, seg.end_ea)
        if nm in ("__cstring", "__const", ".rdata", "__text", ".text",
                  "__literal4", "__literal8"):
            ro.append((seg.start_ea, seg.end_ea))

    def in_ro(ea):
        return any(a <= ea < b for a, b in ro)

    # integers this common carry no signal at all
    BORING = set()
    for v in (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 24, 31, 32, 48, 63,
              64, 100, 127, 128, 200, 255, 256, 512, 1000, 1024, 2048, 4096,
              8192, 16384, 32767, 32768, 65535, 65536):
        BORING.add(v)
        BORING.add((-v) & 0xFFFFFFFF)
    BORING.add(0xFFFFFFFF)

    def fmt_f(x):
        # quantise so tiny representation differences still match
        return "f:%.6g" % x

    out = {}
    for f in idautils.Functions():
        toks = set()
        for ea in idautils.FuncItems(f):
            # ---- integer immediates ----
            for opn in range(3):
                if idc.get_operand_type(ea, opn) != idc.o_imm:
                    continue
                v = idc.get_operand_value(ea, opn) & 0xFFFFFFFF
                if v in BORING:
                    continue
                if lo <= v < hi:            # looks like an address -> useless
                    continue
                if v < 0x100:
                    continue
                toks.add("i:0x%x" % v)
            # ---- float/double literals via data refs ----
            for dr in idautils.DataRefsFrom(ea):
                if not in_ro(dr):
                    continue
                b4 = ida_bytes.get_bytes(dr, 4)
                if b4 and len(b4) == 4:
                    try:
                        fv = struct.unpack("<f", b4)[0]
                    except Exception:
                        fv = None
                    if (fv is not None and fv == fv and abs(fv) != float("inf")
                            and 1e-6 < abs(fv) < 1e9):
                        if fv not in (1.0, 0.5, 2.0, -1.0, 255.0, 100.0, 360.0):
                            toks.add(fmt_f(fv))
                b8 = ida_bytes.get_bytes(dr, 8)
                if b8 and len(b8) == 8:
                    try:
                        dv = struct.unpack("<d", b8)[0]
                    except Exception:
                        dv = None
                    if (dv is not None and dv == dv and abs(dv) != float("inf")
                            and 1e-6 < abs(dv) < 1e9):
                        if dv not in (1.0, 0.5, 2.0, -1.0, 255.0, 100.0, 360.0):
                            toks.add("d:%.9g" % dv)
        if toks:
            out["%x" % f] = sorted(toks)

    path = os.path.join(r"__RE_DIR__", "__KEY___consts.json")
    with open(path, "w", encoding="utf-8") as fh:
        json.dump(out, fh)
    return {"functions_with_consts": len(out),
            "distinct_tokens": len({t for v in out.values() for t in v})}
main()
'''

for key in sys.argv[1:]:
    port = PORTS.get(key) or int(key)
    code = CODE.replace("__RE_DIR__", RE_DIR).replace("__KEY__", key)
    print(key, "->", pyeval(port, code, timeout=1800))
