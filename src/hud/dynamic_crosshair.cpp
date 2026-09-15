#include "pch.h"
#include "dynamic_crosshair.hpp"

#include "Console.hpp"
#include "FuncPointers.h"
#include "GameUtil.hpp"
#include "Hook.hpp"
#include "game.h"

#include "demo/demo_game.hpp"
#include "hud/wii_aim.hpp"

#include <atomic>
#include <cmath>

namespace dynamic_crosshair
{
	namespace
	{
		// RULE A1 -- the arithmetic written out, never done in the head.
		//   CG_CalcCrosshairPosition  IDA 0x3E10A0 - 0x1000 = 0x3E00A0
		constexpr std::uintptr_t ADDR_CALC_CROSSHAIR_POS = 0x3E00A0;

		// Every offset below is read straight out of CG_CalcCrosshairPosition's
		// own decompile, and the refdef block is cross-confirmed by dolly.cpp /
		// world_project.hpp which reached the same numbers independently.
		//
		//   v11 = dir . (cg+1993808, +1993812, +1993816)        forward
		//   *x  = dir . (cg+1993820, +1993824, +1993828) / (tanX*v11) * -320
		//   *y  = dir . (cg+1993832, +1993836, +1993840) / (tanY*v11) * -240
		constexpr std::size_t CG_TAN_HALF_FOV_X = 1993776;
		constexpr std::size_t CG_TAN_HALF_FOV_Y = 1993780;
		constexpr std::size_t CG_VIEW_ORIGIN    = 1993796;   // dolly.cpp agrees
		constexpr std::size_t CG_AXIS_FORWARD   = 1993808;
		constexpr std::size_t CG_AXIS_ROW1      = 1993820;
		constexpr std::size_t CG_AXIS_ROW2      = 1993832;

		// The span we touch, for one readable() probe instead of six.
		constexpr std::size_t CG_BLOCK_LO   = CG_TAN_HALF_FOV_X;
		constexpr std::size_t CG_BLOCK_SIZE = (CG_AXIS_ROW2 + 12) - CG_TAN_HALF_FOV_X;

		// Render-target size, the same two globals dolly.cpp reads. This is the
		// space R_AddCmdDrawStretchPic works in.
		//   IDA 0x1C86268 - 0x1000 = 0x1C85268
		//   IDA 0x1C8626C - 0x1000 = 0x1C8526C
		constexpr std::uintptr_t ADDR_SCREEN_W = 0x1C85268;
		constexpr std::uintptr_t ADDR_SCREEN_H = 0x1C8526C;

		// CG_CalcCrosshairPosition's output is an offset from centre in a 640x480
		// virtual screen (that is what its -320 / -240 constants mean), so the
		// conversion to render-target pixels is a straight scale.
		constexpr float VIRTUAL_W = 640.0f;
		constexpr float VIRTUAL_H = 480.0f;

		// RULE A17 -- transcribed verbatim, not widened. It returns whatever
		// AngleVectors returned (callers ignore it, but we must forward it), and
		// it takes THREE arguments which must all be declared and passed through.
		using CalcCrosshairPos_t = std::int64_t(__fastcall*)(std::int64_t, float*, float*);

		CalcCrosshairPos_t g_orig = nullptr;
		bool g_hook_ok = false;

		std::atomic<bool>  g_enabled{ false };
		std::atomic<float> g_rot_gain{ 6.0f };
		std::atomic<float> g_move_gain{ 0.02f };
		std::atomic<float> g_tau_ms{ 90.0f };
		std::atomic<float> g_max_radius{ 26.0f };

		// Centre dot. These cross a thread boundary -- the stub records on the
		// client thread during the 2D pass, render_dot() consumes on the render
		// thread inside R_EndFrame -- so they are atomic.
		std::atomic<bool>  g_dot_enabled{ false };
		std::atomic<float> g_dot_size{ 3.0f };     // pixels at 1080p, scaled below
		std::atomic<bool>  g_dot_pending{ false };
		std::atomic<float> g_dot_x{ 0.0f };
		std::atomic<float> g_dot_y{ 0.0f };
		int g_dot_ms = 0;

