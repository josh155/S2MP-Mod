import json, os, struct
RE_DIR = r"c:\Users\joshu\OneDrive\Documents\GitHub\S2MP-Mod\re"
def main():
    import ida_bytes
    G = 0x1411a18           # g_netFieldList: POINTER VARIABLE
    reg = struct.unpack("<Q", ida_bytes.get_bytes(G, 8))[0]
    LABELS = ["EntityState","ArchivedEntity","ClientState","PlayerState","Objective","HudElem"]
    def cstr(ea, n=96):
        b = ida_bytes.get_bytes(ea, n) or b""
        i = b.find(b"\x00")
        if i <= 0: return None
        s = b[:i]
        return s.decode("ascii") if all(32 <= c < 127 for c in s) else None
    out = {"registry": hex(reg), "lists": {}}
    for k in range(6):
        rec = ida_bytes.get_bytes(reg + k*16, 16)
        ptr, cnt = struct.unpack("<Qq", rec)
        fields = []
        for i in range(cnt):
            r = ida_bytes.get_bytes(ptr + i*16, 16)
            nptr, off, size, bits, flags = struct.unpack("<QhhhH", r)
            fields.append({"i": i, "name": cstr(nptr) or "?", "offset": off,
                           "size": size, "bits": bits, "flags": flags})
        out["lists"][LABELS[k]] = {"ptr": hex(ptr), "count": cnt, "fields": fields}
    json.dump(out, open(os.path.join(RE_DIR,"ps4_netfields.json"),"w",encoding="utf-8"))
    return {k:(v["ptr"],v["count"]) for k,v in out["lists"].items()}
main()
