#include "pch.h"
#include "aimassist.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"
#include "game.h"

namespace aimassist
{
	namespace
	{
		// RULE A1 -- the arithmetic written out, not done in the head.
		//   aim assist state   unk_5C388F0 - 0x1000 = 0x5C378F0
		//   profile block      unk_8BDEF20 - 0x1000 = 0x8BDDF20
		//   local client -> controller index   sub_4A0B80 - 0x1000 = 0x49FB80
		constexpr std::uintptr_t ADDR_AA_STATE = 0x5C378F0;
		constexpr std::uintptr_t ADDR_PROFILE = 0x8BDDF20;
		constexpr std::uintptr_t ADDR_CONTROLLER_INDEX = 0x49FB80;

		constexpr std::size_t AA_STRIDE = 4912;
		constexpr std::size_t AA_ENABLED = 240;      // the byte sub_78AC0 gates on
		constexpr std::size_t AA_BLOCK = 0x1330;     // what AimAssist_Init memsets

		constexpr std::size_t PROFILE_STRIDE = 6920;
		constexpr std::size_t PROF_SENS_H = 4;
		constexpr std::size_t PROF_SENS_V = 8;
		constexpr std::size_t PROF_ADS_SEPARATE = 12;
		constexpr std::size_t PROF_ADS_H = 16;
		constexpr std::size_t PROF_ADS_V = 20;
		constexpr std::size_t PROF_INVERT_Y = 119;
		constexpr std::size_t PROF_GAMEPAD = 264;    // the gate in sub_78AC0

		using ControllerIndex_t = std::uint32_t(__fastcall*)(std::uint32_t);

		// RULE A6 -- a global belonging to an idle subsystem holds junk, not zero.
		[[nodiscard]] bool readable(const void* p, const std::size_t n)
		{
			if (!p || n == 0)
			{
				return false;
			}
			MEMORY_BASIC_INFORMATION mbi{};
			if (VirtualQuery(p, &mbi, sizeof(mbi)) == 0 || mbi.State != MEM_COMMIT)
			{
				return false;
			}
			if ((mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) != 0)
			{
				return false;
			}
			const auto a = reinterpret_cast<std::uintptr_t>(p);
			const auto end = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
			return a + n <= end;
		}

		[[nodiscard]] char* state_block()
		{
			auto* p = reinterpret_cast<char*>(_b(ADDR_AA_STATE));   // local client 0
			return readable(p, AA_BLOCK) ? p : nullptr;
		}

		[[nodiscard]] char* profile_block(int& controller_out)
		{
			const auto get_idx = reinterpret_cast<ControllerIndex_t>(_b(ADDR_CONTROLLER_INDEX));
			const auto idx = get_idx(0);
			if (idx > 7)
			{
				return nullptr;
			}
			controller_out = static_cast<int>(idx);
			auto* p = reinterpret_cast<char*>(_b(ADDR_PROFILE)) + PROFILE_STRIDE * idx;
			return readable(p, PROF_GAMEPAD + 1) ? p : nullptr;
		}
	}

	// -----------------------------------------------------------------------
	state_t read()
	{
		state_t s{};
		int controller = 0;
		char* prof = profile_block(controller);
		char* st = state_block();
		if (!prof || !st)
		{
			s.readable = false;
			return s;
		}
		s.readable = true;
		s.controller = controller;
		s.gamepad = prof[PROFILE_STRIDE * 0 + PROF_GAMEPAD] != 0;
		s.enabled = st[AA_ENABLED] != 0;
		s.sens_h = *reinterpret_cast<const float*>(prof + PROF_SENS_H);
		s.sens_v = *reinterpret_cast<const float*>(prof + PROF_SENS_V);
		s.ads_separate = prof[PROF_ADS_SEPARATE] != 0;
		s.ads_h = *reinterpret_cast<const float*>(prof + PROF_ADS_H);
		s.ads_v = *reinterpret_cast<const float*>(prof + PROF_ADS_V);
		s.invert_y = prof[PROF_INVERT_Y] != 0;
		return s;
	}

	bool rearm()
	{
		char* st = state_block();
		if (!st)
		{
			return false;
		}
		st[AA_ENABLED] = 1;
		return true;
	}

	// -----------------------------------------------------------------------
	void init()
	{
		dev_mode::add_command("aimassist", []()
		{
			const auto s = read();
			if (!s.readable)
			{
				Console::printf("[aim] state not readable yet - run this in a match.");
				return;
			}

			Console::printf("[aim] controller slot %d", s.controller);
			Console::printf("[aim]   aim assist ENABLED flag (state[240]) : %s",
				s.enabled ? "1  ON" : "0  OFF");
			Console::printf("[aim]   gamepad path      (profile[264])     : %s",
				s.gamepad ? "1  a controller is driving look" : "0  keyboard/mouse");
			Console::printf("[aim]   look sensitivity  %.2f h / %.2f v", s.sens_h, s.sens_v);
			Console::printf("[aim]   separate ADS sens %s (%.2f h / %.2f v)",
				s.ads_separate ? "yes" : "no", s.ads_h, s.ads_v);
			Console::printf("[aim]   invert Y          %s", s.invert_y ? "yes" : "no");

			// The verdict, spelled out, because the whole point is to settle a
			// question rather than dump bytes.
			if (s.enabled && s.gamepad)
			{
				Console::printf("[aim] => AIM ASSIST IS ACTIVE. Both gates are open.");
			}
			else if (s.enabled && !s.gamepad)
			{
				Console::printf("[aim] => Aim assist is armed but the gamepad path is NOT "
					"running. Connect a controller and move the right stick, then run this "
					"again - profile[264] gates stick look itself, not just aim assist.");
			}
			else
			{
				Console::printf("[aim] => state[240] is 0, which is unexpected: the engine "
					"sets it at every cgame init and nothing in the binary clears it. "
					"`aimassist_rearm` puts it back.");
			}
		});

		dev_mode::add_command("aimassist_rearm", []()
		{
			if (!rearm())
			{
				Console::printf("[aim] state block not readable - are you in a match?");
				return;
			}
			Console::printf("[aim] state[240] re-asserted to 1. This is the same value "
				"sub_2D0F0 writes at cgame init, so nothing is fabricated. It does NOT "
				"touch the gamepad flag - aim assist still only applies with a controller.");
		});
	}
}
