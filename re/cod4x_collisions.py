"""Diagnose the one-name-many-functions collisions from the anchor pass.

A name proposed for 2+ target functions is unusable as-is. The skill allows
keeping one IF its evidence is strictly stronger - this reports whether that is
the case, or whether both must be dropped.
"""
import collections
from cod4x_common import build_votes, load

votes, stats, ref, tgt = build_votes()

byname = collections.defaultdict(list)
for ea, vs in votes.items():
    names = {n for _, n, _, _ in vs}
    if len(names) != 1:
        continue
    byname[names.pop()].append((ea, len(vs), max(v[2] for v in vs)))

coll = {n: v for n, v in byname.items() if len(v) > 1}
print(f"collisions: {len(coll)} names over {sum(len(v) for v in coll.values())} funcs\n")

sep_strict = sep_none = 0
for n, v in sorted(coll.items(), key=lambda kv: -len(kv[1])):
    v = sorted(v, key=lambda t: (-t[1], -t[2]))
    top, rest = v[0], v[1:]
    # strictly stronger = more anchors than every rival AND a strong anchor
    strictly = all(top[1] > r[1] for r in rest) and top[2] >= 2
    sep_strict += strictly
    sep_none += not strictly
    if len(coll) <= 80 or strictly:
        flag = "SEPARABLE" if strictly else "ambiguous"
        print(f"  {flag:10} {n[:40]:40} " +
              " ".join(f"0x{e:x}(n={c},s={s})" for e, c, s in v[:5]))

print(f"\nseparable by strictly-stronger evidence : {sep_strict}")
print(f"genuinely ambiguous, must stay dropped  : {sep_none}")