		// Per-frame state. Only ever touched inside the stub, on the client
		// thread, so it needs no synchronisation.
		int   g_last_ms = 0;
		bool  g_have_prev = false;
		float g_prev_row1[3]{};
		float g_prev_row2[3]{};
		float g_prev_origin[3]{};
		float g_sway_x = 0.0f;
		float g_sway_y = 0.0f;
		bool  g_reported = false;

		// RULE A6 -- a pointer into an idle subsystem holds junk, not zero.
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

		[[nodiscard]] float dot3(const float* a, const float* b)
		{
			return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
		}

		void reset_state()
		{
			g_have_prev = false;
			g_sway_x = 0.0f;
			g_sway_y = 0.0f;
		}

		// Update the sway ONCE per frame. CG_CalcCrosshairPosition has five
		// callers and can run several times in a single frame (normal / turret /
		// vehicle reticles), so integrating per call would scale the effect with
		// however many crosshairs happen to be drawn.
		void update(const char* cg)
		{
			// Sys_Milliseconds, NOT cls_realtime: cls_realtime freezes in some
			// capture states, cannot go backwards, and is unaffected by
			// timescale -- all three would break a smoothed effect.
			const int now = demo_game::now_ms();
			if (now == g_last_ms)
			{
				return;                      // same frame, already integrated
			}
			const int dt_i = now - g_last_ms;
			g_last_ms = now;

			// Guard pauses, seeks, alt-tab and the first frame. A huge or
			// negative dt means the clock jumped, not that you turned fast.
			if (dt_i <= 0 || dt_i > 250)
			{
				reset_state();
				return;
			}
			const float dt = static_cast<float>(dt_i);

			const auto* tanx = reinterpret_cast<const float*>(cg + CG_TAN_HALF_FOV_X);
			const auto* tany = reinterpret_cast<const float*>(cg + CG_TAN_HALF_FOV_Y);
			const auto* fwd  = reinterpret_cast<const float*>(cg + CG_AXIS_FORWARD);
			const auto* row1 = reinterpret_cast<const float*>(cg + CG_AXIS_ROW1);
			const auto* row2 = reinterpret_cast<const float*>(cg + CG_AXIS_ROW2);
			const auto* org  = reinterpret_cast<const float*>(cg + CG_VIEW_ORIGIN);

			// A stale-but-mapped cg gives nonsense here; refuse rather than draw
			// a crosshair flung off screen.
			if (!std::isfinite(*tanx) || !std::isfinite(*tany)
				|| *tanx <= 0.0001f || *tany <= 0.0001f
				|| *tanx > 100.0f || *tany > 100.0f
				|| !std::isfinite(fwd[0]) || !std::isfinite(org[0]))
			{
				reset_state();
				return;
			}

			float target_x = 0.0f;
			float target_y = 0.0f;

			if (g_have_prev)
			{
				// --- ROTATION -------------------------------------------------
				// dot(forward_now, row_prev) is, for small angles, the radians
				// rotated toward that axis since the previous frame. Dividing by
				// dt gives a turn RATE, which is bounded by how fast you can
				// actually turn -- so the effect cannot blow up.
				//
				// Converting through (320/tanX) is the engine's own mapping from
				// axis-space to its 640x480 output, so the sway is automatically
				// FOV-correct and in the same units and sign convention as the
				// value we are adding to.
				const float rot1 = dot3(fwd, g_prev_row1) * (1000.0f / dt);
				const float rot2 = dot3(fwd, g_prev_row2) * (1000.0f / dt);
				const float rg = g_rot_gain.load(std::memory_order_relaxed);

				target_x += rot1 * (320.0f / *tanx) * rg * 0.001f;
				target_y += rot2 * (240.0f / *tany) * rg * 0.001f;

				// --- MOVEMENT -------------------------------------------------
				// Camera velocity rather than playerstate velocity: it is right
				// here in the refdef block we already validated, it needs no
				// unproven ps offset, and it behaves correctly in freecam and
				// during demo playback too.
				const float vel[3] = {
					(org[0] - g_prev_origin[0]) * (1000.0f / dt),
					(org[1] - g_prev_origin[1]) * (1000.0f / dt),
					(org[2] - g_prev_origin[2]) * (1000.0f / dt),
				};
				const float mg = g_move_gain.load(std::memory_order_relaxed);
				target_x -= dot3(vel, row1) * (320.0f / *tanx) * mg * 0.001f;
				target_y -= dot3(vel, row2) * (240.0f / *tany) * mg * 0.001f;
			}

			// Exponential smoothing, framerate-independent. tau is the time
			// constant: the sway covers ~63% of the distance to its target every
			// tau milliseconds, and decays back to centre the same way once you
			// stop (target goes to 0 by itself).
			const float tau = g_tau_ms.load(std::memory_order_relaxed);
			const float a = (tau > 1.0f) ? (1.0f - std::exp(-dt / tau)) : 1.0f;
			g_sway_x += (target_x - g_sway_x) * a;
			g_sway_y += (target_y - g_sway_y) * a;

			// Clamp as a RADIUS, not per axis, so a diagonal flick cannot reach
			// 1.41x the limit and the motion stays circular.
			const float maxr = g_max_radius.load(std::memory_order_relaxed);
			const float r = std::sqrt(g_sway_x * g_sway_x + g_sway_y * g_sway_y);
			if (r > maxr && r > 0.0001f)
			{
				const float s = maxr / r;
				g_sway_x *= s;
				g_sway_y *= s;
			}
			if (!std::isfinite(g_sway_x) || !std::isfinite(g_sway_y))
			{
				reset_state();
				return;
			}

			g_prev_row1[0] = row1[0]; g_prev_row1[1] = row1[1]; g_prev_row1[2] = row1[2];
			g_prev_row2[0] = row2[0]; g_prev_row2[1] = row2[1]; g_prev_row2[2] = row2[2];
			g_prev_origin[0] = org[0]; g_prev_origin[1] = org[1]; g_prev_origin[2] = org[2];
			g_have_prev = true;
		}

