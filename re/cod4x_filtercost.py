"""What did the MAC_ONLY blocklist actually COST us?

For each blocklist prefix, count the reference functions it rejects AND how many
of those had a usable anchor into the target - i.e. names we threw away.

A filter that rejects the majority of a reference set must be audited, not
trusted. This is the second time in this pass that a name filter silently
discarded a whole subsystem.
"""
import collections
from cod4x_common import (load, demangle, ida_safe, distinctive, MAC_ONLY,
                          is_named)

ref = load("cod4_strowners.json")
tgt = load("cod4x_strowners.json")
ref_names = {int(k): v for k, v in ref["names"].items()}
tgt_names = {int(k): v for k, v in tgt["names"].items()}


def demangle_only(n):
    """clean_ref_name WITHOUT the MAC_ONLY blocklist."""
    if not n or n.startswith(("-[", "+[")) or "[" in n:
        return None
    if n.startswith(("sub_", "nullsub_", "j_", "unknown_", "loc_")):
        return None
    dm = demangle(n)
    if dm:
        if dm.startswith("std::") or "?" in dm:
            return None
        if dm.split("::")[0] in ("std", "__gnu_cxx", "CCallback", "CCallResult"):
            return None
        return ida_safe(dm)
    if n.startswith("__"):
        return None
    if n.startswith("_"):
        n = n[1:]
    return n or None


# every anchor that WOULD be usable if the blocklist did not exist
cost = collections.defaultdict(lambda: {"funcs": set(), "anchors": 0})
usable_no_blocklist = 0
for s, ro in ref["owners"].items():
    to = tgt["owners"].get(s)
    if not to or len(ro) != 1 or len(to) != 1:
        continue
    nm = demangle_only(ref_names.get(ro[0], ""))
    if not nm:
        continue
    usable_no_blocklist += 1
    for p in MAC_ONLY:
        if nm.startswith(p):
            cost[p]["funcs"].add((nm, to[0]))
            cost[p]["anchors"] += 1
            break

print(f"usable anchors with NO blocklist : {usable_no_blocklist:,}")
print(f"usable anchors WITH blocklist    : 2,924  (measured earlier)\n")
print(f"{'prefix':<12} {'anchors':>8} {'funcs':>6}  lost names (sample)")
print("-" * 78)
tot_f = 0
for p, d in sorted(cost.items(), key=lambda kv: -len(kv[1]["funcs"])):
    names = sorted({n for n, _ in d["funcs"]})
    tot_f += len(names)
    print(f"{p:<12} {d['anchors']:>8} {len(names):>6}  "
          f"{', '.join(names[:5])[:56]}")
print("-" * 78)
print(f"TOTAL target functions the blocklist denied a name: {tot_f}")

# how many are engine subsystems rather than macOS APIs?
ENGINE = ("CG_", "CL_", "SV_", "G_", "BG_", "R_", "Com_", "Scr_", "GScr_",
          "UI_", "FS_", "SND_", "DB_", "Sys_", "Dvar_", "StringTable",
          "String", "Stream", "Struct")
eng = sorted({n for d in cost.values() for n, _ in d["funcs"]
              if n.startswith(ENGINE)})
print(f"\nof those, clearly ENGINE names wrongly blocked: {len(eng)}")
for n in eng[:40]:
    print("   ", n)
