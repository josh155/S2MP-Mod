#include "pch.h"
#include "theater_camera.hpp"

#include "demo/demo_game.hpp"
#include "demo/demo_native.hpp"
#include "demo/demo_playback.hpp"

#include "Console.hpp"
#include "DevMode.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"

#include <atomic>
#include <cstdlib>
#include <format>

// =============================================================================
//  THEATER CAMERA — one camera for BOTH demo systems
// =============================================================================
//
// PROBLEM. The engine has a complete theater camera (1st / 3rd / free-fly) and
// it works on NATIVE playback, but it is structurally unreachable in the custom
// theater. Both gate predicates
//
//     CG_IsTheaterFreeCamera  (IDA 0x916D90)   ->  mode == 1   (third person)
//     CG_IsTheaterOrbitCamera (IDA 0x916DE0)   ->  mode == 2   (free fly)
//
// read the mode out of `s_clientDemoPlayback` (qword_10F340A0) + 6297228, and
// that global is NULL whenever the NATIVE demo system is not running — which is
// exactly the custom theater's situation. `demo_camstate` reported it verbatim:
//     PlaybackData=0000000000000000  cameraMode=-1   custom theater playing=1
//
// ⭐ WHY WE HOOK THE PREDICATES INSTEAD OF BUILDING A CAMERA.
// Those two predicates are consulted in *39 distinct engine functions* — the
// view builder (CG_CalcViewValues), prediction (CG_PredictPlayerState), input
// (CL_CreateCmd), CG_DrawActiveFrame, the 2D HUD drawer (sub_E7980), nameplates
// (CG_ShouldDrawPlayerName), vision sets, entity events, server commands.
// The engine ALREADY knows how to behave as a detached theater camera; the
// custom theater simply cannot answer the question. So we answer it.
//
// Writing our own camera into the refdef instead would leave all 39 of those
// sites believing we are still in first person — which is precisely where the
// first-person-only artifacts (2D scope overlay, viewmodel) come from.
//
// ⭐ PROVEN SAFE. Of those 39 functions, only TWO also dereference PlaybackData:
// CL_Demo_HandleAction and sub_91AC80 — both native-demo KEY ACTION helpers,
// neither on the render/predict path. The remaining 37 never touch it.
// The camera movers reached from CG_PredictPlayerState are safe too: every
// PlaybackData read inside CL_Demo_FreeCameraMove (0x913b40, 0x91400e) and
// CL_Demo_FollowCameraMove (0x91361e, 0x9137d8) is NULL-GUARDED
// (`mov rcx, qword_10F340A0 / test rcx, rcx / jz`) and skips only the
// clip-recording extras — the real movement path runs regardless.
// CL_Demo_FreeCameraIntegrate references it not at all.
//
// ⚠ THE ONE THING WE MUST NOT CALL is the engine's own setter
// CL_Demo_SetCameraMode (0x91AB50): it opens with an UNGUARDED
// `*(DWORD*)(qword_10F340A0 + 6297228)` and would fault instantly. We keep our
// own mode for the custom theater and let the engine keep its own for native.
//
// ⚠ NAMING TRAP: the engine's predicate names do not match their behaviour.
// "FreeCamera" is mode 1 and routes to CL_Demo_FollowCameraMove (THIRD PERSON);
// "OrbitCamera" is mode 2 and routes to CL_Demo_FreeCameraMove (the FLY camera).
// The NUMBERS are what matter, and our enum already matches them 0/1/2.
// =============================================================================

namespace theater_camera
{
	namespace
	{
		constexpr int LOCAL_CLIENT = 0;