		std::int64_t __fastcall calc_crosshair_pos_stub(std::int64_t cg, float* x, float* y)
		{
			// Let the engine compute the real position first; we only ever ADD.
			const std::int64_t rc = g_orig ? g_orig(cg, x, y) : 0;

			// Wii pointer aiming moves the engine's crosshair to the reticle. It
			// rides this stub for the same RULE A3.1 reason the dot does. The sway
			// below still adds on top, and the dot captures the final position.
			const bool wii_on = (x && y) && wii_aim::override_crosshair(x, y);

			const bool sway_on = g_enabled.load(std::memory_order_relaxed);
			const bool dot_on = g_dot_enabled.load(std::memory_order_relaxed);
			(void)wii_on;
			if ((!sway_on && !dot_on) || !x || !y)
			{
				return rc;
			}

			if (sway_on)
			{
				// The cg we were HANDED -- never resolved a second way (RULE A21).
				const auto* base = reinterpret_cast<const char*>(cg);
				if (readable(base + CG_BLOCK_LO, CG_BLOCK_SIZE))
				{
					update(base);
					if (std::isfinite(g_sway_x) && std::isfinite(g_sway_y))
					{
						*x += g_sway_x;
						*y += g_sway_y;
					}
				}
			}

			// Capture the FINAL position (engine + our sway) once per frame for
			// the dot. Taking it here rather than recomputing means the dot rides
			// whatever the crosshair actually does, including engine offsets we
			// never modelled. This function runs several times per frame (normal
			// / turret / vehicle reticles), so only the first wins.
			if (dot_on)
			{
				const int now = demo_game::now_ms();
				if (now != g_dot_ms)
				{
					g_dot_ms = now;
					g_dot_x.store(*x, std::memory_order_relaxed);
					g_dot_y.store(*y, std::memory_order_relaxed);
					g_dot_pending.store(true, std::memory_order_release);
				}
			}
			return rc;
		}

