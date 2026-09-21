"""RUNS INSIDE IDA (CoD4-named 18337). Dump every netfield table.

CoD4 netField_t (32-bit build) = 16 bytes:
    {const char* name; u32 offset; i16 bits; u16 type; u32 flags/changeHints}
matching the layout the existing iw3_playerstate_netfields.json records.
"""
import json, struct, os
OUT = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re\cod4_named_netfields.json"

TABLES = [
    ("entityStateFields", 0x40c920), ("eventEntityStateFields", 0x40cce0),
    ("playerEntityStateFields", 0x40d0a0), ("corpseEntityStateFields", 0x40d460),
    ("vehicleEntityStateFields", 0x40d820), ("itemEntityStateFields", 0x40dbe0),
    ("scriptMoverStateFields", 0x40dfa0), ("soundBlendEntityStateFields", 0x40e360),
    ("loopFxEntityStateFields", 0x40e720), ("missileEntityStateFields", 0x40eae0),
    ("clientStateFields", 0x40f300), ("playerStateFields", 0x40f480),
    ("objectiveFields", 0x40fd60),
]

def main():
    import ida_bytes
    def cstr(ea, n=96):
        b = ida_bytes.get_bytes(ea, n) or b""
        i = b.find(b"\x00")
        if i <= 0: return None
        s = b[:i]
        return s.decode("ascii") if all(32 <= c < 127 for c in s) else None
    out = {}
    for name, base in TABLES:
        fields = []
        for i in range(300):
            rec = ida_bytes.get_bytes(base + i*16, 16)
            if not rec or len(rec) < 16: break
            nptr, off, bits, typ, flags = struct.unpack("<IIhHI", rec)
            s = cstr(nptr)
            if not s or not (s[0].isalpha() or s[0] == '_'): break
            fields.append({"i": i, "name": s, "offset": off,
                           "bits": bits, "type": typ, "flags": flags})
        out[name] = {"base": hex(base), "count": len(fields), "fields": fields}
    with open(OUT, "w", encoding="utf-8") as f:
        json.dump(out, f, indent=1)
    return {k: v["count"] for k, v in out.items()}
main()
