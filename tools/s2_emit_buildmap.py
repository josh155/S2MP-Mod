#!/usr/bin/env python3
"""
s2_emit_buildmap.py -- generate src/BuildMap.Store.inc from the matched builds.

WHAT IT EMITS
    One sorted { steam_b, store_b } pair per address the mod ACTUALLY uses, in
    `_b` form (IDA - 0x1000), which is what the mod's own `_b` literal carries.

    Only the mod's addresses, deliberately -- not all 28k function matches. It
    keeps the table auditable, and it means a newly added `_b` literal is
    UNMAPPED on the Store build until this is re-run, which fails loudly instead
    of silently pointing at the wrong place.

THE THREE KINDS OF ADDRESS, each resolved its own way
    function start   the function matcher (99.4% precision on a holdout)
    mid-function     computed: xbox_func_start + (steam_addr - steam_func_start).
                     Valid because the two builds share codegen -- 21 of 22
                     known-good functions are IDENTICAL in size, so offsets line
                     up. NOT routed through the data-operand path; that was a
                     mistake in the first pass, since these are code, not data.
    data global      the operand-vote resolver, >= 2 agreeing referencing sites

USAGE
    python tools/s2_emit_buildmap.py <scratch dir> [--out src/BuildMap.Store.inc]
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
RE_B = re.compile(r"0x([0-9A-Fa-f]+)_b")
RE_A = re.compile(r"ADDR_[A-Z0-9_]+\s*=\s*0x([0-9A-Fa-f]+)")


def mod_addresses() -> dict[int, set[str]]:
    """Every address the mod uses, IDA form -> the files it appears in."""
    out: dict[int, set[str]] = {}
    for p in (ROOT / "src").rglob("*"):
        if p.suffix not in (".cpp", ".hpp", ".h"):
            continue
        rel = str(p.relative_to(ROOT))
        t = p.read_text(encoding="utf-8", errors="replace")
        for m in RE_B.finditer(t):
            out.setdefault(int(m.group(1), 16) + 0x1000, set()).add(rel)
        for m in RE_A.finditer(t):
            out.setdefault(int(m.group(1), 16) + 0x1000, set()).add(rel)
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("scratch")
    ap.add_argument("--out", default=str(ROOT / "src" / "BuildMap.Store.inc"))
    a = ap.parse_args()
    sc = Path(a.scratch)

    fmap = {int(k, 16): int(v, 16) for k, v in json.loads((sc / "build_map.json").read_text()).items()}
    steam = {int(k, 16): v for k, v in json.loads((sc / "steam_funcs.json").read_text()).items()}
    gmap = json.loads((sc / "globals_map.json").read_text())
    resolved = {int(k, 16): int(v, 16) for k, v in gmap["resolved"].items()}
    weak = {int(k, 16): int(v, 16) for k, v in gmap["weak"].items()}

    # Functions the size matcher could not pair, recovered from call sites inside
    # matched callers (tools/s2_resolve_gaps.py).
    gaps: dict[int, int] = {}
    gap_file = sc / "gap_map.json"
    if gap_file.exists():
        g = json.loads(gap_file.read_text())
        gaps = {int(k, 16): int(v, 16) for k, v in g.get("resolved", {}).items()}
        gaps.update({int(k, 16): int(v, 16) for k, v in g.get("weak", {}).items()})
        fmap.update(gaps)

    # HAND-VERIFIED pairs, applied LAST so they beat the matcher. This layer
    # exists because the matcher can be wrong -- see s2_overrides.json.
    overrides: dict[int, int] = {}
    ov_file = ROOT / "tools" / "s2_overrides.json"
    if ov_file.exists():
        for k, v in json.loads(ov_file.read_text()).items():
            if k.startswith("_"):
                continue
            overrides[int(k, 16)] = int(v["xbox"], 16)
        fmap.update(overrides)
        resolved.update(overrides)

    addrs = mod_addresses()
    rows: list[tuple[int, int, str, str]] = []   # steam_ida, store_ida, kind, note
    missing: list[tuple[int, str, str]] = []

    for d in sorted(addrs):
        where = ",".join(sorted(addrs[d]))
        if d in overrides:
            rows.append((d, overrides[d], "hand", "verified by hand, see s2_overrides.json"))
            continue
        if d in steam:                                  # a function START
            if d in fmap:
                kind = "gap" if d in gaps else "fn"
                rows.append((d, fmap[d], kind, steam[d][1]))
            else:
                missing.append((d, "fn", steam[d][1]))
            continue

        # mid-function code? find the owning Steam function.
        owner = None
        for fs, (size, _, _) in steam.items():
            if fs < d < fs + size:
                owner = fs
                break
        if owner is not None:
            if owner in fmap:
                rows.append((d, fmap[owner] + (d - owner), "mid",
                             f"{steam[owner][1]}+0x{d - owner:X}"))
            else:
                missing.append((d, "mid", steam[owner][1]))
            continue

        if d in resolved:
            rows.append((d, resolved[d], "data", ""))
        elif d in weak:
            rows.append((d, weak[d], "data?", "SINGLE SITE - verify before trusting"))
        else:
            missing.append((d, "data", where))

    rows.sort()
    lines = [
        "// GENERATED by tools/s2_emit_buildmap.py -- DO NOT EDIT BY HAND.",
        "//",
        "// Steam `_b` offset -> Microsoft Store `_b` offset. Both are IDA - 0x1000,",
        "// which is what the mod's own `_b` literals carry.",
        "//",
        "// Provenance, so a wrong row can be traced rather than guessed at:",
        "//   fn    matched by the call-graph matcher (99.4% precision on a holdout)",
        "//   gap   recovered from a call site inside an already-matched caller",
        "//   hand  HAND-VERIFIED override -- beats the matcher, evidence in",
        "//         tools/s2_overrides.json",
        "//   mid   computed from the owning function's match + byte offset",
        "//   data  >= 2 referencing sites agreed on the operand",
        "//   data? ONE site only -- treat as unverified",
        f"// {len(rows)} of {len(addrs)} addresses mapped; {len(missing)} still unresolved.",
        "",
    ]
    for s, x, kind, note in rows:
        tail = f"  // {kind:<5} {note}".rstrip()
        lines.append(f"{{ 0x{s - 0x1000:07X}, 0x{x - 0x1000:07X} }},{tail}")
    Path(a.out).write_text("\n".join(lines) + "\n", encoding="utf-8")

    kinds: dict[str, int] = {}
    for _, _, k, _ in rows:
        kinds[k] = kinds.get(k, 0) + 1
    print(f"wrote {a.out}")
    print(f"  mapped     : {len(rows)}  {kinds}")
    print(f"  unresolved : {len(missing)}")
    for d, k, n in missing:
        print(f"      0x{d:<9X} {k:<5} {n}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
