#include "pch.h"
#include "nametags.hpp"

#include "Console.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"
#include "game.h"

#include <atomic>
#include <intrin.h>

namespace nametags
{
	namespace
	{
		// RULE A1 -- the arithmetic written out, never done in the head.
		//   sub_38F510 "is team gametype"  IDA 0x38F510 - 0x1000 = 0x38E510
		//   sub_5161D0 visibility test     IDA 0x5161D0 - 0x1000 = 0x5151D0
		constexpr std::uintptr_t ADDR_IS_TEAM_GAMETYPE = 0x38E510;
		constexpr std::uintptr_t ADDR_VISIBILITY_TEST = 0x5151D0;

		// ⭐ THE ONE THAT ACTUALLY MATTERS.  sub_52610 IDA 0x52610 - 0x1000 = 0x51610
		//
		// The first build hooked sub_37F00's team gate and measured "gate opened 0
		// time(s)" -- both hooks live, neither ever reached. There are TWO nameplate
		// enumerators and sub_37F00 is the wrong one:
		//
		//   sub_304B0 <- sub_3FA30   per-player, fading, sub_3C9B0(..., 0)  <-- SEEN
		//   sub_37F00 <- sub_E7980   list-driven,        sub_3C9B0(..., 1)
		//
		// sub_3FA30 walks the active player list and asks ONE predicate per player:
		//     v27 = sub_52610(client, entity, visible);
		//     sub_304B0(client, slot, ..., v27);
		//
		// sub_52610 has exactly ONE code caller (sub_3FA30 @0x3fcbd), so hooking it
		// needs no return-address scoping -- nothing else in the engine consults it.
		constexpr std::uintptr_t ADDR_NAMEPLATE_GATE = 0x51610;

		// CG_DrawVisibleNames (sub_37F00) is 1082 bytes = 0x43A.
		//   range = [0x37F00, 0x37F00 + 0x43A) = [0x37F00, 0x3833A)
		// The team-gate call sits at IDA 0x38016, inside that span.
		// These are IDA addresses: _ReturnAddress() minus the module base, no
		// 0x1000 adjustment -- the same convention broadcaster.cpp uses.
		constexpr std::uintptr_t DRAWNAMES_LO = 0x37F00;
		constexpr std::uintptr_t DRAWNAMES_HI = 0x3833A;

		std::atomic<bool> g_enabled{ false };
		std::atomic<bool> g_through_walls{ false };
		std::atomic<std::uint32_t> g_team_opened{ 0 };
		std::atomic<std::uint32_t> g_vis_opened{ 0 };
		std::atomic<std::uint32_t> g_gate_ran{ 0 };
		std::atomic<std::uint32_t> g_gate_said_yes{ 0 };
		std::atomic<std::uint32_t> g_gate_forced{ 0 };

		bool g_hook_team_ok = false;
		bool g_hook_vis_ok = false;
		bool g_hook_gate_ok = false;

		// RULE A17 -- exact return widths. Both return `bool` (AL only).
		//
		// ⛔⛔ AND THE ARGUMENTS MATTER JUST AS MUCH. CRASHED THE GAME 3 TIMES.
		//
		// IDA types sub_5161D0 as `bool()` -- no parameters. That is WRONG. Its
		// whole body is:
		//
		//     sub  rsp, 28h
		//     call sub_5162F0          ; rcx/rdx/r8 passed straight through
		//     comiss xmm0, dword_B3767C
		//     setnb al
		//
		// It never sets up the argument registers, it FORWARDS THE CALLER'S. And
		// sub_5162F0 is `__m128 __fastcall(__int64 a1, float *a2, float *a3)`,
		// whose first act is `sub_517710(a1)`.
		//
		// Declaring the stub with no parameters let the compiler clobber
		// rcx/rdx/r8 before calling the trampoline, so the original ran on garbage
		// and faulted reading an unmapped address -- IDA_0x516332, inside
		// sub_5162F0, exactly where a1 is first dereferenced.
		//
		// Declaring TOO FEW PARAMETERS is as dangerous as the wrong return width:
		// MinHook's trampoline is fine, but nothing preserves the argument
		// registers across our stub. Take the real arguments and forward them.
		using IsTeamGametype_t = bool(__fastcall*)();      // genuinely takes none:
		                                                   // verified in disassembly,
		                                                   // it never reads rcx/rdx/r8
		using VisibilityTest_t = bool(__fastcall*)(std::int64_t, float*, float*);