		[[nodiscard]] float arg_float(const int index, const float fallback)
		{
			const auto* args = GameUtil::getCmdArgs();
			if (!args || args->argc[args->nesting] <= index)
			{
				return fallback;
			}
			const char* s = args->argv[args->nesting][index];
			if (!s || !*s)
			{
				return fallback;
			}
			char* end = nullptr;
			const float v = std::strtof(s, &end);
			// strtof + end so a typo is rejected rather than silently becoming 0
			// (GameUtil::safeStringToFloat cannot tell "0" from "garbage").
			if (end == s || !std::isfinite(v))
			{
				return fallback;
			}
			return v;
		}

		void report()
		{
			Console::printf("[xhair] dynamic crosshair %s", enabled() ? "ON" : "off");
			Console::printf("[xhair]   hook: %s", g_hook_ok
				? "live" : "FAILED - nothing will change");
			Console::printf("[xhair]   rot %.2f  move %.4f  smoothing %.0f ms  max %.0f px",
				rot_gain(), move_gain(), tau_ms(), max_radius());
			Console::printf("[xhair]   purely cosmetic - it moves the reticle only, "
				"never your aim or what it targets.");
		}
	}

	// -----------------------------------------------------------------------
	void render_dot()
	{
		// exchange(): consume the flag. If the crosshair was not positioned this
		// frame -- menus, scoreboard, dead, spectating a killcam -- nothing set
		// it, so the dot vanishes along with the reticle instead of hanging in
		// the middle of the screen.
		if (!g_dot_pending.exchange(false, std::memory_order_acquire))
		{
			return;
		}
		if (!g_dot_enabled.load(std::memory_order_relaxed)
			|| !Functions::_R_AddCmdDrawStretchPic)
		{
			return;
		}

		const auto* sw = reinterpret_cast<const int*>(_b(ADDR_SCREEN_W));
		const auto* sh = reinterpret_cast<const int*>(_b(ADDR_SCREEN_H));
		if (!readable(sw, 4) || !readable(sh, 4) || *sw <= 0 || *sh <= 0)
		{
			return;
		}
		const float w = static_cast<float>(*sw);
		const float h = static_cast<float>(*sh);

		const float ox = g_dot_x.load(std::memory_order_relaxed);
		const float oy = g_dot_y.load(std::memory_order_relaxed);
		if (!std::isfinite(ox) || !std::isfinite(oy))
		{
			return;
		}

		// 640x480 virtual offset -> render-target pixels, from screen centre.
		const float cx = (w * 0.5f) + ox * (w / VIRTUAL_W);
		const float cy = (h * 0.5f) + oy * (h / VIRTUAL_H);

		// Size is specified at 1080p and scaled, so it looks the same at any
		// resolution rather than shrinking on a 1440p/4K display.
		float size = g_dot_size.load(std::memory_order_relaxed) * (h / 1080.0f);
		if (size < 1.0f) { size = 1.0f; }
		if (size > 64.0f) { size = 64.0f; }

		// Off-screen guard: a wild value must not reach the render command list.
		if (cx < -size || cy < -size || cx > w + size || cy > h + size)
		{
			return;
		}

		float colour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		const float half = size * 0.5f;
		Functions::_R_AddCmdDrawStretchPic(cx - half, cy - half, size, size,
			0.0f, 0.0f, 0.0f, 0.0f, colour, InternalConsole::getMaterialWhite());
	}

