#pragma once

// =============================================================================
//  BuildMap -- make one `_b` literal mean the right thing on more than one build
// =============================================================================
//
//  THE PROBLEM. The mod carries ~341 hardcoded addresses of the STEAM build.
//  They are meaningless anywhere else, and today a single game patch would
//  invalidate every one of them at once. That is a live risk even if the
//  Microsoft Store port never happens.
//
//  THE MECHANISM. Every address in the mod goes through exactly one function:
//
//      size_t _b(size_t val) { return base + val; }      // game.cpp
//
//  so a translation table hooked in THERE covers all 341 call sites without
//  touching any of them. `_b` literals stay in Steam form and are translated on
//  the way out.
//
//  WHERE THE TABLE COMES FROM (tools/, all offline):
//      s2_export_idb.py     dumps each IDB's function graph (size, name, callees)
//      s2_match_builds.py   matches the two builds: name + unique-size seed, then
//                           call-graph propagation. HOLDOUT-VALIDATED: hiding half
//                           the shared names and re-deriving them gave 310 correct
//                           and 2 wrong -- 99.36% precision.
//      s2_map_globals.py    data globals, which have no size and no call graph:
//                           take a Steam instruction that references the global,
//                           read the instruction at the SAME offset in the matched
//                           Store twin, and use its operand. Valid because the two
//                           builds share codegen -- 21 of 22 known-good functions
//                           are IDENTICAL in size. Requires >= 2 agreeing sites.
//      s2_emit_buildmap.py  emits BuildMap.Store.inc
//
//  INDEPENDENTLY VERIFIED. The pipeline reproduced g_hostingEnabled -> Store
//  0x106BA28 and Session_CanHostServer -> 0x849380, both of which had been
//  derived by hand months earlier by decompiling the GSC binding table. Neither
//  was fed to the matcher. 8 of 8 addresses with a known reference value matched.
//
//  ⚠ SAFETY. On the Steam build this is a strict no-op -- one predictable branch
//  and then `base + val`, byte for byte what it did before. An address MISSING
//  from the Store table must never fall through to the Steam value, because that
//  would point at arbitrary memory and corrupt it silently. It returns a poison
//  VA instead: canonical, guaranteed unmapped, and carrying the low bits of the
//  Steam offset so a minidump (RULE A13) names which entry was missing.
// =============================================================================

#include <cstddef>
#include <cstdint>
#include <cstring>

// Windows.h comes from the precompiled header. Including it HERE reorders it
// ahead of Arxan.hpp's <ntstatus.h> in some translation units and sets off the
// winnt/ntstatus STATUS_* macro-redefinition warnings (C4005). Every .cpp in
// this project includes pch.h first, so it is already available.

namespace build_map
{
	enum class Build
	{
		Unknown,   // detection failed -- behave exactly as the Steam build did
		Steam,
		Store,     // Microsoft Store / Game Pass (GDK)
	};

	namespace detail
	{
		struct Row
		{
			std::uint32_t steam;
			std::uint32_t store;
		};

		// Steam `_b` -> Store `_b`, sorted by steam. Generated; do not hand-edit.
		inline constexpr Row STORE_MAP[] = {
			#include "BuildMap.Store.inc"
		};

		// RULE A2 applied as build detection: identify the binary by a string
		// whose address is known in BOTH, rather than by a version number or a
		// module size (which a patch changes and a dump reports differently).
		// This is the same string the project already uses to verify a Cheat
		// Engine attachment.
		inline constexpr char SIGNATURE[] = "EXE_ERR_PROCESS_DEMO_FILE_FAILED";
		inline constexpr std::size_t SIG_STEAM = 0xBCE9E0;   // IDA
		inline constexpr std::size_t SIG_STORE = 0xC6D5B0;   // IDA

		// Canonical (< 2^47) and unmapped, so it faults immediately and legibly
		// rather than corrupting whatever the Steam offset happened to land on.
		inline constexpr std::uintptr_t POISON = 0x0000DEAD00000000ULL;

		inline std::size_t g_unmapped = 0;

		inline bool signature_at(const std::uintptr_t va)
		{
			// The module is mapped before our DllMain runs, but a wrong offset
			// must FAIL rather than fault (RULE A6).
			MEMORY_BASIC_INFORMATION mbi{};
			if (VirtualQuery(reinterpret_cast<void*>(va), &mbi, sizeof(mbi)) == 0)
			{
				return false;
			}
			if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) != 0
				|| (mbi.Protect & PAGE_GUARD) != 0)
			{
				return false;
			}
			const auto end = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
			if (va + sizeof(SIGNATURE) > end)
			{
				return false;
			}
			return std::memcmp(reinterpret_cast<const void*>(va), SIGNATURE,
				sizeof(SIGNATURE)) == 0;
		}

		inline Build detect()
		{
			const auto mod = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
			if (mod == 0)
			{
				return Build::Unknown;
			}
			if (signature_at(mod + SIG_STEAM))
			{
				return Build::Steam;
			}
			if (signature_at(mod + SIG_STORE))
			{
				return Build::Store;
			}
			return Build::Unknown;
		}

		inline const Row* find(const std::uint32_t steam_b)
		{
			std::size_t lo = 0;
			std::size_t hi = sizeof(STORE_MAP) / sizeof(STORE_MAP[0]);
			while (lo < hi)
			{
				const std::size_t mid = lo + (hi - lo) / 2;
				if (STORE_MAP[mid].steam < steam_b)
				{
					lo = mid + 1;
				}
				else if (STORE_MAP[mid].steam > steam_b)
				{
					hi = mid;
				}
				else
				{
					return &STORE_MAP[mid];
				}
			}
			return nullptr;
		}
	}

	// Detected once. A magic static is thread-safe and sidesteps the static
	// initialisation order problem that RULE A14 exists for -- nothing here runs
	// before it is first needed.
	[[nodiscard]] inline Build current()
	{
		static const Build b = detail::detect();
		return b;
	}

	[[nodiscard]] inline const char* name()
	{
		switch (current())
		{
		case Build::Steam: return "Steam";
		case Build::Store: return "Microsoft Store";
		default:           return "UNKNOWN (treated as Steam)";
		}
	}

	[[nodiscard]] inline std::size_t mapped_count()
	{
		return sizeof(detail::STORE_MAP) / sizeof(detail::STORE_MAP[0]);
	}

	// How many `_b` lookups have fallen through the Store table. Non-zero means
	// the table needs regenerating -- and every one of those returned poison.
	[[nodiscard]] inline std::size_t unmapped_hits()
	{
		return detail::g_unmapped;
	}

	// THE ONE ENTRY POINT. `base` is the module handle + 0x1000, as game.cpp
	// defines it, and `steam_b` is the literal the caller wrote.
	[[nodiscard]] inline std::size_t resolve(const std::uintptr_t base,
		const std::size_t steam_b)
	{
		if (current() != Build::Store)
		{
			return base + steam_b;      // Steam and Unknown: unchanged behaviour
		}
		if (const auto* row = detail::find(static_cast<std::uint32_t>(steam_b)))
		{
			return base + row->store;
		}
		++detail::g_unmapped;
		return detail::POISON + (steam_b & 0xFFFFFF);
	}
}
