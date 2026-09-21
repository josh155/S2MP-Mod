import ida_bytes, ida_name, json, struct

ea = ida_name.get_name_ea(0, "g_netFieldList")
out = {"g_netFieldList": "0x%X" % ea}
if ea == 0xFFFFFFFFFFFFFFFF:
    print(json.dumps(out)); raise SystemExit

def s(a):
    p = ida_bytes.get_qword(a)
    if not p:
        return None
    b = ida_bytes.get_strlit_contents(p, -1, 0)
    return b.decode("latin-1") if b else None

# The PS4 build keeps the field NAME in the struct, so the layout is 16 bytes:
#   +0 name*  +8 offset  +10 size  +12 type  +14 flags
def readlist(ptr, n):
    return [{"i": i,
             "name": s(ptr + 16 * i),
             "offset": ida_bytes.get_word(ptr + 16 * i + 8),
             "size": struct.unpack("<h", ida_bytes.get_bytes(ptr + 16 * i + 10, 2))[0],
             "type": struct.unpack("<h", ida_bytes.get_bytes(ptr + 16 * i + 12, 2))[0],
             "flags": ida_bytes.get_word(ptr + 16 * i + 14)} for i in range(n)]

reg = []
for i in range(28):
    e = ea + 16 * i
    p = ida_bytes.get_qword(e)
    c = ida_bytes.get_dword(e + 8)
    reg.append({"i": i, "ptr": "0x%X" % p, "count": c})
out["registry"] = reg
# probe entry 0 and 1 so the layout can be judged before dumping everything
for i in (0, 1):
    p = ida_bytes.get_qword(ea + 16 * i)
    c = ida_bytes.get_dword(ea + 16 * i + 8)
    if p and 0 < c <= 400:
        out["sample%d" % i] = readlist(p, min(c, 6))
print(json.dumps(out, indent=1))
