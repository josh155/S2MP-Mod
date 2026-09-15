"""Shared logic for the MW3-Mac -> MW3-Steam naming pass.

Reference: macOS MW3 (Mach-O, GCC/Clang C++, 99.31% symboled), port 14200.
Target:    the new 64-bit Steam client, iw5mp_dumpx64.exe, port 13999.

Same shape as the CoD4-Mac -> CoD4X pass this file is copied from: same game,
different compiler and platform, so:
  * function SIZE is not evidence (cross-compiler; measured harmful on both
    the MWR and CoD4X passes)
  * reference symbols are Itanium-mangled and must be demangled
  * Objective-C / Cocoa / SDL / ASL / OpenGL wrapper code is macOS-only and
    must be dropped by SEGMENT + NAMING-CONVENTION evidence, never by a bare
    prefix guess (a "CG" blocklist entry once deleted the entire cgame
    subsystem in the CoD4 pass - see cod4x_common.py's own history).
"""
import json, os, re, collections, sys

RE_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, RE_DIR)
from demangle_itanium import demangle, ida_safe


def load(name):
    return json.load(open(os.path.join(RE_DIR, name), encoding="utf-8"))


FMT = re.compile(r"%[-+ #0-9.*]*[hlLqjzt]*[diouxXeEfgGaAcspn%]")
NOISE = {"error", "warning", "failed", "invalid", "unknown", "true", "false",
         "none", "null", "yes", "no", "on", "off", "default", "test", "temp",
         "the", "and", "for", "not", "you", "this", "that", "with", "was"}

STUB_SEGMENTS = ("__symbol_stub", "__stub_helper", "__la_symbol_ptr",
                 "__nl_symbol_ptr", "__picsymbol_stub")

# Apple frameworks are CamelCase after a short prefix (CGColorRelease,
# NSRectFill). Engine subsystem names are `XX_Something` with an underscore
# right after a short all-caps/mixed tag (CG_, SCR_, CL_, SV_, BG_...). No
# Apple API name has an underscore that early, so ENGINE_PREFIX exempts a name
# from APPLE_API rather than trying to enumerate every colliding 2-letter tag.
APPLE_API = re.compile(
    r"^(?:"
    r"(?:CG|CGL|AGL|EAGL|NS|CF|IO|AU|CA|QT|SC|LS|AX|TEC|MIDI|HID|AT|CV|CT)[A-Z]"
    r"|gl[A-Zu]"
    r"|(?:pthread|sched|mach|vm|kev|dyld|objc|xpc|dispatch)_"
    r"|Gestalt|LMGet|Movie[A-Z]|Snd[A-Z]|FSp[A-Z]|FSRef"
    r"|ASIHTTP|ASIForm|ASINetwork|ASIData|ASIInput|ASIDownload"
    r")")
ENGINE_PREFIX = re.compile(r"^[A-Za-z][A-Za-z0-9]{0,4}_")

_SEGS = None


def _stub_segments():
    global _SEGS
    if _SEGS is None:
        try:
            _SEGS = [(a, b) for n, a, b, _x in load("mw3_segs.json")
                     if n in STUB_SEGMENTS]
        except Exception:
            _SEGS = []
    return _SEGS


def is_import_stub(ea):
    if ea is None:
        return False
    return any(a <= ea < b for a, b in _stub_segments())


def distinctive(s):
    core = FMT.sub(" ", s)
    toks = re.findall(r"[A-Za-z_][A-Za-z0-9_]{2,}", core)
    toks = [t for t in toks if t.lower() not in NOISE]
    if not toks:
        return 0
    score = 0
    for t in toks:
        if "_" in t or re.search(r"[a-z][A-Z]", t):
            score += 2
        elif len(t) >= 6:
            score += 1
    if len(core.strip()) >= 24:
        score += 1
    return score


def clean_ref_name(n, ea=None):
    """Mach-O symbol -> a C name usable in the target, or None to reject."""
    if not n:
        return None
    if n.startswith(("-[", "+[")) or "[" in n:
        return None                       # Objective-C selector
    if n.startswith(("sub_", "nullsub_", "j_", "unknown_", "loc_")):
        return None
    if is_import_stub(ea):
        return None                       # external API, not engine code

    dm = demangle(n)
    if dm:
        if dm.startswith("std::") or "?" in dm:
            return None
        if dm.split("::")[0] in ("std", "__gnu_cxx", "CCallback", "CCallResult"):
            return None
        n = ida_safe(dm)
    else:
        if n.startswith("__"):
            return None                   # vtable/thunk/typeinfo/runtime
        if n.startswith("_"):
            n = n[1:]                     # Mach-O C-linkage prefix

    if not n or not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", n):
        return None
    if APPLE_API.match(n) and not ENGINE_PREFIX.match(n):
        return None
    return n


def is_named(n):
    return bool(n) and not n.startswith(("sub_", "nullsub_", "j_", "unknown_"))


def build_votes(ref=None, tgt=None):
    """string anchors -> {target_ea: [(anchor, refname, score, ref_ea)]}."""
    ref = ref or load("mw3_strowners.json")
    tgt = tgt or load("mw3steam_strowners.json")
    ref_names = {int(k): v for k, v in ref["names"].items()}
    stats = collections.Counter()
    votes = collections.defaultdict(list)
    for s, ro in ref["owners"].items():
        to = tgt["owners"].get(s)
        if not to:
            stats["absent_in_target"] += 1
            continue
        stats["shared"] += 1
        if len(ro) != 1:
            stats["ambiguous_ref"] += 1
            continue
        if len(to) != 1:
            stats["ambiguous_target"] += 1
            continue
        nm = clean_ref_name(ref_names.get(ro[0], ""), ro[0])
        if not nm:
            stats["ref_name_rejected"] += 1
            continue
        stats["anchor_usable"] += 1
        votes[to[0]].append((s, nm, distinctive(s), ro[0]))
    return votes, stats, ref, tgt
