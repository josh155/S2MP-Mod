"""Generic mutual-best feature-set matcher, shared by the feature methods.

Given two {entity: set(features)} maps, propose pairs. A pair (R, T) is accepted
only when:

    * they share at least MIN_SHARED features
    * overlap score >= MIN_SCORE, where score = shared / min(|R|, |T|)
    * the pair is MUTUALLY BEST - R's best T is T and T's best R is R
    * each side clears MARGIN over its own runner-up

Mutual-best plus a margin is what stops one big feature-rich function absorbing
every small function it happens to share a feature with. Features owned by very
many entities are dropped first, because they carry no signal.

This is the reusable core behind the string-set and constant-set methods.
"""
import collections


def match(ref_feats, tgt_feats, min_shared=2, min_score=0.4, margin=1.0,
          max_owners=8):
    """ref_feats/tgt_feats: {ea: set(features)} -> ({tgt: (ref, n, score)}, stats)"""
    stats = collections.Counter()

    # feature -> owners, so we can skip ubiquitous features and drive the join
    r_by_f = collections.defaultdict(list)
    for ea, fs in ref_feats.items():
        for f in fs:
            r_by_f[f].append(ea)
    t_by_f = collections.defaultdict(list)
    for ea, fs in tgt_feats.items():
        for f in fs:
            t_by_f[f].append(ea)

    shared = collections.defaultdict(collections.Counter)
    for f, rs in r_by_f.items():
        ts = t_by_f.get(f)
        if not ts:
            continue
        if len(rs) > max_owners or len(ts) > max_owners:
            stats["feature_too_common"] += 1
            continue
        for r in rs:
            for t in ts:
                shared[r][t] += 1

    def score(r, t, n):
        return n / (min(len(ref_feats[r]), len(tgt_feats[t])) or 1)

    # best target per reference
    best_t = {}
    for r, cnt in shared.items():
        ranked = sorted(((t, n, score(r, t, n)) for t, n in cnt.items()),
                        key=lambda x: (-x[2], -x[1]))
        if ranked:
            runner = ranked[1][2] if len(ranked) > 1 else 0.0
            best_t[r] = (ranked[0][0], ranked[0][1], ranked[0][2], runner)

    # best reference per target
    best_r = collections.defaultdict(list)
    for r, cnt in shared.items():
        for t, n in cnt.items():
            best_r[t].append((r, score(r, t, n), n))
    for t in best_r:
        best_r[t].sort(key=lambda x: (-x[1], -x[2]))

    out = {}
    for r, (t, n, sc, runner) in best_t.items():
        stats["candidate_pairs"] += 1
        if n < min_shared:
            stats["too_few_shared"] += 1; continue
        if sc < min_score:
            stats["score_too_low"] += 1; continue
        if runner and sc < runner * margin:
            stats["no_margin_ref_side"] += 1; continue
        tr = best_r[t]
        if tr[0][0] != r:
            stats["not_mutual_best"] += 1; continue
        if len(tr) > 1 and tr[1][1] and tr[0][1] < tr[1][1] * margin:
            stats["no_margin_tgt_side"] += 1; continue
        out[t] = (r, n, sc)
    return out, stats
