"""METHOD: dominance-based graph voting - the big relaxation.

cod4x_propagate.py demands that the intersection of every mapped neighbour's
counterpart set leaves EXACTLY ONE survivor. Safe, but brittle: a single inlined
or missing call edge empties the intersection, and it converged with ~7,500
functions still unnamed.

Here the neighbours VOTE instead. For an unmapped target X:

    for each mapped callee c of X : every caller of M[c] gets a vote
    for each mapped caller p of X : every callee of M[p] gets a vote

Accept the top candidate when it reaches MIN_VOTES and beats the runner-up by
RATIO. Votes are WEIGHTED BY NEIGHBOUR RARITY - being called by a function with
three callers is far more informative than being called by Com_Printf - which is
what stops hub functions dominating every ballot.

⚠ VALIDATION IS NOT OPTIONAL AND NOT CIRCULAR. This method cannot be scored by
comparing against already-named functions, because it never proposes for one. So
it is cross-validated: hide a slice of the STRING-derived names (independent
evidence), rebuild the mapping without them, and see whether voting rediscovers
them. Measuring a graph method against graph-produced names would be
self-agreement, not a measurement.

    python re/cod4x_vote.py                       # propose, using all names
    python re/cod4x_vote.py --crossval [folds]    # MEASURE precision first
    options: --min-votes F --ratio F --max-deg N
"""
import json, os, sys, collections, math, random
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import RE_DIR, load, clean_ref_name, is_named


def opt(flag, default, cast=float):
    if flag in sys.argv:
        return cast(sys.argv[sys.argv.index(flag) + 1])
    return default


MIN_VOTES = opt("--min-votes", 2.0)
RATIO = opt("--ratio", 2.0)
MAX_DEG = opt("--max-deg", 40, int)

_G = {}


def graphs():
    if _G:
        return _G
    tg = {int(k, 16): v for k, v in load("cod4x_funcs.json").items()}
    rg = {int(k, 16): v for k, v in load("cod4_funcs.json").items()}
    t_callees = {ea: set(v[2]) for ea, v in tg.items()}
    t_callers = collections.defaultdict(set)
    for ea, cs in t_callees.items():
        for c in cs:
            t_callers[c].add(ea)
    r_callees = {ea: set(v[2]) for ea, v in rg.items()}
    r_callers = collections.defaultdict(set)
    for ea, cs in r_callees.items():
        for c in cs:
            r_callers[c].add(ea)
    ref_clean = {}
    for ea, v in rg.items():
        nm = clean_ref_name(v[1], ea)
        if nm:
            ref_clean[ea] = nm
    _G.update(tg=tg, rg=rg, t_callees=t_callees, t_callers=t_callers,
              r_callees=r_callees, r_callers=r_callers, ref_clean=ref_clean,
              name_count=collections.Counter(ref_clean.values()))
    return _G


def w(n):
    """A vote from a rare neighbour is worth more than one from a hub."""
    return 1.0 / math.log2(2 + max(0, n - 1))


def vote(M, taken, min_votes=MIN_VOTES, ratio=RATIO, max_deg=MAX_DEG):
    """M: {tgt_ea: ref_ea} seed. taken: names already in use. -> proposals."""
    g = graphs()
    tg, ref_clean, name_count = g["tg"], g["ref_clean"], g["name_count"]
    used_ref = set(M.values())
    proposals, stats = {}, collections.Counter()

    for X in tg:
        if X in M:
            continue
        votes, support = collections.Counter(), 0
        for c in g["t_callees"].get(X, ()):
            if c in M:
                fam = g["r_callers"].get(M[c], set())
                if len(fam) > max_deg:
                    stats["skipped_hub"] += 1
                    continue
                support += 1
                for y in fam:
                    votes[y] += w(len(fam))
        for p in g["t_callers"].get(X, ()):
            if p in M:
                fam = g["r_callees"].get(M[p], set())
                if len(fam) > max_deg:
                    stats["skipped_hub"] += 1
                    continue
                support += 1
                for y in fam:
                    votes[y] += w(len(fam))
        if not votes or support < 2:
            stats["too_little_support"] += 1
            continue
        ranked = [(y, s) for y, s in votes.most_common() if y not in used_ref]
        if not ranked:
            stats["all_candidates_used"] += 1
            continue
        top, tops = ranked[0]
        runner = ranked[1][1] if len(ranked) > 1 else 0.0
        if tops < min_votes:
            stats["below_min_votes"] += 1
            continue
        if runner and tops < runner * ratio:
            stats["no_dominance"] += 1
            continue
        nm = ref_clean.get(top)
        if not nm or name_count[nm] != 1 or nm in taken:
            stats["name_unusable"] += 1
            continue
        proposals[X] = {"name": nm, "ref_ea": top,
                        "evidence": f"weighted neighbour vote {tops:.2f} vs "
                                    f"runner-up {runner:.2f}, from {support} "
                                    f"mapped neighbours"}

    byname = collections.defaultdict(list)
    for t, p in proposals.items():
        byname[p["name"]].append(t)
    for nm, ts in byname.items():
        if len(ts) > 1:
            stats["dropped_name_collision"] += len(ts)
            for t in ts:
                proposals.pop(t, None)
    return proposals, stats


