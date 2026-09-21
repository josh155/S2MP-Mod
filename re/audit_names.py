#!/usr/bin/env python3
"""
audit_names.py -- check that every name in the S2 IDB is backed by recorded
evidence, and that nothing contradicts the evidence files.

WHY
    A wrong name is invisible once written: every later decompile shows it and
    every later session builds on it. This project has already lost time to
    exactly that (the `Script_*` prefix on the Lua `Matchmaking` table; two MW3
    names sitting on the wrong functions). Cheap to write, expensive to detect --
    so it needs a detector.

WHAT IT CHECKS
    A  NO RECORDED BASIS   a named function whose comment does not say how we know.
    B  CONTRADICTION       the IDB disagrees with an evidence file in re/.
    C  DUPLICATE NAME      two functions whose names normalise to the same thing.
    D  PHANTOM REFERENCE   a name claiming a reference basis that the reference
                           build does not actually contain.

    A is advisory for names predating the evidence-comment convention; B, C and D
    are hard failures. Exit code is non-zero if any hard failure is found, so this
    can gate a naming pass.

USAGE
    python re/audit_names.py [--port 13337] [--report re/audit_report.json]
                             [--strict]        # make A fail too
"""

from __future__ import annotations

import argparse
import collections
import json
import sys
import urllib.request
from pathlib import Path

RE_DIR = Path(__file__).resolve().parent

# Phrases this project writes when it records a basis. A comment containing any
# of these counts as "the basis is stated"; the audit does not judge its quality.
BASIS_MARKERS = (
    "Basis:", "CANDIDATE", "Behaviour-proven", "behaviour-proven",
    "Twin-proven", "twin-proven", "Self-naming", "self-naming",
    "REVERTED", "CORRECTION", "descriptive", "Evidence:", "PROVEN",
)

DUMP = r'''
def main():
    import idautils, ida_funcs, idc, json
    out = {}
    for fea in idautils.Functions():
        nm = ida_funcs.get_func_name(fea)
        if nm.startswith(("sub_", "nullsub", "j_", "unknown_")):
            continue
        f = ida_funcs.get_func(fea)
        c = idc.get_func_cmt(fea, 0) or idc.get_func_cmt(fea, 1) or ""
        out[hex(fea)] = [nm, f.size() if f else 0, c]
    with open(OUT, "w") as fh:
        json.dump(out, fh)
    return {"named": len(out), "out": OUT}
main()
'''


