"""RUNS INSIDE IDA (CoD4 18337). Dump every netfield table by POINTER.

Tables come from s_netFieldList @0x410040 (18 entries {fields*, count}, indexed by
eType clamped to 17) plus the four standalone tables. Counts are the binary's own,
so nothing is guessed or truncated by a heuristic terminator.
"""
import json, struct
OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\cod4_all_netfields.json"

def main():
    import ida_bytes, ida_name
    def cstr(ea, n=96):
        b = ida_bytes.get_bytes(ea, n) or b""
        i = b.find(b"\x00")
        if i <= 0: return None
        s = b[:i]
        return s.decode("ascii") if all(32 <= c < 127 for c in s) else None

    def read_table(ptr, cnt):
        fields = []
        for i in range(cnt):
            rec = ida_bytes.get_bytes(ptr + i*16, 16)
            nptr, off, bits, typ, hints = struct.unpack("<IIhHI", rec)
            fields.append({"i": i, "name": cstr(nptr), "offset": off,
                           "bits": bits, "changeHints": hints})
        return fields

    out = {"etype": {}, "tables": {}}
    b = ida_bytes.get_bytes(0x410040, 18*8)
    for i in range(18):
        ptr, cnt = struct.unpack_from("<II", b, i*8)
        nm = (ida_name.get_name(ptr) or hex(ptr)).lstrip("_")
        for pre in ("ZL13","ZL27","ZL16","ZL"):
            if nm.startswith(pre): nm = nm[len(pre):]
        out["etype"][i] = {"table": nm, "count": cnt}
        if nm not in out["tables"]:
            out["tables"][nm] = {"base": hex(ptr), "count": cnt,
                                 "fields": read_table(ptr, cnt)}
    # standalone tables with counts read from the binary
    for nm, ptr, cptr in (("clientStateFields", 0x40f300, 0x3a9564),
                          ("playerStateFields", 0x40f480, 0x3a9568),
                          ("objectiveFields",   0x40fd60, 0x3a956c)):
        cnt = struct.unpack("<I", ida_bytes.get_bytes(cptr, 4))[0]
        out["tables"][nm] = {"base": hex(ptr), "count": cnt,
                             "fields": read_table(ptr, cnt)}
    with open(OUT, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=1)
    return {k: v["count"] for k, v in out["tables"].items()}
main()