		// cg byte offsets. Identical to dolly.cpp's (proven in the dolly work) and
		// independently re-confirmed by CL_Demo_SetCameraMode's own seed, which
		// does `cg[588912..914] = cg[498449..451]` — i.e. freecam origin at byte
		// 2355648 from refdef view origin at byte 1993796.
		constexpr std::size_t CG_FREECAM_ORIGIN = 2355648;   // float[3]
		constexpr std::size_t CG_FREECAM_BLOCK = 36;         // origin+angles+velocity
		constexpr std::size_t CG_REFDEF_VIEW_ORIGIN = 1993796; // float[3]
		constexpr std::size_t CG_REFDEF_VIEW_AXIS = 1993808;   // float[3][3]
		constexpr std::size_t CG_VIEW_BLOCK = 1993776;         // covers both, one probe
		constexpr std::size_t CG_VIEW_BLOCK_BYTES = 68;

		// The mover's own kill switch. BOTH CL_Demo_FreeCameraMove (0x913b33) and
		// CL_Demo_FollowCameraMove (0x913611) open with
		//     cmp dword ptr [cg+598Ch], 0
		//     jnz <function epilogue>
		// so a NON-ZERO value here means the camera update returns having done
		// NOTHING — the exact signature of "the camera detaches but will not move".
		// Its meaning is NOT established (it is the base of a small struct whose
		// first dword sub_69B520 treats as a count, and sub_5C1370 ORs seven
		// dwords out of it), so it is MEASURED and reported, never written.
		constexpr std::size_t CG_MOVER_GATE = 0x598C;   // 22924

		std::atomic<int> g_mode{THEATER_CAMERA_FIRST_PERSON};
		std::atomic<bool> g_enabled{true};       // demo_camera 0|1
		std::atomic<bool> g_seed_pending{false};

		// Diagnostics. Relaxed counters on a hot path cost essentially nothing and
		// turn "it does not work" into a named cause (RULE A15).
		std::atomic<std::uint64_t> g_calls{0};        // predicate stub entered
		std::atomic<std::uint64_t> g_overrides{0};    // ...and we answered
		std::atomic<std::uint64_t> g_origin_moves{0}; // freecam origin actually changed
		float g_last_origin[3]{};

		// RULE A17/A23: both predicates are `bool __fastcall(int)`. Verified from
		// their own decompile — one int argument, and only AL is defined.
		using IsTheaterCam_fn = bool(__fastcall*)(int);
		IsTheaterCam_fn CG_IsTheaterFreeCamera_orig = nullptr;
		IsTheaterCam_fn CG_IsTheaterOrbitCamera_orig = nullptr;
		bool g_hooks_ok = false;

		// sub_759070(float* axis, void* outAngles) — AxisToAngles. A genuine
		// two-argument function (rcx -> rbx, rdx -> rdi in its prologue), NOT a
		// forwarder, so the arg list is real. RULE A23.
		using AxisToAngles_fn = void(__fastcall*)(const float*, void*);

		// RULE A6 — `if (!p)` is not enough in this game: a global belonging to an
		// idle subsystem holds junk, not zero.
		[[nodiscard]] bool readable(const void* p, const std::size_t n)
		{
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
			const auto addr = reinterpret_cast<std::uintptr_t>(p);
			return addr + n <= start + mbi.RegionSize;
		}

		// Is the CUSTOM theater the thing driving playback right now? Native
		// playback keeps the engine's own camera, which already works.
		[[nodiscard]] bool custom_theater_owns_camera()
		{
			return g_enabled.load(std::memory_order_relaxed)
				&& demo_playback::is_playing()
				&& !demo_native::native_playing();
		}