def rpc(port: int, tool: str, args: dict, timeout: int = 900) -> str:
    body = json.dumps({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
                       "params": {"name": tool, "arguments": args}}).encode()
    req = urllib.request.Request(f"http://127.0.0.1:{port}/mcp", body,
                                 {"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return json.load(r)["result"]["content"][0]["text"]


def demangle_lite(n: str) -> str:
    """Reduce an MSVC-mangled name to its identifier.

    The reference graph exports carry RAW IDA names, and AW's are mangled
    (`?Dvar_GetFloat@@YAMPBUdvar_t@@@Z`), while names applied to S2 are the
    demangled form. Comparing the two without this makes every AW-sourced name
    look like a phantom.
    """
    if n.startswith("??") and len(n) > 3 and n[2].isdigit():
        end = n.find("@@")
        if end > 3:
            parts = [q for q in n[3:end].split("@") if q]
            if parts:
                # ??0Foo@@ is Foo::Foo (ctor), ??1Foo@@ is Foo::~Foo (dtor)
                q = "::".join(reversed(parts))
                return q + "::" + ("~" if n[2] == "1" else "") + parts[0]
    if n.startswith("?"):
        end = n.find("@@")
        if end > 1:
            # MSVC nests INNERMOST-FIRST: ?method@class@ns@@ -> ns::class::method.
            # Splitting without reversing yields 'method@class', which matches
            # nothing and makes every C++ name look like a phantom.
            parts = [p for p in n[1:end].split("@") if p]
            return "::".join(reversed(parts))
    return n


def norm(n: str) -> str:
    return demangle_lite(n).replace("::", "__").rstrip("_").lower()


def load(name: str):
    p = RE_DIR / name
    if not p.exists():
        return None
    try:
        return json.loads(p.read_text())
    except json.JSONDecodeError:
        return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=13337)
    ap.add_argument("--report", default=str(RE_DIR / "audit_report.json"))
    ap.add_argument("--dump", default=str(RE_DIR / "s2_named_dump.json"),
                    help="where to stage the pulled name dump (per-IDB, so a "
                         "CoD4X audit does not clobber the S2 one)")
    ap.add_argument("--evidence", default="s2", choices=("s2", "none"),
                    help="which ADDRESS-KEYED evidence set applies to this IDB. "
                         "The re/*.json claim files are keyed by S2 address, so "
                         "auditing another binary with them compares unrelated "
                         "functions that happen to share an address - use 'none'.")
    ap.add_argument("--strict", action="store_true",
                    help="treat 'no recorded basis' as a hard failure too")
    a = ap.parse_args()

    dump_path = str(a.dump).replace("\\", "/")
    print(f"pulling named functions from port {a.port} ...")
    print("  " + rpc(a.port, "py_eval", {"code": f"OUT = {dump_path!r}\n" + DUMP}))
    idb = json.loads(Path(dump_path).read_text())
    print(f"  {len(idb)} named functions\n")

    findings = collections.defaultdict(list)

    # ---- A. no recorded basis ------------------------------------------------
    for ea, (nm, size, cmt) in idb.items():
        if not any(m in cmt for m in BASIS_MARKERS):
            findings["A_no_basis"].append({"func": ea, "name": nm, "size": size,
                                           "has_comment": bool(cmt.strip())})

    # ---- B. contradiction with the evidence files ---------------------------
    # each entry: (file, addr_key, name_key, label)
    # These files are keyed by S2 ADDRESS. Auditing a different binary with them
    # would compare unrelated functions that merely share an address, so the
    # whole check is skipped unless the evidence set matches the IDB.
    claims: list[tuple[str, str, str]] = []
    if a.evidence != "s2":
        print(f"  (address-keyed S2 evidence skipped: --evidence={a.evidence})")

    bt = load("s2_binding_tables.json")
    if bt:
        for e in bt:
            if e.get("ambiguous"):
                continue
            claims.append((e["func"], e["binding"], "binding-table"))

    for fn in ("prop_mwr.json", "prop_aw.json"):
        rows = load(fn)
        if rows:
            for r in rows:
                claims.append((r["s2_func"], r["name"], f"propagation:{fn}"))

    ma = load("s2_multi_anchor.json")
    if ma:
        for r in ma:
            for src, nm in r.get("sources", {}).items():
                claims.append((r["func"], nm, f"anchor:{src}"))

    if a.evidence != "s2":
        claims = []          # see the note above: these are keyed by S2 address

    for func, claimed, src in claims:
        cur = idb.get(func)
        if not cur:
            continue                       # unnamed in the IDB -> not a contradiction
        actual = cur[0]
        if src == "binding-table":
            # A binding table asserts the LUA-VISIBLE name. It is only a claim about
            # what the FUNCTION should be called for names applied via that route,
            # i.e. Lua_<Lib>_<binding>. The same table's OOB and spawn entries were
            # deliberately named from AW instead (HandleStartMsg, SP_trigger_hurt),
            # and pre-existing names came from other routes entirely -- none of those
            # is a contradiction, so only audit the Lua_ ones.
            if not actual.startswith("Lua_"):
                continue
            if not actual.endswith("_" + "".join(
                    c if (c.isalnum() or c == "_") else "_" for c in claimed)):
                findings["B_contradiction"].append(
                    {"func": func, "idb": actual, "claimed": claimed, "source": src})
        else:
            if norm(actual) != norm(claimed):
                # Two very different situations, and only one is a defect:
                #   the name STATES a basis and still disagrees with that evidence
                #     -> something applied it wrongly. HARD.
                #   the name predates the evidence convention (no basis comment)
                #     -> the evidence merely SUGGESTS a different name. REVIEW,
                #        a human decides; the Contradiction Rule says resolve it,
                #        not that the newer claim automatically wins.
                # HARD only when the name clashes with ITS OWN stated source.
                # A different source offering another valid name is not a defect:
                # `Lua_Broadcaster_FollowNext` (from S2's own binding table) and
                # `LUI_CoD_LuaCall_FollowNext` (AW's symbol) identify the same
                # marshaller by two conventions. Both are correct; we picked one.
                cmt = cur[2]
                own = ("binding-table" if "Lua binding:" in cmt else
                       "anchor" if "string-anchor port" in cmt.lower() else
                       "propagation" if "Call-graph propagation" in cmt else
                       "worker" if "worker propagation" in cmt else None)
                same_source = own is not None and own.split(":")[0] in src
                bucket = "B_contradiction" if same_source else "B_review"
                findings[bucket].append(
                    {"func": func, "idb": actual, "claimed": claimed,
                     "source": src, "size": cur[1]})

    # ---- C. duplicate names --------------------------------------------------
    byname = collections.defaultdict(list)
    for ea, (nm, size, _c) in idb.items():
        byname[norm(nm)].append((ea, nm, size))
    for k, v in byname.items():
        if len(v) > 1:
            exact = len({n for _e, n, _s in v}) == 1
            findings["C_duplicate" if exact else "C_near_duplicate"].append({"normalised": k,
                                            "functions": [{"func": e, "name": n, "size": s}
                                                          for e, n, s in v]})

    # ---- D. phantom reference names -----------------------------------------
    refs = {}
    # CoD4-Mac names are applied in DEMANGLED/cleaned form, so the reference set
    # must be cleaned the same way or every ported name looks like a phantom.
    cg = load("cod4_funcs.json")
    if cg:
        try:
            sys.path.insert(0, str(RE_DIR))
            from cod4x_common import clean_ref_name as _clean
            refs["COD4MAC"] = {norm(_clean(v[1])) for v in cg.values()
                               if _clean(v[1])}
        except Exception as e:
            print(f"  (CoD4-Mac reference not loaded: {e})")
    mw = load("mw3_funcs.json")
    if mw:
        try:
            sys.path.insert(0, str(RE_DIR))
            from mw3_common import clean_ref_name as _mclean
            refs["MW3MAC"] = {norm(_mclean(v[1])) for v in mw.values()
                              if _mclean(v[1])}
        except Exception as e:
            print(f"  (MW3-Mac reference not loaded: {e})")
    for fn, label in (("aw_funcs.json", "AW"), ("mwr_funcs.json", "MWR")):
        g = load(fn)
        if g:
            refs[label] = {norm(v[1]) for v in g.values()
                           if not v[1].startswith(("sub_", "nullsub", "j_", "unknown_"))}
    def claimed_refs(cmt: str) -> set:
        """Which reference a name CLAIMS as its basis.

        Read this from the structured tier marker only. Do NOT substring-match
        'AW' / 'MWR' anywhere in the comment: the explanatory footer names both
        builds ("References: AW = default_mp.pe; MWR = 2-h1_mp.elf"), so a loose
        match fires for every anchor-derived name and the check becomes noise.
        """
        out = set()
        if "AW string-anchor port" in cmt or "AW worker propagation" in cmt:
            out.add("AW")
        if "[both-agree" in cmt:
            out |= {"AW", "MWR"}
        if "[mwr-" in cmt:
            out.add("MWR")
        if "[aw-only" in cmt:
            out.add("AW")
        if "[cod4mac-" in cmt:
            out.add("COD4MAC")
        if "[mw3mac-" in cmt:
            out.add("MW3MAC")
        for tag in ("MWR+AW", "AW+MWR"):
            if tag in cmt:
                out |= {"AW", "MWR"}
        if "gen " in cmt and "Call-graph propagation" in cmt:
            if ", MWR]" in cmt:
                out.add("MWR")
            if ", AW]" in cmt:
                out.add("AW")
        return out

    for ea, (nm, size, cmt) in idb.items():
        for label in claimed_refs(cmt):
            if label in refs and norm(nm) not in refs[label]:
                findings["D_phantom_ref"].append(
                    {"func": ea, "name": nm, "claims": label})

    # ---- report --------------------------------------------------------------
    Path(a.report).write_text(json.dumps(findings, indent=1))

    hard = ("B_contradiction", "C_duplicate", "D_phantom_ref")
    print(f"{'check':<22} {'count':>7}   severity")
    print("-" * 52)
    labels = {"A_no_basis": "no recorded basis", "B_contradiction": "contradicts own source",
              "B_review": "evidence suggests other", "C_duplicate": "duplicate name",
              "C_near_duplicate": "name differs only by case",
              "D_phantom_ref": "phantom reference name"}
    for k in ("A_no_basis", "B_review", "C_near_duplicate", "B_contradiction",
              "C_duplicate", "D_phantom_ref"):
        n = len(findings[k])
        sev = "HARD" if k in hard else ("HARD" if a.strict else "review")
        print(f"{labels[k]:<22} {n:>7}   {sev}")

    for k in ("B_contradiction", "C_duplicate", "D_phantom_ref", "B_review"):
        if findings[k]:
            print(f"\n--- {labels[k]} (first 12) ---")
            for f in findings[k][:12]:
                print("   ", json.dumps(f)[:150])

    if findings["A_no_basis"]:
        big = sorted(findings["A_no_basis"], key=lambda x: -x["size"])[:12]
        print("\n--- no recorded basis, largest first (first 12) ---")
        for f in big:
            print(f"    {f['func']:>9} {f['size']:>7}B  {f['name'][:52]}")

    print(f"\nfull report: {a.report}")

    fails = sum(len(findings[k]) for k in hard)
    if a.strict:
        fails += len(findings["A_no_basis"])
    if fails:
        print(f"\nFAIL: {fails} hard finding(s)")
        return 1
    print("\nPASS: no hard findings")
    return 0


if __name__ == "__main__":
    sys.exit(main())
