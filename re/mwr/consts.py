import ida_bytes, struct, json
out = {}
for a in (0xF9B8C0, 0xF9B8C4, 0xF9B8C8, 0xF9B8CC, 0xF9B8D0, 0xF9B8D4, 0xF9B8D8, 0xFA0C30):
    raw = ida_bytes.get_bytes(a, 4)
    out["0x%X" % a] = {"hex": raw.hex(), "f32": struct.unpack("<f", raw)[0],
                       "u32": struct.unpack("<I", raw)[0]}
print(json.dumps(out, indent=1))
