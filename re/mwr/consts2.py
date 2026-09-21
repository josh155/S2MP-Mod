import ida_bytes, struct, json
out = {}
for a in (0xFA0C30, 0xFA0C34, 0xFA0C38, 0xFA0C3C, 0xFA0C40):
    raw = ida_bytes.get_bytes(a, 4)
    out["0x%X" % a] = struct.unpack("<f", raw)[0]
print(json.dumps(out))
