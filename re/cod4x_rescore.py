"""Re-score anchors after the filter fix, and CLASSIFY against what is already
applied.

The first pass applied 1,239 names, so a fresh anchor can now land on a function
that call-graph propagation already named. Three outcomes, and they must be told
apart rather than silently skipped:

    NEW       the function is unnamed        -> apply
    AGREE     already has exactly this name  -> corroboration, two independent
                                                methods agreeing
    CONFLICT  already has a DIFFERENT name   -> anchor evidence vs graph
                                                evidence. Reported, never
                                                silently dropped.

Writes re/cod4x_proposals.json (NEW only) and re/cod4x_conflicts.json.
"""
import json, os, collections
from cod4x_common import RE_DIR, build_votes, is_named, load

DOM_RATIO = 3.0
DOM_MIN_ANCHORS = 3

votes, stats, ref, tgt = build_votes()

# current names come from the LIVE dump taken by the audit, not the stale export
try:
    live = {int(k, 16): v[0] for k, v in load("cod4x_named_dump.json").items()}
except Exception:
    live = {}
tgt_names = {int(k): v for k, v in tgt["names"].items()}
cur = dict(tgt_names)
cur.update(live)

# basis tier of each applied name, so a conflict can be judged
applied = {}
for fn in ("cod4x_applied.json", "cod4x_loop_plan.json"):
    try:
        for k, v in load(fn).items():
            applied[int(k)] = v.get("comment", "")
    except Exception:
        pass


def support_of(cmt):
    import re as _re
    m = _re.search(r"support=(\d+)", cmt or "")
    return int(m.group(1)) if m else None


def anchors_of(cmt):
    import re as _re
    m = _re.search(r"anchor tier=\w+ n=(\d+)", cmt or "")
    return int(m.group(1)) if m else None


cand = collections.Counter()
proposals, conflicts, agree = {}, [], 0
raw = {}
for ea, vs in votes.items():
    names = {n for _, n, _, _ in vs}
    if len(names) != 1:
        cand["split_vote"] += 1
        continue
    name = names.pop()
    best = max(s for _, _, s, _ in vs)
    ref_ea = collections.Counter(r for _, _, _, r in vs).most_common(1)[0][0]
    tier = ("multi" if len(vs) >= 2 and any(s >= 2 for _, _, s, _ in vs) else
            "single_strong" if best >= 3 else "single_weak")
    raw[ea] = {"name": name, "tier": tier, "n_anchors": len(vs),
               "best_score": best, "ref_ea": ref_ea,
               "anchors": sorted((a for a, _, _, _ in vs), key=len)[-4:]}

# one name, one function (+ strict dominance recovery)
byname = collections.defaultdict(list)
for ea, p in raw.items():
    byname[p["name"]].append(ea)
kept = {}
recovered = ambiguous = 0
for name, eas in byname.items():
    if len(eas) == 1:
        kept[eas[0]] = raw[eas[0]]
        continue
    ranked = sorted(eas, key=lambda e: (-raw[e]["n_anchors"], -raw[e]["best_score"]))
    top, runner = raw[ranked[0]], raw[ranked[1]]
    if (top["n_anchors"] >= DOM_MIN_ANCHORS and top["best_score"] >= 2 and
            top["n_anchors"] >= DOM_RATIO * runner["n_anchors"]):
        p = dict(top); p["tier"] = "dominant"
        p["dominance"] = f"{top['n_anchors']} anchors vs {runner['n_anchors']}"
        kept[ranked[0]] = p
        recovered += 1
    else:
        ambiguous += 1

for ea, p in kept.items():
    existing = cur.get(ea, "")
    if is_named(existing):
        if existing == p["name"]:
            agree += 1
        else:
            conflicts.append({
                "tgt": ea, "anchor_name": p["name"],
                "anchor_n": p["n_anchors"], "anchor_tier": p["tier"],
                "existing": existing,
                "existing_support": support_of(applied.get(ea, "")),
                "existing_anchors": anchors_of(applied.get(ea, "")),
                "ref_ea": p["ref_ea"]})
    else:
        proposals[ea] = p

print(f"USABLE ANCHORS (filter fixed)   : {stats['anchor_usable']:,}"
      f"   (was 2,924)")
print(f"target funcs receiving votes    : {len(votes):,}")
print(f"  collisions recovered          : {recovered}")
print(f"  collisions left ambiguous     : {ambiguous}")
print(f"  AGREE with an applied name    : {agree}   <- independent corroboration")
print(f"  CONFLICT with an applied name : {len(conflicts)}")
print(f"  NEW, applicable               : {len(proposals):,}")
tiers = collections.Counter(p["tier"] for p in proposals.values())
for t in ("multi", "dominant", "single_strong", "single_weak"):
    print(f"     {t:14}: {tiers.get(t,0):,}")

json.dump({str(k): v for k, v in proposals.items()},
          open(os.path.join(RE_DIR, "cod4x_proposals.json"), "w", encoding="utf-8"))
json.dump(conflicts, open(os.path.join(RE_DIR, "cod4x_conflicts.json"),
                          "w", encoding="utf-8"))

print("\n--- CONFLICTS (anchor vs already-applied) ---")
for c in sorted(conflicts, key=lambda c: -c["anchor_n"]):
    print(f"  0x{c['tgt']:<8x} anchor {c['anchor_name'][:34]:34} n={c['anchor_n']:<3}"
          f" vs applied {c['existing'][:30]:30} "
          f"sup={c['existing_support']} anch={c['existing_anchors']}")

print("\n--- sample of NEW CG_ names ---")
for ea, p in sorted(proposals.items(), key=lambda kv: -kv[1]["n_anchors"]):
    if p["name"].startswith("CG_"):
        print(f"  0x{ea:<8x} {p['name'][:44]:44} n={p['n_anchors']}")