		// RULE A17 again -- transcribed verbatim from the decompile, not widened:
		//     char __fastcall sub_52610(unsigned int a1, __int64 a2, char a3)
		// It returns `char`, so only AL is defined. a3 is the engine's own
		// "this player is visible" flag, computed by sub_3FA30.
		using NameplateGate_t = char(__fastcall*)(unsigned int, std::int64_t, char);

		IsTeamGametype_t g_is_team_orig = nullptr;
		VisibilityTest_t g_vis_orig = nullptr;
		NameplateGate_t g_gate_orig = nullptr;

		[[nodiscard]] bool from_drawnames(const void* ra)
		{
			const auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
			const auto addr = reinterpret_cast<std::uintptr_t>(ra);
			if (base == 0 || addr < base)
			{
				return false;
			}
			const auto ida = addr - base;
			return ida >= DRAWNAMES_LO && ida < DRAWNAMES_HI;
		}

		bool __fastcall is_team_gametype_stub()
		{
			if (ungate_team(_ReturnAddress()))
			{
				g_team_opened.fetch_add(1, std::memory_order_relaxed);
				return false;          // "not a team game" -> the engine names EVERYONE
			}
			return g_is_team_orig ? g_is_team_orig() : false;
		}

		bool __fastcall visibility_stub(std::int64_t a1, float* a2, float* a3)
		{
			if (ungate_visibility(_ReturnAddress()))
			{
				g_vis_opened.fetch_add(1, std::memory_order_relaxed);
				return true;           // "visible" -> draw through walls
			}
			// Forward the caller's arguments untouched. Getting this wrong is what
			// crashed the game three times -- see the typedef above.
			return g_vis_orig ? g_vis_orig(a1, a2, a3) : false;
		}

		// ⭐ The primary ungate. Ask the engine FIRST, then only ever upgrade a
		// "no" to a "yes" -- never the reverse. Calling the original first is what
		// preserves its own preconditions (both clientinfos valid, the local player
		// not in team 5, the looked-at-player special case in sub_3FA30), so we
		// cannot draw a nameplate for a slot the engine considers invalid.
		char __fastcall nameplate_gate_stub(unsigned int client, std::int64_t entity, char visible)
		{
			const char real = g_gate_orig ? g_gate_orig(client, entity, visible) : 0;
			g_gate_ran.fetch_add(1, std::memory_order_relaxed);
			if (real)
			{
				g_gate_said_yes.fetch_add(1, std::memory_order_relaxed);
				return real;                    // the engine already wants this name
			}
			if (!g_enabled.load(std::memory_order_relaxed))
			{
				return real;
			}
			// `visible` is the engine's OWN visibility flag. Honouring it mirrors
			// sub_52610's existing theater branch exactly:
			//     if (CG_IsTheaterFreeCamera || CG_IsTheaterOrbitCamera)
			//         if (v10 != 5 && a3) return 1;
			// Through-walls ignores it, which is the whole point of that toggle.
			if (!g_through_walls.load(std::memory_order_relaxed) && !visible)
			{
				return real;
			}
			g_gate_forced.fetch_add(1, std::memory_order_relaxed);
			return 1;
		}
	}

	// -----------------------------------------------------------------------
	bool enabled() { return g_enabled.load(std::memory_order_relaxed); }
	bool through_walls() { return g_through_walls.load(std::memory_order_relaxed); }

	void set_enabled(const bool on)
	{
		g_enabled.store(on, std::memory_order_relaxed);
		g_team_opened.store(0, std::memory_order_relaxed);
		g_vis_opened.store(0, std::memory_order_relaxed);
		g_gate_ran.store(0, std::memory_order_relaxed);
		g_gate_said_yes.store(0, std::memory_order_relaxed);
		g_gate_forced.store(0, std::memory_order_relaxed);
	}

	void set_through_walls(const bool on)
	{
		g_through_walls.store(on, std::memory_order_relaxed);
	}

	bool ungate_team(const void* ra)
	{
		return g_enabled.load(std::memory_order_relaxed) && from_drawnames(ra);
	}

