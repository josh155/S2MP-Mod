#include "pch.h"
#include "game.h"
#include "BuildMap.hpp"

uintptr_t base = (uintptr_t)GetModuleHandle(NULL) + 0x1000;

// Every hardcoded address in the mod funnels through here, which is why the
// per-build translation lives at this one point rather than at 341 call sites.
// On the Steam build build_map::resolve is `base + val` -- byte for byte what
// this did before, behind one predictable branch. See BuildMap.hpp.
size_t _b(const size_t val) { return build_map::resolve(base, val); }
size_t operator"" _b(const size_t val) { return _b(val); }
