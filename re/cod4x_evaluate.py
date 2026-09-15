"""Generic scorer for ANY new naming method on CoD4X.

We now hold a large corroborated set: 438 functions where a string anchor and
independent call-graph propagation agreed. That is ground truth good enough to
MEASURE a new method before trusting it.

Given a proposals file {tgt_ea: {"name": ...}}, this reports:

    OVERLAP   proposals landing on a function that already has a name
      agree   ...and the name matches            -> the method is right there
      differ  ...and it does not                 -> the method's error rate
    NEW       proposals for currently-unnamed functions -> the method's yield

precision = agree / (agree + differ) on the overlap. A method that reproduces
hundreds of known names is trustworthy for its novel ones; a method that cannot
be evaluated on any overlap is NOT applied.

    python re/cod4x_evaluate.py cod4x_strset_proposals.json [--examples]
"""
import json, os, sys, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cod4x_common import load, is_named

SHOW = "--examples" in sys.argv
# Restrict ground truth to names derived from a given evidence marker. Needed to
# avoid CIRCULAR validation: measuring a graph method against names that graph
# propagation itself produced would be self-agreement, not a measurement.
TRUTH = None
for _a in sys.argv[1:]:
    if _a.startswith("--truth="):
        TRUTH = _a.split("=", 1)[1]
files = [a for a in sys.argv[1:] if not a.startswith("--")]


def current_names(truth=None):
    """Live names, preferring the freshest source available.

    truth: if given, keep ONLY functions whose basis comment matches this regex,
    so a method can be measured against independent evidence.
    """
    if truth:
        import re as _re
        pat = _re.compile(truth, _re.I)
        out = {}
        try:
            for k, v in load("cod4x_named_dump.json").items():
                if len(v) > 2 and pat.search(v[2] or ""):
                    out[int(k, 16)] = v[0]
        except Exception:
            pass
        return out
    cur = {}
    try:
        for k, v in load("cod4x_funcs.json").items():
            cur[int(k, 16)] = v[1]
    except Exception:
        pass
    try:
        for k, v in load("cod4x_named_dump.json").items():
            cur[int(k, 16)] = v[0]
    except Exception:
        pass
    return cur


def evaluate(path, cur, show=False):
    props = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                        path), encoding="utf-8"))
    agree = differ = new = 0
    diffs, news = [], []
    for k, v in props.items():
        ea = int(k) if not str(k).startswith("0x") else int(k, 16)
        nm = v["name"] if isinstance(v, dict) else v
        existing = cur.get(ea, "")
        if is_named(existing):
            if existing == nm:
                agree += 1
            else:
                differ += 1
                diffs.append((ea, nm, existing))
        else:
            new += 1
            news.append((ea, nm, v.get("evidence", "") if isinstance(v, dict) else ""))
    tot = agree + differ
    prec = 100.0 * agree / tot if tot else 0.0
    print(f"===== {path} =====")
    print(f"  proposals            : {len(props):,}")
    print(f"  overlap with known   : {tot:,}   agree {agree:,}  differ {differ:,}")
    print(f"  MEASURED PRECISION   : {prec:.2f}%" if tot else
          "  MEASURED PRECISION   : n/a - NO OVERLAP, do not apply")
    print(f"  NEW names offered    : {new:,}")
    if show:
        print("  disagreements (method name vs established name):")
        for ea, nm, ex in diffs[:15]:
            print(f"     0x{ea:<8x} method={nm[:34]:34} established={ex[:34]}")
        print("  sample of NEW:")
        for ea, nm, ev in news[:20]:
            print(f"     0x{ea:<8x} {nm[:44]:44} {str(ev)[:40]}")
    return {"precision": prec, "overlap": tot, "agree": agree, "differ": differ,
            "new": new}


if __name__ == "__main__":
    cur = current_names(TRUTH)
    if TRUTH:
        print(f"ground truth RESTRICTED to comments matching {TRUTH!r}")
    print(f"known names available as ground truth: "
          f"{sum(1 for v in cur.values() if is_named(v)):,}\n")
    for f in files:
        evaluate(f, cur, SHOW)
        print()
