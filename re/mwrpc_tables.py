"""RUNS INSIDE IDA (MWR-PC). Find self-naming {name, function} tables.

Strongest evidence tier: the target binary itself pairs a name string with a
function pointer, so no cross-binary inference is involved.

Scans .rdata for runs of qword slots that alternate "pointer to a printable
string" / "pointer to a function start", inferring stride and the field offset
from the data rather than assuming stride 16.

Also harvests registrar-style pairings where the name and handler are passed as
ARGUMENTS (Cmd_AddCommandInternal), by walking back from each call.

Writes re/mwrpc_tables.json.
"""
import json, os

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"


def main():
    import idautils, ida_bytes, ida_funcs, ida_segment, ida_name, idc

    # ---- segment map -----------------------------------------------------
    code_lo = code_hi = None
    rdata = None
    for s in idautils.Segments():
        seg = ida_segment.getseg(s)
        nm = ida_segment.get_segm_name(seg)
        if seg.perm & ida_segment.SEGPERM_EXEC and code_lo is None:
            code_lo, code_hi = seg.start_ea, seg.end_ea
        if nm == ".rdata":
            rdata = (seg.start_ea, seg.end_ea)

    func_starts = set()
    for ea in idautils.Functions():
        if code_lo <= ea < code_hi:
            func_starts.add(ea)

    lo, hi = rdata
    buf = ida_bytes.get_bytes(lo, hi - lo) or b""

    def qw(off):
        return int.from_bytes(buf[off:off + 8], "little")

    def as_str(addr):
        """Printable NUL-terminated string living inside .rdata."""
        if not (lo <= addr < hi):
            return None
        o = addr - lo
        end = buf.find(b"\x00", o, min(o + 128, len(buf)))
        if end < 0 or end - o < 2:
            return None
        s = buf[o:end]
        try:
            t = s.decode("ascii")
        except Exception:
            return None
        if not all(32 <= c < 127 for c in s):
            return None
        return t

    n = (hi - lo) // 8
    kind = bytearray(n)          # 1 = string ptr, 2 = func ptr
    for i in range(n):
        v = qw(i * 8)
        if not v:
            continue
        if v in func_starts:
            kind[i] = 2
        elif as_str(v):
            kind[i] = 1

    # ---- find alternating runs, inferring stride --------------------------
    tables = []
    for stride_q in (2, 3, 4, 6, 8):        # stride in qwords
        for sfield in range(stride_q):
            for ffield in range(stride_q):
                if sfield == ffield:
                    continue
                i = 0
                while i < n:
                    if kind[i] == 1 and i - sfield >= 0:
                        base = i - sfield
                        cnt = 0
                        j = base
                        while (j + max(sfield, ffield) < n
                               and kind[j + sfield] == 1
                               and kind[j + ffield] == 2):
                            cnt += 1
                            j += stride_q
                        if cnt >= 6:
                            tables.append({
                                "base": lo + base * 8,
                                "stride": stride_q * 8,
                                "name_off": sfield * 8,
                                "func_off": ffield * 8,
                                "count": cnt,
                            })
                            i = j
                            continue
                    i += 1

    # dedupe: keep the longest table starting at each base
    best = {}
    for t in tables:
        k = t["base"]
        if k not in best or t["count"] > best[k]["count"]:
            best[k] = t
    # drop tables fully contained in a bigger one
    ordered = sorted(best.values(), key=lambda t: (-t["count"], t["base"]))
    kept, covered = [], []
    for t in ordered:
        end = t["base"] + t["stride"] * t["count"]
        if any(t["base"] >= a and end <= b for a, b in covered):
            continue
        kept.append(t)
        covered.append((t["base"], end))

    out = []
    for t in kept:
        pairs = []
        for k in range(t["count"]):
            rec = t["base"] + k * t["stride"]
            sp = int.from_bytes(buf[rec - lo + t["name_off"]:rec - lo + t["name_off"] + 8], "little")
            fp = int.from_bytes(buf[rec - lo + t["func_off"]:rec - lo + t["func_off"] + 8], "little")
            s = as_str(sp)
            if s and fp in func_starts:
                pairs.append([s, hex(fp), ida_name.get_name(fp)])
        if len(pairs) >= 6:
            t["pairs"] = pairs
            out.append(t)

    # ---- registrar-style: Cmd_AddCommandInternal(name, fn, ...) ----------
    cmds = []
    reg = None
    for ea in idautils.Functions():
        nm = ida_name.get_name(ea)
        if nm in ("Cmd_AddCommandInternal", "Cmd_AddServerCommandInternal"):
            reg = ea
            break
    if reg:
        for xr in idautils.CodeRefsTo(reg, 0):
            f = ida_funcs.get_func(xr)
            if not f:
                continue
            name_s = fn_ea = None
            ea2 = xr
            for _ in range(24):
                ea2 = idc.prev_head(ea2, f.start_ea)
                if ea2 == idc.BADADDR or ea2 < f.start_ea:
                    break
                mnem = idc.print_insn_mnem(ea2)
                if mnem != "lea":
                    continue
                dst = idc.print_operand(ea2, 0)
                v = idc.get_operand_value(ea2, 1)
                if dst == "rcx" and name_s is None:
                    s = as_str(v)
                    if s:
                        name_s = s
                elif dst == "rdx" and fn_ea is None:
                    if v in func_starts:
                        fn_ea = v
            if name_s and fn_ea:
                cmds.append([name_s, hex(fn_ea), ida_name.get_name(fn_ea)])

    res = {"tables": out, "commands": cmds,
           "registrar": hex(reg) if reg else None}
    json.dump(res, open(os.path.join(RE_DIR, "mwrpc_tables.json"), "w",
                        encoding="utf-8"))
    return {"tables": len(out),
            "pairs": sum(len(t["pairs"]) for t in out),
            "commands": len(cmds),
            "registrar": res["registrar"]}


main()
