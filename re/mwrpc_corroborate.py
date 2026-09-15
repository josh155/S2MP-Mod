"""Cross-validate anchor proposals against CALL-GRAPH structure.

A string anchor says "PC function X is PS4 function Y". That claim is
independently testable: if it is true, X's callees should be the same set of
functions as Y's callees. We do not know PC callee identities yet - but we have
proposals for many of them, so:

    corroboration(X -> Y) = | {proposed names of X's callees} INTER {names of Y's callees} |

Zero shared callee names where both sides HAVE named callees is evidence
against. This uses no string evidence, so it is a genuine second source.
"""
import json, os, collections

RE_DIR = os.path.dirname(os.path.abspath(__file__))
L = lambda n: json.load(open(os.path.join(RE_DIR, n), encoding="utf-8"))

pc = {int(k, 16): v for k, v in L("mwrpc_funcs.json").items()}
ps4 = {int(k, 16): v for k, v in L("mwr_funcs.json").items()}
prop = {int(k): v for k, v in L("mwrpc_proposals.json").items()}

# PS4: name -> ea (drop names worn by 2+ functions; they cannot disambiguate)
ps4_by_name = collections.defaultdict(list)
for ea, (sz, nm, cal) in ps4.items():
    ps4_by_name[nm].append(ea)
ps4_name2ea = {n: e[0] for n, e in ps4_by_name.items() if len(e) == 1}

# PC: reverse edges, for caller-side corroboration
pc_callers = collections.defaultdict(set)
for ea, (sz, nm, cal) in pc.items():
    for c in cal:
        pc_callers[c].add(ea)
ps4_callers = collections.defaultdict(set)
for ea, (sz, nm, cal) in ps4.items():
    for c in cal:
        ps4_callers[c].add(ea)

proposed_name = {ea: p["name"] for ea, p in prop.items()}

rows = []
for ea, p in prop.items():
    y = ps4_name2ea.get(p["name"])
    if y is None:
        rows.append((ea, p, None, 0, 0, 0, 0)); continue

    # callee side
    pc_callee_names = {proposed_name[c] for c in pc[ea][2] if c in proposed_name}
    ps4_callee_names = {ps4[c][1] for c in ps4[y][2] if c in ps4}
    hit_out = len(pc_callee_names & ps4_callee_names)

    # caller side
    pc_caller_names = {proposed_name[c] for c in pc_callers.get(ea, ()) if c in proposed_name}
    ps4_caller_names = {ps4[c][1] for c in ps4_callers.get(y, ()) if c in ps4}
    hit_in = len(pc_caller_names & ps4_caller_names)

    rows.append((ea, p, y, hit_out, len(pc_callee_names), hit_in, len(pc_caller_names)))

# ---- report ------------------------------------------------------------
by_tier = collections.defaultdict(lambda: [0, 0, 0])   # testable, corroborated, contradicted
for ea, p, y, hout, nout, hin, nin in rows:
    t = p["tier"]
    if y is None:
        continue
    testable = (nout > 0 or nin > 0)
    if not testable:
        continue
    by_tier[t][0] += 1
    if hout or hin:
        by_tier[t][1] += 1
    else:
        by_tier[t][2] += 1

print(f"{'tier':16} {'testable':>9} {'corrob':>8} {'contra':>8}  rate")
for t in ("multi", "single_strong", "single_weak"):
    tst, ok, bad = by_tier[t]
    r = f"{100.0*ok/tst:.1f}%" if tst else "-"
    print(f"{t:16} {tst:9,} {ok:8,} {bad:8,}  {r}")

no_ps4 = sum(1 for _, _, y, *_ in rows if y is None)
untestable = sum(1 for ea, p, y, hout, nout, hin, nin in rows
                 if y is not None and nout == 0 and nin == 0)
print(f"\nPS4 name not uniquely resolvable : {no_ps4}")
print(f"no named neighbours yet (untestable): {untestable}")

json.dump([{"pc": ea, "name": p["name"], "tier": p["tier"],
            "n_anchors": p["n_anchors"], "ps4": y,
            "corrob_out": hout, "corrob_in": hin,
            "neighbours": nout + nin, "anchors": p["anchors"]}
           for ea, p, y, hout, nout, hin, nin in rows],
          open(os.path.join(RE_DIR, "mwrpc_corroborated.json"), "w", encoding="utf-8"))

print("\n--- strongest corroborations ---")
best = sorted(rows, key=lambda r: -(r[3] + r[5]))[:12]
for ea, p, y, hout, nout, hin, nin in best:
    print(f"  0x{ea:<8x} {p['name'][:46]:46} callees {hout}/{nout}  callers {hin}/{nin}")