		// Entering the free camera without this puts you at the world origin with
		// a stale angle. This is CL_Demo_SetCameraMode's own mode-2 seed,
		// transcribed: origin from the current view, angles from the current view
		// AXIS via AxisToAngles into the usercmd viewangles (clientActive+25900,
		// already named CA_CMD_VIEWANGLES in demo_game.hpp), roll zeroed.
		//
		// Runs on the CLIENT thread — it is called from the predicate stubs, which
		// the engine invokes from cgame. The GUI only sets the pending flag, so no
		// engine memory is written from the Present thread.
		void seed_freecam_from_current_view()
		{
			void* cg = demo_game::cg_globals_for(LOCAL_CLIENT);
			if (!cg)
			{
				return;   // cg not up yet — stay pending, try again next call
			}
			auto* base = static_cast<char*>(cg);

			const auto* view = reinterpret_cast<const float*>(base + CG_VIEW_BLOCK);
			auto* freecam = reinterpret_cast<float*>(base + CG_FREECAM_ORIGIN);
			if (!readable(view, CG_VIEW_BLOCK_BYTES) || !readable(freecam, CG_FREECAM_BLOCK))
			{
				return;
			}

			const auto* view_origin = reinterpret_cast<const float*>(base + CG_REFDEF_VIEW_ORIGIN);
			freecam[0] = view_origin[0];
			freecam[1] = view_origin[1];
			freecam[2] = view_origin[2];

			// OUR ADDITION, not the engine's: zero the velocity. The engine's
			// integrator damps it rather than clearing it, so entering the camera
			// with a stale value drifts on the first frames.
			freecam[6] = 0.0f;
			freecam[7] = 0.0f;
			freecam[8] = 0.0f;

			// Angles live on the usercmd side — CL_Demo_FreeCameraMove derives
			// cg's freecam angles from the usercmd, so seeding cl.viewangles is
			// what actually stops the camera snapping to wherever the mouse is.
			if (void* cl = demo_game::client_active_for(LOCAL_CLIENT))
			{
				auto* ang = reinterpret_cast<float*>(
					static_cast<char*>(cl) + demo_game::CA_CMD_VIEWANGLES);
				if (readable(ang, 12))
				{
					const auto* axis = reinterpret_cast<const float*>(base + CG_REFDEF_VIEW_AXIS);
					reinterpret_cast<AxisToAngles_fn>(_b(0x758070))(axis, ang);
					ang[2] = 0.0f;   // the engine discards the computed roll too
				}
			}

			g_seed_pending.store(false, std::memory_order_relaxed);
			Console::printf("[cam] free camera seeded at (%.0f %.0f %.0f)",
				freecam[0], freecam[1], freecam[2]);
		}

		// Both stubs are on a hot path (~80 calls/frame across the engine), so the
		// not-overriding case is one relaxed load and a tail call to the original.
		[[nodiscard]] bool override_active()
		{
			g_calls.fetch_add(1, std::memory_order_relaxed);
			if (!custom_theater_owns_camera())
			{
				return false;
			}
			if (g_seed_pending.load(std::memory_order_relaxed))
			{
				seed_freecam_from_current_view();
			}
			// Did the engine's mover actually move the camera since last call?
			// This is the one measurement that separates "the mover never runs"
			// from "it runs but gets no input".
			if (g_mode.load(std::memory_order_relaxed) == THEATER_CAMERA_FREECAM)
			{
				if (void* cg = demo_game::cg_globals_for(LOCAL_CLIENT))
				{
					const auto* o = reinterpret_cast<const float*>(
						static_cast<char*>(cg) + CG_FREECAM_ORIGIN);
					if (readable(o, 12))
					{
						if (o[0] != g_last_origin[0] || o[1] != g_last_origin[1]
							|| o[2] != g_last_origin[2])
						{
							g_origin_moves.fetch_add(1, std::memory_order_relaxed);
							g_last_origin[0] = o[0];
							g_last_origin[1] = o[1];
							g_last_origin[2] = o[2];
						}
					}
				}
			}
			g_overrides.fetch_add(1, std::memory_order_relaxed);
			return true;
		}

		bool __fastcall CG_IsTheaterFreeCamera_stub(const int local_client_num)
		{
			if (override_active())
			{
				return g_mode.load(std::memory_order_relaxed) == THEATER_CAMERA_THIRD_PERSON;
			}
			return CG_IsTheaterFreeCamera_orig
				? CG_IsTheaterFreeCamera_orig(local_client_num) : false;
		}

		bool __fastcall CG_IsTheaterOrbitCamera_stub(const int local_client_num)
		{
			if (override_active())
			{
				return g_mode.load(std::memory_order_relaxed) == THEATER_CAMERA_FREECAM;
			}
			return CG_IsTheaterOrbitCamera_orig
				? CG_IsTheaterOrbitCamera_orig(local_client_num) : false;
		}

