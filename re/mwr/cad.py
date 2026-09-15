import ida_bytes, ida_name, struct, json
ea = ida_name.get_name_ea(0, "g_commonAngleDeltas")
out = {"ea": "0x%X" % ea}
if ea != 0xFFFFFFFFFFFFFFFF:
    out["f32"] = [struct.unpack("<f", ida_bytes.get_bytes(ea + 4 * i, 4))[0] for i in range(8)]
    out["i32"] = [ida_bytes.get_dword(ea + 4 * i) for i in range(8)]
print(json.dumps(out))
