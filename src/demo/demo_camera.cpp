#include "pch.h"
#include "demo/demo_camera.hpp"

#include "Console.hpp"
#include "GameUtil.hpp"
#include "demo/demo_game.hpp"
#include "demo/demo_native.hpp"

#include <algorithm>
#include <cstring>

namespace demo_camera
{
	namespace
	{
		// ---- addresses (RULE A1: the arithmetic is written out) ---------
		//
		//   cg_fov dvar ptr        IDA 0x11111B8 - 0x1000 = 0x11101B8
		//   eye height instr       IDA 0x9137C1  - 0x1000 = 0x9127C1
		//   pull-back instr        IDA 0x913939  - 0x1000 = 0x912939
		//   freecam roll field     cg + 2355668  (angles[2])
		//
		// S2 dvar layout, proven from Dvar_SetBool @0xB1FD0:
		//   dvar+12 = type, dvar+16 = current value.
		//
		// RULE A14: the _b literal is NEVER cached at namespace scope -- `base`
		// is assigned in init(), so a file-scope initialiser would resolve to
		// the bare literal. It is applied inside the accessor below.
		constexpr std::uintptr_t CG_FOV_DVAR_LITERAL = 0x11101B8;
		constexpr std::size_t    CAM_ANGLES_OFF = 2355660;   // pitch, yaw, roll
		constexpr std::size_t    CAM_ROLL_OFF = CAM_ANGLES_OFF + 8;

		constexpr float STOCK_HEIGHT = 35.0f;
		constexpr float STOCK_DISTANCE = 85.0f;

		float g_height_storage = STOCK_HEIGHT;
		float g_distance_storage = STOCK_DISTANCE;
		float* g_height = &g_height_storage;
		float* g_distance = &g_distance_storage;
		bool g_framing_patched = false;

		float g_roll = 0.0f;

		// Resolved inside a function, never at namespace scope (RULE A14).
		// On the Store build this address is not in BuildMap.Store.inc, so _b
		// hands back POISON -- which the readable() check below then declines,
		// leaving FOV reported as unavailable rather than faulting.
		[[nodiscard]] std::uintptr_t CG_FOV_DVAR_LITERAL_b()
		{
			return _b(CG_FOV_DVAR_LITERAL);
		}

		bool readable(const void* p, const std::size_t n)
		{
			// RULE A6: a null check is not enough in this game -- a global
			// belonging to an inactive subsystem can hold arbitrary non-zero
			// junk, and dereferencing it faults.
			if (!p)
			{
				return false;
			}
			MEMORY_BASIC_INFORMATION mbi{};
			if (!VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT)
			{
				return false;
			}
			if (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))
			{
				return false;
			}
			const auto start = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
			const auto end = start + mbi.RegionSize;
			const auto want = reinterpret_cast<std::uintptr_t>(p);
			return want >= start && want + n <= end;
		}