		[[nodiscard]] const char* mode_name(const int mode)
		{
			switch (mode)
			{
			case THEATER_CAMERA_FIRST_PERSON: return "first person";
			case THEATER_CAMERA_THIRD_PERSON: return "third person";
			case THEATER_CAMERA_FREECAM:      return "free camera";
			default:                          return "unknown";
			}
		}

		// Answers, in one run, every question the "half working" report leaves open:
		// are the stubs firing, are we answering, is the engine's mover gate open,
		// and is the freecam origin actually moving.
		void cmd_demo_camdiag()
		{
			Console::printf("[camdiag] hooks=%s  free_orig=%p  orbit_orig=%p",
				g_hooks_ok ? "OK" : "FAILED",
				reinterpret_cast<void*>(CG_IsTheaterFreeCamera_orig),
				reinterpret_cast<void*>(CG_IsTheaterOrbitCamera_orig));
			Console::printf("[camdiag] gate: enabled=%d  theater_playing=%d  native_playing=%d "
				"-> override %s",
				g_enabled.load(std::memory_order_relaxed) ? 1 : 0,
				demo_playback::is_playing() ? 1 : 0,
				demo_native::native_playing() ? 1 : 0,
				custom_theater_owns_camera() ? "ENGAGED" : "not engaged");
			Console::printf("[camdiag] mode=%d (%s)  stub calls=%llu  answered=%llu  "
				"origin moved=%llu times",
				g_mode.load(std::memory_order_relaxed),
				mode_name(g_mode.load(std::memory_order_relaxed)),
				static_cast<unsigned long long>(g_calls.load(std::memory_order_relaxed)),
				static_cast<unsigned long long>(g_overrides.load(std::memory_order_relaxed)),
				static_cast<unsigned long long>(g_origin_moves.load(std::memory_order_relaxed)));

			void* cg = demo_game::cg_globals_for(LOCAL_CLIENT);
			if (!cg)
			{
				Console::printf("[camdiag] cg NOT resolvable — nothing else can be read");
				return;
			}
			auto* base = static_cast<char*>(cg);

			// THE prime suspect for "detaches but will not move".
			const auto* gate = reinterpret_cast<const std::int32_t*>(base + CG_MOVER_GATE);
			if (readable(gate, 4))
			{
				Console::printf("[camdiag] cg+0x598C = %d  %s", *gate,
					*gate == 0
						? "(0 = OPEN, the movers will run)"
						: "(NON-ZERO = the movers return immediately — THIS is why the "
						  "camera cannot move)");
			}

			const auto* fc = reinterpret_cast<const float*>(base + CG_FREECAM_ORIGIN);
			const auto* vo = reinterpret_cast<const float*>(base + CG_REFDEF_VIEW_ORIGIN);
			if (readable(fc, CG_FREECAM_BLOCK) && readable(vo, 12))
			{
				Console::printf("[camdiag] freecam pos (%.1f %.1f %.1f) ang (%.1f %.1f %.1f) "
					"vel (%.2f %.2f %.2f)",
					fc[0], fc[1], fc[2], fc[3], fc[4], fc[5], fc[6], fc[7], fc[8]);
				Console::printf("[camdiag] refdef view pos (%.1f %.1f %.1f) — %s",
					vo[0], vo[1], vo[2],
					(fc[0] == vo[0] && fc[1] == vo[1] && fc[2] == vo[2])
						? "MATCHES freecam, so the view IS the free camera"
						: "differs from freecam, so the view is NOT following it");
			}
		}

