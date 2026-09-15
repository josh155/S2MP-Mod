"""Shared logic for the CoD4-Mac -> CoD4X naming pass.

Reference: macOS CoD4 (Mach-O, GCC C++, 100% symboled), port 18337.
Target:    CoD4X iw3mp_dump.exe, port 19337.

Same game, DIFFERENT compiler and platform. Consequences that shape everything
here:
  * function SIZE is not evidence and is never used as a filter (measured on the
    MWR pass: a size gate made precision WORSE and cost a third of the recall)
  * reference symbols are Itanium-mangled and must be demangled
  * Objective-C / Cocoa / OpenGL / STL-template code is macOS-only and dropped
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

# ⛔ THE OLD LOOSE-PREFIX BLOCKLIST WAS A BUG AND IS GONE.
# It contained "CG" for CoreGraphics, which also matches CG_* - so it silently
# deleted the ENTIRE cgame subsystem: 47 functions (CG_Init, CG_Draw2D,
# CG_PredictPlayerState, CG_EntityEvent, CG_RegisterWeapon, ...) across 784
# wasted anchors. "Str" likewise killed StringTable_Lookup and String_Parse.
# Measured by re/cod4x_filtercost.py.
#
# Replaced by two mechanisms that do not guess from a name prefix:
#
#  1. SEGMENT EVIDENCE. macOS system APIs are Mach-O IMPORT STUBS: _atoi,
#     _glFogi and _CFArrayGetTypeID all live in __symbol_stub (737 of them),
#     while real engine bodies (Sys_Init, FS_FileSeek, and statically-linked ODE
#     like dMessage) live in __text (8,402). Rejecting stubs is checkable.
#  2. APPLE-FRAMEWORK NAMING. Apple frameworks are CamelCase after a 2-4 letter
#     prefix (CGColorRelease, NSRectFill, IOObjectRelease), so the pattern is
#     `CG[A-Z]` - which does NOT match `CG_`. That distinction is the whole bug.
STUB_SEGMENTS = ("__symbol_stub", "__stub_helper", "__la_symbol_ptr",
                 "__nl_symbol_ptr", "__picsymbol_stub")

APPLE_API = re.compile(
    r"^(?:"
    r"(?:CG|CGL|AGL|EAGL|NS|CF|IO|AU|CA|QT|SC|LS|AX|TEC|MIDI|HID|AT|CV|CT)[A-Z]"
    r"|gl[A-Zu]"
    r"|(?:pthread|sched|mach|vm|kev|dyld|objc|xpc|dispatch)_"
    r"|Gestalt|LMGet|Movie[A-Z]|Snd[A-Z]|FSp[A-Z]|FSRef"
    r"|ASIHTTP|ASIForm|ASINetwork|ASIData|ASIInput|ASIDownload"
    r")")

# ⛔ AND THEN I MADE THE SAME MISTAKE A SECOND TIME.
# `SC[A-Z]` (Apple's SystemConfiguration) also matches SCR_ (screen), so
# SCR_StopCinematic and SCR_UpdateFrame were rejected exactly as CG_ had been.
# The AUDIT caught it, as a phantom-reference finding.
#
# The real discriminator is not the prefix letters, it is the UNDERSCORE: every
# engine subsystem name is `XX_Something` (CG_, SCR_, CL_, SV_, R_, UI_, FS_,
# BG_, SND_, MSG_, NET_, SEH_), and no Apple framework name has an underscore
# that early (CGColorRelease, NSRectFill, IOObjectRelease, SCNetworkCheck).
# So an early underscore EXEMPTS a name from the framework patterns outright.
ENGINE_PREFIX = re.compile(r"^[A-Za-z][A-Za-z0-9]{0,4}_")

_SEGS = None


def _stub_segments():
    global _SEGS
    if _SEGS is None:
        try:
            _SEGS = [(a, b) for n, a, b, _x in load("cod4_segs.json")
                     if n in STUB_SEGMENTS]
        except Exception:
            _SEGS = []
    return _SEGS


def is_import_stub(ea):
    """Is this reference address a Mach-O import stub (an external API)?"""
    if ea is None:
        return False
    return any(a <= ea < b for a, b in _stub_segments())


def distinctive(s):
    """Does an identifier-ish token survive after stripping format specifiers?"""
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
    """Mach-O symbol -> a C name usable in the target, or None to reject.

    Pass `ea` whenever it is known: it enables the segment check, which is the
    only evidence-based half of the filter.
    """
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
    # an early underscore means an engine subsystem prefix, never an Apple API
    if APPLE_API.match(n) and not ENGINE_PREFIX.match(n):
        return None
    return n


def is_named(n):
    return bool(n) and not n.startswith(("sub_", "nullsub_", "j_", "unknown_"))


def build_votes(ref=None, tgt=None):
    """string anchors -> {target_ea: [(anchor, refname, score, ref_ea)]}.

    An anchor counts only when it has exactly ONE owning function on BOTH
    sides (unambiguous both ways) and the reference name survives cleaning.
    """
    ref = ref or load("cod4_strowners.json")
    tgt = tgt or load("cod4x_strowners.json")
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