		// -----------------------------------------------------------------
		//  Repoint ONE instruction's rip-relative operand at a float we own.
		// -----------------------------------------------------------------
		// This mirrors demo_native's proven free-camera-speed patch. It is
		// duplicated rather than shared deliberately: that one works, is
		// user-confirmed, and is not worth destabilising for tidiness.
		//
		// It exists because BOTH camera constants are SHARED (dword_B378E8 has
		// 17 xrefs, dword_B2D3A4 has 12), so patching the constant itself would
		// change unrelated engine behaviour. Repointing the instruction touches
		// exactly one call site.
		bool repoint(const char* what, const std::uintptr_t literal,
			const std::uint8_t (&expect)[4], float** slot)
		{
			auto* instr = reinterpret_cast<std::uint8_t*>(literal);
			if (!readable(instr, 8))
			{
				Console::printf("[cam] %s: instruction not readable, left stock", what);
				return false;
			}
			// RULE A4: verify the exact opcode before writing. Arxan puts jumps
			// and thunks all over this image, so "it looks like an instruction"
			// proves nothing.
			if (std::memcmp(instr, expect, sizeof(expect)) != 0)
			{
				Console::printf(
					"[cam] %s: unexpected opcode (%02X %02X %02X %02X), left stock",
					what, instr[0], instr[1], instr[2], instr[3]);
				return false;
			}

			const auto rip = reinterpret_cast<std::uintptr_t>(instr) + 8;
			auto tgt = reinterpret_cast<std::uintptr_t>(*slot);
			std::intptr_t delta = static_cast<std::intptr_t>(tgt)
				- static_cast<std::intptr_t>(rip);

			// Our DLL can load many GB from the game module (measured ~10 GB)
			// and a rip-relative operand only reaches +/-2GB. Allocate a page
			// within reach and keep the float there instead of giving up.
			if (delta > INT32_MAX || delta < INT32_MIN)
			{
				constexpr std::uintptr_t STEP = 0x10000;         // alloc granularity
				constexpr std::uintptr_t REACH = 0x60000000ull;  // well inside 2GB
				float* near_slot = nullptr;
				for (std::uintptr_t off = STEP; off < REACH && !near_slot; off += STEP)
				{
					for (const std::uintptr_t cand : { rip - off, rip + off })
					{
						auto* p = VirtualAlloc(reinterpret_cast<void*>(cand & ~(STEP - 1)),
							sizeof(float), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
						if (p)
						{
							near_slot = static_cast<float*>(p);
							break;
						}
					}
				}
				if (!near_slot)
				{
					Console::printf("[cam] %s: no page within rip range, left stock", what);
					return false;
				}
				*near_slot = **slot;      // carry the current value over
				*slot = near_slot;        // the slider now edits this
				tgt = reinterpret_cast<std::uintptr_t>(near_slot);
				delta = static_cast<std::intptr_t>(tgt) - static_cast<std::intptr_t>(rip);
				if (delta > INT32_MAX || delta < INT32_MIN)
				{
					Console::printf("[cam] %s: still out of range, left stock", what);
					return false;
				}
			}

			DWORD old = 0;
			if (!VirtualProtect(instr, 8, PAGE_EXECUTE_READWRITE, &old))
			{
				Console::printf("[cam] %s: VirtualProtect failed, left stock", what);
				return false;
			}
			const std::int32_t d32 = static_cast<std::int32_t>(delta);
			std::memcpy(instr + 4, &d32, 4);
			VirtualProtect(instr, 8, old, &old);
			FlushInstructionCache(GetCurrentProcess(), instr, 8);
			return true;
		}

		void patch_framing()
		{
			// 0x9137C1  F3 0F 58 05 disp32   addss  xmm0, [rip+d]   (+35.0 eye height)
			// 0x913939  F3 0F 10 0D disp32   movss  xmm1, [rip+d]   (85.0 pull-back)
			static const std::uint8_t addss_xmm0[4] = { 0xF3, 0x0F, 0x58, 0x05 };
			static const std::uint8_t movss_xmm1[4] = { 0xF3, 0x0F, 0x10, 0x0D };

			const bool h = repoint("camera height", 0x9127C1_b, addss_xmm0, &g_height);
			const bool d = repoint("camera distance", 0x912939_b, movss_xmm1, &g_distance);
			g_framing_patched = h && d;

			Console::printf(
				"[cam] third-person framing: %s (height %.0f, distance %.0f)",
				g_framing_patched ? "adjustable" : "stock - one or both patches declined",
				*g_height, *g_distance);
		}

		// ---- commands ---------------------------------------------------

		void cmd_fov()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				const float f = fov();
				if (f < 0.0f)
				{
					Console::printf("fov: unavailable (cg_fov not registered yet)");
				}
				else
				{
					Console::printf("fov: %.0f   (demo_fov <45..160>)", f);
				}
				return;
			}
			set_fov(static_cast<float>(std::atof(args->argv[args->nesting][1])));
		}

		void cmd_third()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!g_framing_patched)
			{
				Console::printf("[cam] third-person framing is not patchable in this build");
				return;
			}
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("third person: distance %.0f  height %.0f"
					"   (demo_thirdperson <distance> [height]; stock 85 35)",
					*g_distance, *g_height);
				return;
			}
			*g_distance = std::clamp(
				static_cast<float>(std::atof(args->argv[args->nesting][1])), 0.0f, 600.0f);
			if (args->argc[args->nesting] >= 3)
			{
				*g_height = std::clamp(
					static_cast<float>(std::atof(args->argv[args->nesting][2])), -100.0f, 200.0f);
			}
			Console::printf("third person: distance %.0f  height %.0f", *g_distance, *g_height);
		}

		void cmd_roll()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] < 2)
			{
				Console::printf("camera roll: %.1f deg   (demo_roll <-180..180>)", g_roll);
				return;
			}
			set_roll(static_cast<float>(std::atof(args->argv[args->nesting][1])));
			Console::printf("camera roll: %.1f deg", g_roll);
		}

		void cmd_screenshot() { screenshot(); }
	}

	// =====================================================================

	bool fov_available()
	{
		return fov() >= 0.0f;
	}

	float fov()
	{
		// off_11111B8 is a POINTER to the dvar; the value sits at dvar+16.
		auto* slot = reinterpret_cast<std::uintptr_t*>(CG_FOV_DVAR_LITERAL_b());
		if (!readable(slot, sizeof(std::uintptr_t)))
		{
			return -1.0f;
		}
		const auto dvar = *slot;
		if (!readable(reinterpret_cast<void*>(dvar), 20))
		{
			return -1.0f;
		}
		const float v = *reinterpret_cast<float*>(dvar + 16);
		// A dvar that has not been registered yet reads as junk, so sanity-check
		// rather than handing the GUI a slider position of 1e38.
		return (v > 1.0f && v < 200.0f) ? v : -1.0f;
	}

	void set_fov(const float degrees)
	{
		const float v = std::clamp(degrees, 45.0f, 160.0f);
		// Through the console, so the engine's own setter runs on the client
		// thread and any change callback fires. Writing dvar+16 directly would
		// skip both.
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, std::format("cg_fov {:.0f}", v));
	}

	bool framing_patched() { return g_framing_patched; }
	float* height() { return g_framing_patched ? g_height : nullptr; }
	float* distance() { return g_framing_patched ? g_distance : nullptr; }

	float roll() { return g_roll; }

	void set_roll(const float degrees)
	{
		g_roll = std::clamp(degrees, -180.0f, 180.0f);
	}

	void apply_after_camera_move()
	{
		if (g_roll == 0.0f)
		{
			return;                       // stock behaviour, touch nothing
		}
		// The engine writes roll here from usercmd angle[2] every frame, so this
		// is an overwrite of a field it owns and refreshes -- not manufactured
		// state that could go stale.
		void* cg = demo_game::cg_globals_for(0);
		if (!cg)
		{
			return;
		}
		auto* roll_field = reinterpret_cast<float*>(
			static_cast<char*>(cg) + CAM_ROLL_OFF);
		if (readable(roll_field, sizeof(float)))
		{
			*roll_field = g_roll;
		}
	}

	void screenshot()
	{
		if (!demo_native::native_playing())
		{
			Console::printf("[cam] screenshot: only available during demo playback");
			return;
		}
		Console::printf("[cam] high-resolution screenshot -- playback will freeze and "
			"the camera will sweep while it captures the tiles.");
		// Action 17 is the engine's own CL_Demo_CaptureScreenshot. transport()
		// calls the ORIGINAL handler, so our key-block on 17 (which stops F3
		// doing this by surprise) does not get in the way of asking for it.
		demo_native::transport(17);
	}

	void init()
	{
		patch_framing();

		GameUtil::addCommand("demo_fov", cmd_fov);
		GameUtil::addCommand("demo_thirdperson", cmd_third);
		GameUtil::addCommand("demo_roll", cmd_roll);
		GameUtil::addCommand("demo_screenshot", cmd_screenshot);
	}
}
