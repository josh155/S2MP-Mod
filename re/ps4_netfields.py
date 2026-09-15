"""RUNS INSIDE IDA (MWR-PS4). Dump the netfield tables WITH names.

The three accessors resolve the tables:
    GetEntityStateNetFields  0x72b590
    GetPlayerStateNetFields  0x72b5f0
    GetClientStateNetFields  0x72b620

A debug build keeps the field NAME pointer in each record (MSG_DumpNetFieldChanges_f
prints them), so the record layout can be recovered by probing for a stride where
slot 0 is a pointer to a plausible identifier.

Writes re/ps4_netfields.json.
"""
import json, os, struct

RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"


def main():
    import idautils, ida_bytes, ida_segment, idc, ida_funcs, ida_name

    segs = [(ida_segment.getseg(s).start_ea, ida_segment.getseg(s).end_ea)
            for s in idautils.Segments()]
    lo = min(a for a, _ in segs)
    hi = max(b for _, b in segs)

    def rd(ea, n):
        return ida_bytes.get_bytes(ea, n) or b""

    def cstr(ea, maxn=96):
        b = rd(ea, maxn)
        i = b.find(b"\x00")
        if i <= 0:
            return None
        s = b[:i]
        if not all(32 <= c < 127 for c in s):
            return None
        return s.decode("ascii")

    # the accessors just return a global table pointer; pull the operand
    tables = {}
    for name in ("GetEntityStateNetFields", "GetPlayerStateNetFields",
                 "GetClientStateNetFields"):
        ea = None
        for f in idautils.Functions():
            if ida_name.get_name(f) == name:
                ea = f
                break
        if ea is None:
            continue
        cands = []
        cur = ea
        for _ in range(24):
            for k in (0, 1):
                v = idc.get_operand_value(cur, k)
                if v and lo <= v < hi:
                    cands.append(v)
            cur = idc.next_head(cur, ea + 200)
            if cur == idc.BADADDR:
                break
        tables[name] = cands

    # probe a table: find a stride where slot0 is a name pointer
    def probe(base):
        best = None
        for stride in (16, 24, 32, 40, 48):
            names, ok = [], 0
            for i in range(6):
                p = struct.unpack("<Q", rd(base + i * stride, 8))[0]
                s = cstr(p) if lo <= p < hi else None
                if s and s[0].isalpha():
                    ok += 1
                    names.append(s)
            if ok >= 5:
                best = (stride, names)
                break
        return best

    out = {}
    for name, cands in tables.items():
        for base in cands:
            pr = probe(base)
            if not pr:
                continue
            stride, _ = pr
            fields = []
            for i in range(400):
                rec = base + i * stride
                p = struct.unpack("<Q", rd(rec, 8))[0]
                s = cstr(p) if lo <= p < hi else None
                if not s or not s[0].isalpha():
                    break
                off, bits, typ = struct.unpack("<iii", rd(rec + 8, 12))
                fields.append({"i": i, "name": s, "offset": off,
                               "bits": bits, "type": typ})
            if len(fields) >= 10:
                out[name] = {"base": hex(base), "stride": stride,
                             "count": len(fields), "fields": fields}
                break

    json.dump(out, open(os.path.join(RE_DIR, "ps4_netfields.json"), "w",
                        encoding="utf-8"))
    return {k: {"base": v["base"], "stride": v["stride"], "count": v["count"]}
            for k, v in out.items()}


main()
