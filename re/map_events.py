"""Build the CoD4 -> MWR event-enum mapping by NAME.

Both engines keep a contiguous EV_* name table in address order, so position ==
enum value. CoD4's run starts at EV_NONE (0); MWR's starts at EV_FOLIAGE_SOUND,
which is CoD4's index 1 - so MWR's table appears to omit index 0. That offset is
VERIFIED here rather than assumed, by checking how many names line up under each
candidate base.
"""
import json, os

RE = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE, n), encoding="utf-8"))

cod4 = L("ev_enum_cod4.json")["runs"][0]["names"]
mwr = L("ev_enum_mwr.json")["runs"][0]["names"]

# --- verify MWR's base offset instead of assuming it ---
best = None
for base in (0, 1):
    mwr_idx = {n: i + base for i, n in enumerate(mwr)}
    cod4_idx = {n: i for i, n in enumerate(cod4)}
    shared = set(mwr_idx) & set(cod4_idx)
    same = sum(1 for n in shared if mwr_idx[n] == cod4_idx[n])
    print(f"MWR base {base}: shared names {len(shared)}, identical index {same}")
    if best is None or same > best[1]:
        best = (base, same)
base = best[0]
print(f"-> using MWR base {base}\n")

mwr_idx = {n: i + base for i, n in enumerate(mwr)}
cod4_idx = {n: i for i, n in enumerate(cod4)}

mapped, only_cod4, only_mwr = {}, [], []
for n, i in cod4_idx.items():
    if n in mwr_idx:
        mapped[i] = (n, mwr_idx[n])
    else:
        only_cod4.append((i, n))
for n, i in mwr_idx.items():
    if n not in cod4_idx:
        only_mwr.append((i, n))

print(f"CoD4 events           : {len(cod4)}")
print(f"MWR events            : {len(mwr)}")
print(f"MAPPED by name        : {len(mapped)}")
print(f"CoD4-only (drop/synth): {len(only_cod4)}")
print(f"MWR-only  (unused)    : {len(only_mwr)}")
same_val = sum(1 for i, (n, j) in mapped.items() if i == j)
print(f"of the mapped, SAME numeric value: {same_val}  "
      f"({100.0*same_val/max(1,len(mapped)):.0f}%)  -> renumbering IS required")

print("\n--- CoD4 event 66 (the obituary temp entity) ---")
if 66 < len(cod4):
    n = cod4[66]
    print(f"  cod4[66] = {n}   -> MWR {mwr_idx.get(n, 'NO EQUIVALENT')}")

print("\n--- events for the user's requirements ---")
WANT = ["OBITUARY", "DEATH", "KILL", "GRENADE", "THROW", "FIRE_WEAPON", "MELEE",
        "RELOAD", "RAISE_WEAPON", "DROP_WEAPON", "SWITCH", "PICKUP", "HIT",
        "DAMAGE", "STANCE", "SPRINT", "JUMP", "LAND", "FOOTSTEP", "IMPACT"]
for key in WANT:
    hits = [(i, n) for n, i in cod4_idx.items() if key in n]
    hits.sort(key=lambda t: t[0])
    if not hits:
        continue
    print(f"  [{key}]")
    for i, n in hits[:8]:
        tgt = mwr_idx.get(n)
        flag = "" if tgt is not None else "   <-- NO MWR EQUIVALENT"
        print(f"     cod4 {i:3} {n:38} -> mwr {tgt}{flag}")

json.dump({"cod4": cod4, "mwr": mwr, "mwr_base": base,
           "mapped": {str(k): v for k, v in mapped.items()},
           "only_cod4": only_cod4, "only_mwr": only_mwr},
          open(os.path.join(RE, "event_map.json"), "w", encoding="utf-8"), indent=1)
