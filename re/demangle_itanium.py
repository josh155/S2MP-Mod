"""Minimal Itanium (GCC/Clang) demangler - function NAME only, no signature.

The macOS CoD4 build is GCC-compiled C++, so 7,364 of its 9,140 symbols are
Itanium-mangled and carry the real engine names:

    __Z16BG_ClipForWeaponi                      -> BG_ClipForWeapon
    __ZN12CStreamSound22set_sample_ms_positionEi-> CStreamSound::set_sample_ms_position
    __ZL18DynEnt_AllocXModeli                   -> DynEnt_AllocXModel   (L = static)
    __ZL19_cldClipPolyToPlaneP10collData_t      -> _cldClipPolyToPlane

Only the leading name component is decoded; argument types are deliberately
ignored because we want a name, not a prototype. Validated against IDA's own
demangler in re/check_demangle.py.
"""
import re

_STD_SUBST = {
    "St": "std",
    "Sa": "std::allocator",
    "Sb": "std::basic_string",
    "Ss": "std::string",
    "Si": "std::istream",
    "So": "std::ostream",
    "Sd": "std::iostream",
}


def _read_len_name(s, i):
    """<number><identifier> at s[i:] -> (name, next_index) or (None, i)."""
    j = i
    while j < len(s) and s[j].isdigit():
        j += 1
    if j == i:
        return None, i
    n = int(s[i:j])
    if n <= 0 or j + n > len(s):
        return None, i
    return s[j:j + n], j + n


def demangle(sym):
    """Return the qualified function name, or None if not an Itanium symbol."""
    if not sym:
        return None
    s = sym
    # Mach-O prefixes every C symbol with '_', so C++ symbols arrive as '__Z'
    if s.startswith("__Z"):
        s = s[3:]
    elif s.startswith("_Z"):
        s = s[2:]
    else:
        return None

    # <special-name> we do not attempt (vtables, thunks, guards, typeinfo)
    if s[:2] in ("TV", "TT", "TI", "TS", "GV", "Th", "Tc"):
        return None

    if s.startswith("L"):          # internal linkage (static)
        s = s[1:]

    parts = []
    if s.startswith("N"):          # nested name
        i = 1
        # CV / ref qualifiers on the enclosing class
        while i < len(s) and s[i] in "rVKRO":
            i += 1
        while i < len(s) and s[i] != "E":
            if s[i] == "S":        # substitution (std:: etc.) or back-ref
                two = s[i:i + 2]
                if two in _STD_SUBST:
                    parts.append(_STD_SUBST[two])
                    i += 2
                    continue
                m = re.match(r"S[0-9A-Z_]*?_", s[i:])
                if not m:
                    return None
                parts.append("?")
                i += m.end()
                continue
            if s[i] == "I":        # template args - stop, keep what we have
                break
            if s[i] == "C":        # constructor  C1/C2/C3
                parts.append(parts[-1] if parts else "ctor")
                i += 2
                continue
            if s[i] == "D":        # destructor   D0/D1/D2
                parts.append("~" + (parts[-1] if parts else "dtor"))
                i += 2
                continue
            nm, ni = _read_len_name(s, i)
            if nm is None:
                return None
            parts.append(nm)
            i = ni
    else:
        nm, _ = _read_len_name(s, 0)
        if nm is None:
            return None
        parts.append(nm)

    if not parts:
        return None
    return "::".join(parts)


def ida_safe(name):
    """'::' is awkward in an IDA name; the project convention is '__'."""
    if not name:
        return None
    return name.replace("::", "__").replace("~", "dtor_")


if __name__ == "__main__":
    tests = [
        ("__Z16BG_ClipForWeaponi", "BG_ClipForWeapon"),
        ("__ZN12CStreamSound22set_sample_ms_positionEi",
         "CStreamSound::set_sample_ms_position"),
        ("__ZL18DynEnt_AllocXModeli", "DynEnt_AllocXModel"),
        ("__ZL19_cldClipPolyToPlaneP10collData_tPA4_fiS2_RiRA4_Kf",
         "_cldClipPolyToPlane"),
        ("__Z24PlayerCmd_switchToWeapon12scr_entref_t",
         "PlayerCmd_switchToWeapon"),
        ("__ZN10MacDisplay13GlobalToLocalER5Point",
         "MacDisplay::GlobalToLocal"),
        ("__Z10RunLogicOpi13operationEnumP12OperandStack7OperandS2_PKc",
         "RunLogicOp"),
        ("_atoi", None),
        ("-[ASIHTTPRequest foo]", None),
    ]
    bad = 0
    for sym, want in tests:
        got = demangle(sym)
        ok = got == want
        bad += not ok
        print(f"{'ok ' if ok else 'BAD'} {sym[:52]:52} -> {got!r}")
    print("failures:", bad)
