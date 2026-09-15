import ida_bytes, json
# MSG_ReadDeltaField case -94 indexes this as a u32 array by eventType, and the
# engine's own assert bounds eventType at 186 (EV_MAX_EVENTS).
vals = [ida_bytes.get_dword(0xF9BA00 + 4 * i) for i in range(186)]
print(json.dumps(vals))
