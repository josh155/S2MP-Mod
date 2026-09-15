"""METHOD: constraint resolution on AMBIGUOUS anchors.

The anchor pass throws away any string that has 2+ owners on either side - 648
strings on the reference side, 44 on the target side. But ambiguity is not the
same as uselessness: if a string is owned by {r1, r2} and {t1, t2}, and r1 is
already known to be t1, then r2 MUST be t2. That is deduction, not guessing.

Generalised: for a string with reference owners R and target owners T, drop the
already-mapped members from both sides; if exactly one candidate remains on each
side, the pair is forced.

Every forced pair is then required to be CONSISTENT across every string that
forces it - a pair contradicted by any other string is dropped.

Unlike the graph vote, this method can land on already-named functions, so it is
directly measurable with the standard harness.

    python re/cod4x_ambiguous.py [max_owners]
writes re/cod4x_ambig_proposals.json
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name, is_named

MAX_OWNERS = 4
for _a in sys.argv[1:]:
    if _a.isdigit():
        MAX_OWNERS = int(_a)
CROSSVAL = "--crossval" in sys.argv and __name__ == "__main__"
MIN_WITNESS = 1
if "--witness" in sys.argv:
    MIN_WITNESS = int(sys.argv[sys.argv.index("--witness") + 1])

ref = load("cod4_strowners.json")
tgt = load("cod4x_strowners.json")
tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
rg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}

ref_clean = {}
for ea, v in rg.items():
    nm = clean_ref_name(v[1], ea)
    if nm:
        ref_clean[ea] = nm
name_count = collections.Counter(ref_clean.values())

# the mapping we already trust, both directions
ref_by_name = collections.defaultdict(list)
for ea, nm in ref_clean.items():
    ref_by_name[nm].append(ea)
ref_uniq = {nm: e[0] for nm, e in ref_by_name.items() if len(e) == 1}
tgt_by_name = collections.defaultdict(list)
for ea, v in tg.items():
    if is_named(v[1]):
        tgt_by_name[v[1]].append(ea)
def build_M(exclude=()):
    return {e[0]: ref_uniq[nm] for nm, e in tgt_by_name.items()
            if len(e) == 1 and nm in ref_uniq and e[0] not in exclude}


def deduce(M, max_owners=MAX_OWNERS):
    """Forced-by-elimination pairs, given a trusted mapping M."""
    rev = {r: t for t, r in M.items()}
    forced = collections.defaultdict(collections.Counter)
    witness = collections.defaultdict(list)
    stats = collections.Counter()
    for s, R in ref["owners"].items():
        T = tgt["owners"].get(s)
        if not T:
            continue
        if len(R) == 1 and len(T) == 1:
            stats["already_unambiguous"] += 1; continue
        if len(R) > max_owners or len(T) > max_owners:
            stats["too_many_owners"] += 1; continue
        R_free = [r for r in R if r not in rev]
        T_free = [t for t in T if t not in M]
        if len(R_free) != 1 or len(T_free) != 1:
            stats["not_reduced_to_one"] += 1; continue
        # STRICT: the two owner sets must correspond EXACTLY apart from the one
        # free element each. ">=1 anchor in common" was too weak - it let
        # partially-overlapping sets through and cost 3 of 93 (96.77%).
        if any(rev[r] not in T for r in R if r in rev):
            stats["ref_owner_maps_outside"] += 1; continue
        if any(M[t] not in R for t in T if t in M):
            stats["tgt_owner_maps_outside"] += 1; continue
        if len(R) - 1 == 0:
            stats["no_anchor_in_common"] += 1; continue
        r, t = R_free[0], T_free[0]
        nm = ref_clean.get(r)
        if not nm or name_count[nm] != 1:
            stats["ref_name_unusable"] += 1; continue
        stats["FORCED"] += 1
        forced[t][r] += 1
        witness[(t, r)].append(s)
    out = {}
    for t, cnt in forced.items():
        if len(cnt) != 1:
            stats["contradicted"] += 1; continue
        r = next(iter(cnt))
        if MIN_WITNESS > 1 and len(witness[(t, r)]) < MIN_WITNESS:
            stats["too_few_witnesses"] += 1; continue
        out[t] = {"name": ref_clean[r], "ref_ea": r,
                  "evidence": f"forced by elimination on "
                              f"{len(witness[(t, r)])} shared string(s), e.g. "
                              f"{witness[(t, r)][0]!r}"}
    return out, stats


if CROSSVAL:
    import random
    truth = {ea: v[1] for ea, v in tg.items() if is_named(v[1])}
    keys = sorted(truth)
    random.Random(23).shuffle(keys)
    FOLDS = 5
    rec = ok = bad = 0
    wrong = []
    for i in range(FOLDS):
        hide = set(keys[i::FOLDS])
        props, _ = deduce(build_M(exclude=hide))
        for h in hide:
            if h in props:
                rec += 1
                if props[h]["name"] == truth[h]:
                    ok += 1
                else:
                    bad += 1
                    if len(wrong) < 8:
                        wrong.append((h, truth[h], props[h]["name"]))
    print(f"CROSSVAL {FOLDS} folds over {len(keys)} known names:")
    print(f"  recovered {rec}  correct {ok}  wrong {bad}  "
          f"PRECISION {100.0*ok/rec if rec else 0:.2f}%")
    for h, t, p in wrong:
        print(f"    0x{h:<8x} truth={t!r} deduced={p!r}")
    sys.exit(0)

if __name__ == "__main__":
    M = build_M()
    rev = {r: t for t, r in M.items()}
    print(f"trusted mapping: {len(M):,}")

    forced = collections.defaultdict(collections.Counter)   # tgt -> Counter(ref)
    witness = collections.defaultdict(list)
    stats = collections.Counter()

    for s, R in ref["owners"].items():
        T = tgt["owners"].get(s)
        if not T:
            continue
        if len(R) == 1 and len(T) == 1:
            stats["already_unambiguous"] += 1
            continue
        if len(R) > MAX_OWNERS or len(T) > MAX_OWNERS:
            stats["too_many_owners"] += 1
            continue
        # remove members already accounted for by the trusted mapping
        R_free = [r for r in R if r not in rev]
        T_free = [t for t in T if t not in M]
        # every dropped reference owner should correspond to a dropped target owner,
        # otherwise the two owner sets are not the same set of functions
        matched = sum(1 for r in R if r in rev and rev[r] in T)
        if matched == 0:
            stats["no_anchor_in_common"] += 1
            continue
        if len(R_free) != 1 or len(T_free) != 1:
            stats["not_reduced_to_one"] += 1
            continue
        r, t = R_free[0], T_free[0]
        nm = ref_clean.get(r)
        if not nm or name_count[nm] != 1:
            stats["ref_name_unusable"] += 1
            continue
        stats["FORCED"] += 1
        forced[t][r] += 1
        witness[(t, r)].append(s)

    print(f"strings examined:")
    for k, v in stats.most_common():
        print(f"  {k:24} {v:,}")

    proposals, dropped = {}, 0
    for t, cnt in forced.items():
        if len(cnt) != 1:                 # contradicted by another string
            dropped += 1
            continue
        r = next(iter(cnt))
        proposals[t] = {"name": ref_clean[r], "ref_ea": r,
                        "evidence": f"forced by elimination on "
                                    f"{len(witness[(t, r)])} shared string(s), e.g. "
                                    f"{witness[(t, r)][0]!r}"}
    print(f"  dropped, contradicted    {dropped}")

    byname = collections.defaultdict(list)
    for t, p in proposals.items():
        byname[p["name"]].append(t)
    for nm, ts in byname.items():
        if len(ts) > 1:
            for t in ts:
                proposals.pop(t, None)

    print(f"PROPOSALS                  {len(proposals):,}")
    json.dump({str(k): v for k, v in proposals.items()},
              open(os.path.join(RE_DIR, "cod4x_ambig_proposals.json"), "w",
                   encoding="utf-8"))
