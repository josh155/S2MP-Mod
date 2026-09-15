import ida_bytes, ida_name, json, struct

sym = ida_name.get_name_ea(0, "g_entityStateNetFieldList")
base = ida_bytes.get_qword(sym)
out = {"sym": "0x%X" % sym, "registry_base": "0x%X" % base}

def s(a):
    p = ida_bytes.get_qword(a)
    if not p:
        return None
    b = ida_bytes.get_strlit_contents(p, -1, 0)
    return b.decode("latin-1") if b else None

def readlist(ptr, n):
    return [{"i": i,
             "name": s(ptr + 16 * i),
             "offset": ida_bytes.get_word(ptr + 16 * i + 8),
             "size": struct.unpack("<h", ida_bytes.get_bytes(ptr + 16 * i + 10, 2))[0],
             "type": struct.unpack("<h", ida_bytes.get_bytes(ptr + 16 * i + 12, 2))[0],
             "flags": ida_bytes.get_word(ptr + 16 * i + 14)} for i in range(n)]

lists = {}
reg = []
for i in range(21):
    p = ida_bytes.get_qword(base + 16 * i)
    c = ida_bytes.get_dword(base + 16 * i + 8)
    reg.append({"eType": i, "ptr": "0x%X" % p, "count": c})
    if p and 0 < c <= 400 and "0x%X" % p not in lists:
        lists["0x%X" % p] = readlist(p, c)
out["registry"] = reg
out["lists"] = lists
with open(r"F:\Coding\H1-Mod-Demos\demo-corpus\docs\cod4_to_h1\mwr_ps4_entity_netfields_named.json", "w") as f:
    json.dump(out, f, indent=1)
print(json.dumps({"registry": reg[:3], "n_lists": len(lists),
                  "sample": lists.get(reg[1]["ptr"], [])[:5]}, indent=1))