def build_mapping(exclude=()):
    """Mapping from names present and unique on both sides, minus `exclude`."""
    g = graphs()
    ref_by_name = collections.defaultdict(list)
    for ea, nm in g["ref_clean"].items():
        ref_by_name[nm].append(ea)
    ref_uniq = {nm: e[0] for nm, e in ref_by_name.items() if len(e) == 1}
    tgt_by_name = collections.defaultdict(list)
    for ea, v in g["tg"].items():
        if ea in exclude:
            continue
        if is_named(v[1]):
            tgt_by_name[v[1]].append(ea)
    M = {e[0]: ref_uniq[nm] for nm, e in tgt_by_name.items()
         if len(e) == 1 and nm in ref_uniq}
    taken = {v[1] for ea, v in g["tg"].items()
             if is_named(v[1]) and ea not in exclude}
    return M, taken


def string_truth():
    """Functions named from STRING evidence only - independent of the graph."""
    out = {}
    for k, v in load("cod4x_named_dump.json").items():
        cmt = v[2] if len(v) > 2 else ""
        if "string-anchor" in cmt or "string-SET" in cmt or "strset" in cmt:
            out[int(k, 16)] = v[0]
    return out


if __name__ == "__main__":
    if "--crossval" in sys.argv:
        folds = 5
        for a in sys.argv[sys.argv.index("--crossval") + 1:]:
            if a.isdigit():
                folds = int(a); break
        truth = string_truth()
        keys = sorted(truth)
        random.Random(11).shuffle(keys)
        print(f"string-derived ground truth: {len(keys)} functions, "
              f"{folds} folds\n")
        for mv, rt in ((2.0, 2.0), (1.5, 1.5), (1.0, 1.3)):
            rec = ok = bad = 0
            wrong = []
            for i in range(folds):
                hide = set(keys[i::folds])
                M, taken = build_mapping(exclude=hide)
                props, _ = vote(M, taken, mv, rt, MAX_DEG)
                for h in hide:
                    if h in props:
                        rec += 1
                        if props[h]["name"] == truth[h]:
                            ok += 1
                        else:
                            bad += 1
                            if len(wrong) < 8:
                                wrong.append((h, truth[h], props[h]["name"]))
            prec = 100.0 * ok / rec if rec else 0.0
            print(f"min_votes={mv} ratio={rt}: recovered {rec}  correct {ok}  "
                  f"wrong {bad}  PRECISION {prec:.2f}%  "
                  f"(recall {100.0*rec/len(keys):.1f}%)")
            for h, t, p in wrong[:5]:
                print(f"    0x{h:<8x} truth={t!r} voted={p!r}")
        sys.exit(0)

    M, taken = build_mapping()
    print(f"seed mapping: {len(M):,}")
    props, stats = vote(M, taken)
    print(f"MIN_VOTES={MIN_VOTES} RATIO={RATIO} MAX_DEG={MAX_DEG}")
    for k, v in stats.most_common():
        print(f"  {k:24} {v:,}")
    print(f"  PROPOSALS                {len(props):,}")
    json.dump({str(k): v for k, v in props.items()},
              open(os.path.join(RE_DIR, "cod4x_vote_proposals.json"), "w",
                   encoding="utf-8"))
