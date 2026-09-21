import ida_bytes, json

REG = 0x12D4BB0          # per-eType {ptr,count} registry, 28 entries
OUT = r"F:\Coding\H1-Mod-Demos\demo-corpus\docs\cod4_to_h1\mwr_netfields_full.json"

def u16(a): return ida_bytes.get_word(a)
def i16(a):
    v = ida_bytes.get_word(a)
    return v - 65536 if v >= 32768 else v
def u32(a): return ida_bytes.get_dword(a)
def u64(a): return ida_bytes.get_qword(a)

def read_list(ptr, count):
    out = []
    for i in range(count):
        e = ptr + 8 * i
        out.append({
            "i": i,
            "offset": u16(e + 0),
            "bits":   i16(e + 2),
            "type":   i16(e + 4),      # SIGNED: negatives are special encoders
            "flags":  u16(e + 6),
        })
    return out

def main():
    reg = []
    lists = {}
    for i in range(28):
        e = REG + 16 * i
        ptr = u64(e)
        cnt = u32(e + 8)
        reg.append({"i": i, "ptr": "0x%X" % ptr, "count": cnt})
        if ptr and 0 < cnt <= 400:
            key = "0x%X" % ptr
            if key not in lists:
                lists[key] = read_list(ptr, cnt)
    data = {"registry": reg, "lists": lists}
    with open(OUT, "w") as f:
        json.dump(data, f, indent=1)
    return {"registry": len(reg), "lists": len(lists),
            "total_fields": sum(len(v) for v in lists.values()), "out": OUT}

print(json.dumps(main()))