	// -----------------------------------------------------------------------
	bool enabled()      { return g_enabled.load(std::memory_order_relaxed); }
	bool dot_enabled()  { return g_dot_enabled.load(std::memory_order_relaxed); }
	float dot_size()    { return g_dot_size.load(std::memory_order_relaxed); }

	void set_dot_enabled(const bool on)
	{
		g_dot_enabled.store(on, std::memory_order_relaxed);
		if (!on)
		{
			g_dot_pending.store(false, std::memory_order_relaxed);
		}
	}

	float rot_gain()    { return g_rot_gain.load(std::memory_order_relaxed); }
	float move_gain()   { return g_move_gain.load(std::memory_order_relaxed); }
	float tau_ms()      { return g_tau_ms.load(std::memory_order_relaxed); }
	float max_radius()  { return g_max_radius.load(std::memory_order_relaxed); }

	void set_enabled(const bool on)
	{
		g_enabled.store(on, std::memory_order_relaxed);
		reset_state();
	}

	// -----------------------------------------------------------------------
	void init()
	{
		// RULE A3 -- not installed until it says so; a null orig alongside "OK"
		// is MH_ERROR_ALREADY_CREATED (RULE A3.1, checked: nothing else in src/
		// references 0x3E10A0 or 0x3E00A0).
		g_hook_ok = Hook::create("dynamic_crosshair:CalcCrosshairPos",
			reinterpret_cast<void*>(_b(ADDR_CALC_CROSSHAIR_POS)),
			&calc_crosshair_pos_stub,
			reinterpret_cast<void**>(&g_orig)) && g_orig != nullptr;

		GameUtil::addCommand("crosshair_sway", []()
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
			report();
		});

		GameUtil::addCommand("crosshair_sway_rot", []()
		{
			g_rot_gain.store(arg_float(1, rot_gain()), std::memory_order_relaxed);
			Console::printf("[xhair] rotation gain %.2f  (0 disables the turn lag)",
				rot_gain());
		});

		GameUtil::addCommand("crosshair_sway_move", []()
		{
			g_move_gain.store(arg_float(1, move_gain()), std::memory_order_relaxed);
			Console::printf("[xhair] movement gain %.4f  (0 disables the strafe/run lean)",
				move_gain());
		});

		GameUtil::addCommand("crosshair_sway_smooth", []()
		{
			g_tau_ms.store(arg_float(1, tau_ms()), std::memory_order_relaxed);
			Console::printf("[xhair] smoothing %.0f ms  (higher = laggier, floatier)",
				tau_ms());
		});

		GameUtil::addCommand("crosshair_sway_max", []()
		{
			g_max_radius.store(arg_float(1, max_radius()), std::memory_order_relaxed);
			Console::printf("[xhair] max radius %.0f  (640x480 virtual units)",
				max_radius());
		});

		GameUtil::addCommand("crosshair_dot", []()
		{
			const auto* args = GameUtil::getCmdArgs();
			if (args && args->argc[args->nesting] > 1)
			{
				set_dot_enabled(GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0);
			}
			else
			{
				set_dot_enabled(!dot_enabled());
			}
			Console::printf("[xhair] centre dot %s  (%.1f px at 1080p). It rides the "
				"crosshair, so it sways with it when crosshair_sway is on.",
				dot_enabled() ? "ON" : "off", dot_size());
			if (dot_enabled() && !g_hook_ok)
			{
				Console::printf("[xhair]   ...but the hook FAILED, so nothing will draw.");
			}
		});

		GameUtil::addCommand("crosshair_dot_size", []()
		{
			g_dot_size.store(arg_float(1, dot_size()), std::memory_order_relaxed);
			Console::printf("[xhair] dot size %.1f px at 1080p (scales with resolution)",
				dot_size());
		});

		Console::printf("[xhair] ready - `crosshair_sway 1`. hook %s",
			g_hook_ok ? "OK" : "FAILED");
	}
}