	bool ungate_visibility(const void* ra)
	{
		return g_enabled.load(std::memory_order_relaxed)
			&& g_through_walls.load(std::memory_order_relaxed)
			&& from_drawnames(ra);
	}

	// -----------------------------------------------------------------------
	void init()
	{
		// RULE A3 -- a hook is not installed until it SAYS so, and a null `orig`
		// alongside "OK" means MH_ERROR_ALREADY_CREATED (RULE A3.1).
		g_hook_team_ok = Hook::create("nametags:IsTeamGametype",
			reinterpret_cast<void*>(_b(ADDR_IS_TEAM_GAMETYPE)),
			&is_team_gametype_stub,
			reinterpret_cast<void**>(&g_is_team_orig)) && g_is_team_orig != nullptr;

		g_hook_vis_ok = Hook::create("nametags:VisibilityTest",
			reinterpret_cast<void*>(_b(ADDR_VISIBILITY_TEST)),
			&visibility_stub,
			reinterpret_cast<void**>(&g_vis_orig)) && g_vis_orig != nullptr;

		g_hook_gate_ok = Hook::create("nametags:NameplateGate",
			reinterpret_cast<void*>(_b(ADDR_NAMEPLATE_GATE)),
			&nameplate_gate_stub,
			reinterpret_cast<void**>(&g_gate_orig)) && g_gate_orig != nullptr;

		GameUtil::addCommand("names", []()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (args && args->argc[args->nesting] > 1)
			{
				set_enabled(GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0);
			}
			else
			{
				set_enabled(!enabled());
			}
			Console::printf("[names] %s -- the ENGINE's own nameplates, ungated so they "
				"show every player instead of only teammates.", enabled() ? "ON" : "off");
			Console::printf("[names]   nameplate gate : %s   <- the one that matters",
				g_hook_gate_ok ? "live" : "FAILED - nothing will change");
			Console::printf("[names]   through walls  : %s", through_walls() ? "ON" : "off");

			const auto ran = g_gate_ran.load();
			const auto yes = g_gate_said_yes.load();
			const auto forced = g_gate_forced.load();
			Console::printf("[names]   gate ran %u, engine said yes %u, WE forced %u",
				ran, yes, forced);

			// RULE A15 -- a diagnostic must name the cause, not leave a bare 0.
			if (!g_hook_gate_ok)
			{
				Console::printf("[names] => the hook is not installed. Nothing can work.");
			}
			else if (ran == 0)
			{
				Console::printf("[names] => the engine never asked. sub_3FA30 (the nameplate "
					"loop) is not running: you are not in a live match with players, or this "
					"mode uses the other enumerator. Run it in an actual match.");
			}
			else if (forced == 0 && yes > 0)
			{
				Console::printf("[names] => the engine already says yes for every player it "
					"asked about, so names should be visible without us.");
			}
			else if (forced > 0)
			{
				Console::printf("[names] => we upgraded %u decision(s). If names still do not "
					"appear, the block is downstream in sub_304B0's fade timer, not the gate.",
					forced);
			}
			else
			{
				Console::printf("[names] => asked %u times, always no, and we forced none. "
					"Turn on `names_thruwalls` -- the engine's visibility flag is false for "
					"these players.", ran);
			}

			// The other enumerator, kept because it covers a path this one does not.
			Console::printf("[names]   (other enumerator sub_37F00: team gate %s, opened %u; "
				"vis hook %s, opened %u)",
				g_hook_team_ok ? "live" : "FAILED", g_team_opened.load(),
				g_hook_vis_ok ? "live" : "FAILED", g_vis_opened.load());
		});

		GameUtil::addCommand("names_thruwalls", []()
		{
			set_through_walls(!through_walls());
			Console::printf("[names] through walls: %s%s", through_walls() ? "ON" : "off",
				g_hook_vis_ok ? "" : "  (hook FAILED - no effect)");
		});

		Console::printf("[names] ready - `names 1` ungates the engine's own nameplates. "
			"gate hook %s (team %s, vis %s)",
			g_hook_gate_ok ? "OK" : "FAILED",
			g_hook_team_ok ? "OK" : "FAILED", g_hook_vis_ok ? "OK" : "FAILED");
	}
}