		void cmd_demo_camera()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (args && args->argc[args->nesting] >= 2)
			{
				const char* a = args->argv[args->nesting][1];
				if (a[0] == '0' && a[1] == '\0')
				{
					g_enabled.store(false, std::memory_order_relaxed);
				}
				else if (a[0] == '1' && a[1] == '\0')
				{
					g_enabled.store(true, std::memory_order_relaxed);
				}
				else
				{
					set_mode(static_cast<camera_mode>(std::atoi(a)));
				}
			}
			// Report unconditionally (RULE A15) — including which system owns the
			// camera and whether the hooks are live, so "the buttons do nothing"
			// is diagnosable from this one line.
			const bool native = demo_native::native_playing();
			GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, std::format(
				"echo [cam] {} | owner: {} | hooks {} | override {}",
				mode_name(get_mode()),
				native ? "NATIVE (engine's own)"
				       : (demo_playback::is_playing() ? "custom theater (ours)" : "no demo playing"),
				g_hooks_ok ? "live" : "DEAD",
				g_enabled.load(std::memory_order_relaxed) ? "on" : "off (demo_camera 1)"));
		}
	}

	void init()
	{
		const bool a = Hook::create("CG_IsTheaterFreeCamera",
			reinterpret_cast<void*>(_b(0x915D90)),          // IDA 0x916D90
			reinterpret_cast<void*>(CG_IsTheaterFreeCamera_stub),
			reinterpret_cast<void**>(&CG_IsTheaterFreeCamera_orig));

		const bool b = Hook::create("CG_IsTheaterOrbitCamera",
			reinterpret_cast<void*>(_b(0x915DE0)),          // IDA 0x916DE0
			reinterpret_cast<void*>(CG_IsTheaterOrbitCamera_stub),
			reinterpret_cast<void**>(&CG_IsTheaterOrbitCamera_orig));

		// RULE A3: a hook is not installed until it says so, and a non-null
		// trampoline is the only proof (MinHook fills it on success only).
		g_hooks_ok = a && b && CG_IsTheaterFreeCamera_orig && CG_IsTheaterOrbitCamera_orig;
		Console::printf("[cam] theater camera hooks: %s — 1st/3rd/free now work in the "
			"CUSTOM theater too (demo_camera, demo_cam_1st/3rd/free)",
			g_hooks_ok ? "OK" : "FAILED");

		GameUtil::addCommand("demo_camera", cmd_demo_camera);
		dev_mode::add_command("demo_camdiag", cmd_demo_camdiag);
		GameUtil::addCommand("demo_cam_1st", [] { set_mode(THEATER_CAMERA_FIRST_PERSON); });
		GameUtil::addCommand("demo_cam_3rd", [] { set_mode(THEATER_CAMERA_THIRD_PERSON); });
		GameUtil::addCommand("demo_cam_free", [] { set_mode(THEATER_CAMERA_FREECAM); });
	}

	// The effective camera mode for whichever system is playing. Native keeps the
	// engine's own value (it is authoritative there and its F2 key still drives
	// it); the custom theater uses ours.
	camera_mode get_mode()
	{
		if (demo_native::native_playing())
		{
			const int m = demo_native::camera_mode();
			return (m >= 0 && m <= 2)
				? static_cast<camera_mode>(m) : THEATER_CAMERA_FIRST_PERSON;
		}
		return static_cast<camera_mode>(g_mode.load(std::memory_order_relaxed));
	}

	void set_mode(const camera_mode mode)
	{
		if (mode < THEATER_CAMERA_FIRST_PERSON || mode > THEATER_CAMERA_FREECAM)
		{
			return;
		}
		if (demo_native::native_playing())
		{
			// Native: the engine owns the mode AND does its own seeding. Calling
			// its setter is correct there and is what F2 does.
			demo_native::set_camera_mode(static_cast<int>(mode));
			return;
		}
		const int prev = g_mode.exchange(static_cast<int>(mode), std::memory_order_relaxed);
		if (mode == THEATER_CAMERA_FREECAM && prev != THEATER_CAMERA_FREECAM)
		{
			// Deferred: the actual write happens on the client thread, inside the
			// predicate stub. set_mode() is reachable from the ImGui Present
			// thread and must not touch engine memory itself.
			g_seed_pending.store(true, std::memory_order_relaxed);
		}
	}

	bool available()
	{
		return demo_native::native_playing() || demo_playback::is_playing();
	}

	bool hooks_installed()
	{
		return g_hooks_ok;
	}



}
