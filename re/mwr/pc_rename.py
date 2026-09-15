import ida_name, ida_funcs, json

# Behaviour-proven from call sites plus the named PS4 twin of the same function.
# The PC build strips these names; the PS4 build (same game, debug) keeps them.
NAMES = {
    0x4EB7D0: ("MSG_ReadLong", "reads msg+36/+28; serverTime in CL_ParseSnapshot"),
    0x4EB510: ("MSG_ReadByte", "Arxan-obfuscated body; identified from use (deltaNum, snapFlags)"),
    0x4EB190: ("MSG_Discard", "PS4 twin MSG_Discard; called on overflow paths"),
    0x4EC1E0: ("MSG_ClearLastReferencedEntity", "called before each of the 3 index streams"),
    0x4EC1F0: ("MSG_CopyFieldOver", "copies one netfield from baseline to target"),
    0x4EC2E0: ("MSG_FieldTypeInZeroBaseMask", "mask 0x1807E000001 over type+108"),
    0x4ECBE0: ("MSG_ReadDeltaEntity", "PS4 twin 0x7246F0, same structure"),
    0x4ED0E0: ("MSG_ReadDeltaField", "PS4 twin 0x7273A0"),
    0x4EDB98: ("MSG_ReadDeltaStruct", "PS4 twin 0x725240"),
    0x4F0780: ("MSG_ReadNumFieldsSkipped", "PS4 twin 0x726F60"),
    0x4F04B0: ("MSG_ReadEntityIndex", "PS4 twin 0x724540"),
    0x4F2C30: ("MSG_GetStateFieldListForEntityType", "PS4 twin 0x73A0C0, clamp at 20"),
    0x342770: ("CL_ParseSnapshot", "svc 6 handler from CL_ParseMessage"),
    0x341D30: ("CL_ParsePacketEntities", "MSG_ReadEntityIndex(msg, 11)"),
    0x341960: ("CL_ParsePacketClients", "MSG_ReadEntityIndex(msg, 5)"),
    0x341580: ("CL_ParsePacketAgents", "MSG_ReadEntityIndex(msg, 6)"),
    0x341420: ("CL_ParseMessage", "3-bit svc opcode dispatch"),
}

out = []
for ea, (name, basis) in NAMES.items():
    cur = ida_name.get_name(ea)
    if cur.startswith("sub_") or cur.startswith("nullsub") or cur == "":
        ok = ida_name.set_name(ea, name, ida_name.SN_NOCHECK | ida_name.SN_NOWARN)
        back = ida_name.get_name(ea)
        # set_name silently appends _0 on a collision and still reports success,
        # so read the name back rather than trusting the return value.
        out.append({"ea": "0x%X" % ea, "want": name, "got": back, "ok": bool(ok) and back == name})
        f = ida_funcs.get_func(ea)
        if f:
            ida_funcs.set_func_cmt(f, "Basis: %s" % basis, True)
    else:
        out.append({"ea": "0x%X" % ea, "want": name, "already": cur})
print(json.dumps(out, indent=0))
