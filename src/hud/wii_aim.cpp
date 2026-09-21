#include "pch.h"
#include "wii_aim.hpp"

#include "Console.hpp"
#include "FuncPointers.h"
#include "GameUtil.hpp"
#include "game.h"

#include "demo/demo_game.hpp"
#include "demo/demo_native.hpp"
#include "demo/demo_playback.hpp"

#include <atomic>
#include <cmath>
#include <cstring>

namespace wii_aim
{
	namespace
	{
		constexpr float PI = 3.14159265358979f;
		constexpr float DEG2RAD = PI / 180.0f;
		constexpr float RAD2DEG = 180.0f / PI;

		// Refdef fields, the SAME offsets dynamic_crosshair / dolly / world_project
		// proved independently (CG_CalcCrosshairPosition decompile).
		constexpr std::size_t CG_TAN_HALF_FOV_X = 1993776;
		constexpr std::size_t CG_TAN_HALF_FOV_Y = 1993780;

		// usercmd angle slots. From the CL_CreateCmd -> sub_74770 decompile note in
		// demo_game.hpp ("packed into usercmd +0x10/+0x14/+0x18 as ANGLE2SHORT").
		// Treated as LIKELY and verified at runtime in after_create_cmd() before
		// anything is written.
		constexpr std::size_t CMD_ANGLE_PITCH = 0x10;
		constexpr std::size_t CMD_ANGLE_YAW = 0x14;

		// Render-target size globals, same as dynamic_crosshair / dolly.
		constexpr std::uintptr_t ADDR_SCREEN_W = 0x1C85268;
		constexpr std::uintptr_t ADDR_SCREEN_H = 0x1C8526C;

		// The engine clamps the predicted pitch; keep the AIM inside this so the
		// camera we derive from it never disagrees with what the engine kept.
		constexpr float PITCH_LIMIT = 85.0f;

		// How many consecutive layout mismatches before we give up on the
		// usercmd slots. One or two can happen legitimately (the engine may pack
		// nothing on a frame with no input change), a run means the note is wrong.
		constexpr int LAYOUT_STRIKES = 8;

		// ---- tunables (console) ----------------------------------------------
		std::atomic<bool>  g_enabled{ false };
		std::atomic<float> g_box_w{ 0.50f };      // half-width of the box, fraction of half-screen
		std::atomic<float> g_box_h{ 0.40f };      // half-height
		std::atomic<float> g_turn_speed{ 180.0f };// deg/s at the screen edge
		std::atomic<float> g_turn_curve{ 1.5f };  // exponent on the excess (1 = linear)
		std::atomic<float> g_ads_scale{ 0.5f };   // box multiplier while ADS
		std::atomic<float> g_ads_threshold{ 0.85f };  // fov ratio below which = ADS
		std::atomic<float> g_scope_threshold{ 0.50f };// fov ratio below which = scoped
		std::atomic<bool>  g_lock_scoped{ true }; // scoped: reticle locks to centre
		std::atomic<bool>  g_draw_reticle{ true };
		std::atomic<bool>  g_draw_box{ false };
		std::atomic<float> g_reticle_size{ 22.0f }; // px at 1080p

		// ---- client-thread state -----------------------------------------------
		bool  g_have_pre = false;
		float g_pre[2]{};          // CA_CMD_VIEWANGLES pitch/yaw before the engine ran
		bool  g_seeded = false;
		float g_cam[2]{};          // camera pitch/yaw, cmd space
		float g_cur_x = 0.0f;      // reticle, -1..1 of half-screen
		float g_cur_y = 0.0f;
		float g_off[2]{};          // aim - camera (pitch, yaw), for the ps subtraction
		bool  g_off_valid = false;
		int   g_last_ms = 0;
		float g_fov_max = 0.0f;    // widest tanHalfFovX seen while active (hip baseline)
		float g_fov_ratio = 1.0f;
		bool  g_ads = false;
		bool  g_scoped = false;
		int   g_layout_strikes = 0;
		bool  g_layout_ok = false;
		bool  g_layout_failed = false;
		int   g_frames = 0;

		// ---- render-thread mirror --------------------------------------------
		std::atomic<bool>  g_draw_pending{ false };
		std::atomic<float> g_draw_x{ 0.0f };
		std::atomic<float> g_draw_y{ 0.0f };
		std::atomic<float> g_draw_bx{ 0.5f };
		std::atomic<float> g_draw_by{ 0.4f };
		std::atomic<bool>  g_draw_locked{ false };

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

		[[nodiscard]] float wrap180(float a)
		{
			a = std::fmod(a + 180.0f, 360.0f);
			if (a < 0.0f)
			{
				a += 360.0f;
			}
			return a - 180.0f;
		}

		[[nodiscard]] float clampf(const float v, const float lo, const float hi)
		{
			return v < lo ? lo : (v > hi ? hi : v);
		}

		void reset_state()
		{
			g_have_pre = false;
			g_seeded = false;
			g_cur_x = 0.0f;
			g_cur_y = 0.0f;
			g_off[0] = 0.0f;
			g_off[1] = 0.0f;
			g_off_valid = false;
			g_last_ms = 0;
			g_fov_max = 0.0f;
			g_fov_ratio = 1.0f;
			g_ads = false;
			g_scoped = false;
			g_draw_pending.store(false, std::memory_order_relaxed);
		}

		// Live play only. Both demo systems own the camera themselves and the
		// theater strips the usercmd we would be writing into.
		[[nodiscard]] bool live_play_active()
		{
			if (!g_enabled.load(std::memory_order_relaxed) || g_layout_failed)
			{
				return false;
			}
			if (demo_game::connstate() < demo_game::CA_ACTIVE)
			{
				return false;
			}
			if (demo_playback::is_playing() || demo_native::native_playing())
			{
				return false;
			}
			return true;
		}

		[[nodiscard]] float* cmd_viewangles(const int local_client_num)
		{
			void* cl = demo_game::client_active_for(local_client_num);
			if (!cl)
			{
				return nullptr;
			}
			auto* ang = reinterpret_cast<float*>(
				static_cast<char*>(cl) + demo_game::CA_CMD_VIEWANGLES);
			return readable(ang, 12) ? ang : nullptr;
		}

		// Reads the refdef tan-half-fov pair. False when cg is not up or stale.
		[[nodiscard]] bool read_fov(const int local_client_num, float& tan_x, float& tan_y)
		{
			void* cg = demo_game::cg_globals_for(local_client_num);
			if (!cg)
			{
				return false;
			}
			const auto* base = static_cast<const char*>(cg);
			const auto* tx = reinterpret_cast<const float*>(base + CG_TAN_HALF_FOV_X);
			const auto* ty = reinterpret_cast<const float*>(base + CG_TAN_HALF_FOV_Y);
			if (!readable(tx, 8))
			{
				return false;
			}
			if (!std::isfinite(*tx) || !std::isfinite(*ty)
				|| *tx <= 0.0001f || *ty <= 0.0001f || *tx > 100.0f || *ty > 100.0f)
			{
				return false;
			}
			tan_x = *tx;
			tan_y = *ty;
			return true;
		}

		// The engine's own AngleVectors with roll = 0. Quake axes: +x forward,
		// +y left, +z up; pitch positive = looking down.
		void angle_vectors(const float pitch, const float yaw,
			float* fwd, float* right, float* up)
		{
			const float sp = std::sin(pitch * DEG2RAD), cp = std::cos(pitch * DEG2RAD);
			const float sy = std::sin(yaw * DEG2RAD), cy = std::cos(yaw * DEG2RAD);
			fwd[0] = cp * cy;  fwd[1] = cp * sy;  fwd[2] = -sp;
			right[0] = sy;     right[1] = -cy;    right[2] = 0.0f;
			up[0] = sp * cy;   up[1] = sp * sy;   up[2] = cp;
		}

		// Aim angles for the ray from the camera through the reticle.
		void aim_from_cursor(const float cam_pitch, const float cam_yaw,
			const float cx, const float cy, const float tan_x, const float tan_y,
			float& aim_pitch, float& aim_yaw)
		{
			float f[3], r[3], u[3];
			angle_vectors(cam_pitch, cam_yaw, f, r, u);
			const float sx = cx * tan_x;
			const float sy = -cy * tan_y;   // screen y is down, world up is up
			const float d[3] = {
				f[0] + r[0] * sx + u[0] * sy,
				f[1] + r[1] * sx + u[1] * sy,
				f[2] + r[2] * sx + u[2] * sy,
			};
			const float flat = std::sqrt(d[0] * d[0] + d[1] * d[1]);
			aim_yaw = std::atan2(d[1], d[0]) * RAD2DEG;
			aim_pitch = -std::atan2(d[2], flat) * RAD2DEG;
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
			if (end == s || !std::isfinite(v))
			{
				return fallback;
			}
			return v;
		}

		[[nodiscard]] bool arg_toggle(std::atomic<bool>& flag)
		{
			const auto* args = GameUtil::getCmdArgs();
			bool v = !flag.load(std::memory_order_relaxed);
			if (args && args->argc[args->nesting] > 1)
			{
				v = GameUtil::safeStringToInt(args->argv[args->nesting][1]) != 0;
			}
			flag.store(v, std::memory_order_relaxed);
			return v;
		}

		void report()
		{
			Console::printf("[wii] pointer aiming %s%s",
				enabled() ? "ON" : "off",
				g_layout_failed ? "  (DISABLED: usercmd layout check failed)" : "");
			Console::printf("[wii]   box %.2f x %.2f   turn %.0f deg/s  curve %.2f",
				g_box_w.load(), g_box_h.load(), g_turn_speed.load(), g_turn_curve.load());
			Console::printf("[wii]   ads box x%.2f (ratio < %.2f)   scoped lock %s (ratio < %.2f)",
				g_ads_scale.load(), g_ads_threshold.load(),
				g_lock_scoped.load() ? "on" : "off", g_scope_threshold.load());
			Console::printf("[wii]   live: cursor (%.2f, %.2f)  cam (%.1f, %.1f)  "
				"off (%.2f, %.2f)  fov ratio %.2f  ads %d scoped %d  layout %s  frames %d",
				g_cur_x, g_cur_y, g_cam[0], g_cam[1], g_off[0], g_off[1],
				g_fov_ratio, g_ads ? 1 : 0, g_scoped ? 1 : 0,
				g_layout_ok ? "verified" : (g_layout_failed ? "FAILED" : "unverified"),
				g_frames);
		}
	}

	// -----------------------------------------------------------------------
	bool enabled() { return g_enabled.load(std::memory_order_relaxed); }

	void set_enabled(const bool on)
	{
		g_enabled.store(on, std::memory_order_relaxed);
		reset_state();
		if (on)
		{
			// A fresh enable is a fresh chance for the layout check.
			g_layout_failed = false;
			g_layout_ok = false;
			g_layout_strikes = 0;
			g_frames = 0;
		}
	}

	// -----------------------------------------------------------------------
	void before_create_cmd(const int local_client_num)
	{
		g_have_pre = false;
		if (!live_play_active())
		{
			return;
		}
		if (const float* ang = cmd_viewangles(local_client_num))
		{
			g_pre[0] = ang[0];
			g_pre[1] = ang[1];
			g_have_pre = true;
		}
	}

	void after_create_cmd(void* cmd, const int local_client_num)
	{
		if (!live_play_active() || !cmd)
		{
			reset_state();
			return;
		}
		float* ang = cmd_viewangles(local_client_num);
		float tan_x = 0.0f, tan_y = 0.0f;
		if (!ang || !g_have_pre || !read_fov(local_client_num, tan_x, tan_y))
		{
			// cg not up yet (map load) -- wait, do not reset the box position.
			g_off_valid = false;
			return;
		}
		if (!readable(cmd, CMD_ANGLE_YAW + 4))
		{
			g_off_valid = false;
			return;
		}

		// ---- runtime proof of the usercmd layout note ------------------------
		// The engine has just packed ITS angles. If the slots hold ANGLE2SHORT of
		// the live CA_CMD_VIEWANGLES, the note is right and we may repack them.
		auto* cmd_pitch = reinterpret_cast<int*>(static_cast<char*>(cmd) + CMD_ANGLE_PITCH);
		auto* cmd_yaw = reinterpret_cast<int*>(static_cast<char*>(cmd) + CMD_ANGLE_YAW);
		if (!g_layout_ok)
		{
			const bool match =
				(*cmd_pitch & 0xFFFF) == demo_game::angle_to_short(ang[0])
				&& (*cmd_yaw & 0xFFFF) == demo_game::angle_to_short(ang[1]);
			if (match)
			{
				g_layout_ok = true;
				g_layout_strikes = 0;
				Console::printf("[wii] usercmd angle layout verified (+0x10 pitch, +0x14 yaw)");
			}
			else if (++g_layout_strikes >= LAYOUT_STRIKES)
			{
				g_layout_failed = true;
				Console::printf("[wii] usercmd angle slots did NOT match ANGLE2SHORT of "
					"CA_CMD_VIEWANGLES for %d frames -- the +0x10/+0x14 note is wrong "
					"for this build. Pointer aiming disabled; nothing was written.",
					LAYOUT_STRIKES);
				reset_state();
				return;
			}
			else
			{
				g_off_valid = false;
				return;
			}
		}

		// ---- mouse delta this frame, in degrees, sensitivity already applied --
		float d_pitch = ang[0] - g_pre[0];
		float d_yaw = wrap180(ang[1] - g_pre[1]);
		if (!g_seeded)
		{
			g_cam[0] = ang[0];
			g_cam[1] = ang[1];
			g_cur_x = 0.0f;
			g_cur_y = 0.0f;
			g_seeded = true;
			d_pitch = 0.0f;
			d_yaw = 0.0f;
		}
		if (!std::isfinite(d_pitch) || !std::isfinite(d_yaw)
			|| std::fabs(d_pitch) > 90.0f || std::fabs(d_yaw) > 180.0f)
		{
			d_pitch = 0.0f;
			d_yaw = 0.0f;
		}

		// ---- frame time -----------------------------------------------------
		const int now = demo_game::now_ms();
		float dt = 0.0f;
		if (g_last_ms != 0)
		{
			const int dti = now - g_last_ms;
			if (dti > 0 && dti <= 250)
			{
				dt = static_cast<float>(dti) * 0.001f;
			}
		}
		g_last_ms = now;

		// ---- ADS heuristic: fov shrinks relative to the widest seen ----------
		if (tan_x > g_fov_max)
		{
			g_fov_max = tan_x;
		}
		g_fov_ratio = (g_fov_max > 0.0001f) ? (tan_x / g_fov_max) : 1.0f;
		g_ads = g_fov_ratio < g_ads_threshold.load(std::memory_order_relaxed);
		g_scoped = g_fov_ratio < g_scope_threshold.load(std::memory_order_relaxed);
		const bool locked = g_scoped && g_lock_scoped.load(std::memory_order_relaxed);

		float bx = clampf(g_box_w.load(std::memory_order_relaxed), 0.0f, 0.98f);
		float by = clampf(g_box_h.load(std::memory_order_relaxed), 0.0f, 0.98f);
		if (g_ads)
		{
			const float s = clampf(g_ads_scale.load(std::memory_order_relaxed), 0.0f, 1.0f);
			bx *= s;
			by *= s;
		}

		if (locked)
		{
			// Scoped: behave like a normal PC mouse, reticle pinned to centre.
			g_cam[0] = clampf(g_cam[0] + d_pitch, -PITCH_LIMIT, PITCH_LIMIT);
			g_cam[1] = wrap180(g_cam[1] + d_yaw);
			g_cur_x = 0.0f;
			g_cur_y = 0.0f;
		}
		else
		{
			// ---- mouse moves the reticle, in screen space -------------------
			// yaw decreasing = turning right = reticle moves right.
			// pitch increasing = looking down = reticle moves down.
			g_cur_x += -std::tan(d_yaw * DEG2RAD) / tan_x;
			g_cur_y += std::tan(d_pitch * DEG2RAD) / tan_y;
			g_cur_x = clampf(g_cur_x, -0.98f, 0.98f);
			g_cur_y = clampf(g_cur_y, -0.98f, 0.98f);

			// ---- past the box edge the camera turns ---------------------------
			// The reticle keeps its place on screen; the excess beyond the box,
			// normalised so the screen edge = 1, sets the turn rate. Frozen while
			// a menu or the console owns input, so an open menu cannot spin you.
			if (dt > 0.0f && demo_game::key_catchers() == 0)
			{
				const float speed = g_turn_speed.load(std::memory_order_relaxed);
				const float curve = clampf(g_turn_curve.load(std::memory_order_relaxed), 0.25f, 4.0f);
				auto excess = [curve](const float c, const float b) -> float
				{
					const float a = std::fabs(c);
					if (a <= b || b >= 0.98f)
					{
						return 0.0f;
					}
					const float n = (a - b) / (0.98f - b);
					return (c < 0.0f ? -1.0f : 1.0f) * std::pow(n, curve);
				};
				const float ex = excess(g_cur_x, bx);
				const float ey = excess(g_cur_y, by);
				g_cam[1] = wrap180(g_cam[1] - ex * speed * dt);
				g_cam[0] = clampf(g_cam[0] + ey * speed * dt, -PITCH_LIMIT, PITCH_LIMIT);
			}
		}

		// ---- aim = ray through the reticle ----------------------------------
		float aim_pitch = g_cam[0], aim_yaw = g_cam[1];
		aim_from_cursor(g_cam[0], g_cam[1], g_cur_x, g_cur_y, tan_x, tan_y, aim_pitch, aim_yaw);
		if (std::fabs(aim_pitch) > PITCH_LIMIT)
		{
			// Push the camera back so the engine's own pitch clamp never bites the
			// aim -- otherwise ps and our camera would disagree by the clamp.
			g_cam[0] -= (aim_pitch - (aim_pitch < 0.0f ? -PITCH_LIMIT : PITCH_LIMIT));
			g_cam[0] = clampf(g_cam[0], -PITCH_LIMIT, PITCH_LIMIT);
			aim_from_cursor(g_cam[0], g_cam[1], g_cur_x, g_cur_y, tan_x, tan_y, aim_pitch, aim_yaw);
			aim_pitch = clampf(aim_pitch, -PITCH_LIMIT, PITCH_LIMIT);
		}
		if (!std::isfinite(aim_pitch) || !std::isfinite(aim_yaw))
		{
			reset_state();
			return;
		}

		// Live angles the next frame's mouse integrates on top of, and the
		// usercmd the server will fire along.
		ang[0] = aim_pitch;
		ang[1] = aim_yaw;
		*cmd_pitch = demo_game::angle_to_short(aim_pitch);
		*cmd_yaw = demo_game::angle_to_short(aim_yaw);

		g_off[0] = aim_pitch - g_cam[0];
		g_off[1] = wrap180(aim_yaw - g_cam[1]);
		g_off_valid = true;
		++g_frames;

		g_draw_x.store(g_cur_x, std::memory_order_relaxed);
		g_draw_y.store(g_cur_y, std::memory_order_relaxed);
		g_draw_bx.store(bx, std::memory_order_relaxed);
		g_draw_by.store(by, std::memory_order_relaxed);
		g_draw_locked.store(locked, std::memory_order_relaxed);
		g_draw_pending.store(true, std::memory_order_release);
	}

	// -----------------------------------------------------------------------
	void after_update_local_player_state(const int local_client_num)
	{
		if (!g_off_valid)
		{
			return;
		}
		// Consume: exactly one subtraction per usercmd we built, even if this
		// boundary were to run twice in a frame.
		g_off_valid = false;
		if (!live_play_active())
		{
			return;
		}
		void* cg = demo_game::cg_globals_for(local_client_num);
		if (!cg)
		{
			return;
		}
		// cg_t begins with predictedPlayerState, so ps+576 is cg+576.
		auto* ps_ang = reinterpret_cast<float*>(static_cast<char*>(cg) + demo_game::PS_VIEWANGLES);
		if (!readable(ps_ang, 12) || !std::isfinite(ps_ang[0]) || !std::isfinite(ps_ang[1]))
		{
			return;
		}
		// ps = aim + delta_angles. Subtracting (aim - camera) leaves camera +
		// delta_angles, which is what CG_CalcViewValues should render from.
		ps_ang[0] = clampf(ps_ang[0] - g_off[0], -89.0f, 89.0f);
		ps_ang[1] = wrap180(ps_ang[1] - g_off[1]);
	}

	// -----------------------------------------------------------------------
	bool override_crosshair(float* x, float* y)
	{
		if (!x || !y || !g_draw_pending.load(std::memory_order_relaxed))
		{
			return false;
		}
		if (!live_play_active())
		{
			return false;
		}
		// The engine's output is an offset from centre in 640x480 virtual units.
		*x = g_draw_x.load(std::memory_order_relaxed) * 320.0f;
		*y = g_draw_y.load(std::memory_order_relaxed) * 240.0f;
		return true;
	}

	// -----------------------------------------------------------------------
	void render_reticle()
	{
		if (!g_draw_pending.exchange(false, std::memory_order_acquire))
		{
			return;
		}
		if (!Functions::_R_AddCmdDrawStretchPic)
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
		const float scale = h / 1080.0f;
		Material* white = InternalConsole::getMaterialWhite();
		if (!white)
		{
			return;
		}

		auto rect = [&](const float x, const float y, const float rw, const float rh, float* col)
		{
			if (!std::isfinite(x) || !std::isfinite(y) || rw <= 0.0f || rh <= 0.0f)
			{
				return;
			}
			if (x + rw < 0.0f || y + rh < 0.0f || x > w || y > h)
			{
				return;
			}
			Functions::_R_AddCmdDrawStretchPic(x, y, rw, rh, 0.0f, 0.0f, 0.0f, 0.0f, col, white);
		};

		if (g_draw_box.load(std::memory_order_relaxed))
		{
			float dim[4] = { 1.0f, 1.0f, 1.0f, 0.25f };
			const float bx = g_draw_bx.load(std::memory_order_relaxed) * (w * 0.5f);
			const float by = g_draw_by.load(std::memory_order_relaxed) * (h * 0.5f);
			const float x0 = w * 0.5f - bx, x1 = w * 0.5f + bx;
			const float y0 = h * 0.5f - by, y1 = h * 0.5f + by;
			const float t = std::fmax(1.0f, 1.5f * scale);
			rect(x0, y0, x1 - x0, t, dim);
			rect(x0, y1 - t, x1 - x0, t, dim);
			rect(x0, y0, t, y1 - y0, dim);
			rect(x1 - t, y0, t, y1 - y0, dim);
		}

		if (!g_draw_reticle.load(std::memory_order_relaxed))
		{
			return;
		}
		const float cx = w * 0.5f + g_draw_x.load(std::memory_order_relaxed) * (w * 0.5f);
		const float cy = h * 0.5f + g_draw_y.load(std::memory_order_relaxed) * (h * 0.5f);
		float size = g_reticle_size.load(std::memory_order_relaxed) * scale;
		size = clampf(size, 6.0f, 120.0f);

		// Wii CoD reticle: a centre dot with four ticks and a gap. White with a
		// dark backing so it reads over bright skies. Dim + shrink when scoped.
		const bool locked = g_draw_locked.load(std::memory_order_relaxed);
		float fg[4] = { 1.0f, 1.0f, 1.0f, locked ? 0.35f : 0.95f };
		float bg[4] = { 0.0f, 0.0f, 0.0f, locked ? 0.15f : 0.55f };
		const float t = std::fmax(1.0f, 2.0f * scale);     // tick thickness
		const float gap = size * 0.25f;
		const float len = size * 0.5f;
		const float dot = std::fmax(2.0f, 3.0f * scale);
		const float o = std::fmax(1.0f, 1.0f * scale);     // outline

		// backing
		rect(cx - t * 0.5f - o, cy - gap - len - o, t + 2 * o, len + 2 * o, bg);
		rect(cx - t * 0.5f - o, cy + gap - o, t + 2 * o, len + 2 * o, bg);
		rect(cx - gap - len - o, cy - t * 0.5f - o, len + 2 * o, t + 2 * o, bg);
		rect(cx + gap - o, cy - t * 0.5f - o, len + 2 * o, t + 2 * o, bg);
		rect(cx - dot * 0.5f - o, cy - dot * 0.5f - o, dot + 2 * o, dot + 2 * o, bg);
		// ticks + dot
		rect(cx - t * 0.5f, cy - gap - len, t, len, fg);
		rect(cx - t * 0.5f, cy + gap, t, len, fg);
		rect(cx - gap - len, cy - t * 0.5f, len, t, fg);
		rect(cx + gap, cy - t * 0.5f, len, t, fg);
		rect(cx - dot * 0.5f, cy - dot * 0.5f, dot, dot, fg);
	}

	// -----------------------------------------------------------------------
	void init()
	{
		GameUtil::addCommand("wii_aim", []()
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

		GameUtil::addCommand("wii_aim_status", []() { report(); });

		GameUtil::addCommand("wii_aim_box", []()
		{
			const float bw = clampf(arg_float(1, g_box_w.load()), 0.0f, 0.98f);
			const float bh = clampf(arg_float(2, bw * 0.8f), 0.0f, 0.98f);
			g_box_w.store(bw, std::memory_order_relaxed);
			g_box_h.store(bh, std::memory_order_relaxed);
			Console::printf("[wii] bounding box %.2f x %.2f  (fraction of half-screen; "
				"0 = camera always turns, 0.98 = never)", bw, bh);
		});

		GameUtil::addCommand("wii_aim_speed", []()
		{
			g_turn_speed.store(clampf(arg_float(1, g_turn_speed.load()), 0.0f, 1080.0f),
				std::memory_order_relaxed);
			Console::printf("[wii] turn speed %.0f deg/s at the screen edge", g_turn_speed.load());
		});

		GameUtil::addCommand("wii_aim_curve", []()
		{
			g_turn_curve.store(clampf(arg_float(1, g_turn_curve.load()), 0.25f, 4.0f),
				std::memory_order_relaxed);
			Console::printf("[wii] turn curve %.2f  (1 = linear, higher = gentler near the box)",
				g_turn_curve.load());
		});

		GameUtil::addCommand("wii_aim_ads", []()
		{
			g_ads_scale.store(clampf(arg_float(1, g_ads_scale.load()), 0.0f, 1.0f),
				std::memory_order_relaxed);
			Console::printf("[wii] ADS box scale x%.2f", g_ads_scale.load());
		});

		GameUtil::addCommand("wii_aim_ads_threshold", []()
		{
			g_ads_threshold.store(clampf(arg_float(1, g_ads_threshold.load()), 0.05f, 1.0f),
				std::memory_order_relaxed);
			g_scope_threshold.store(clampf(arg_float(2, g_scope_threshold.load()), 0.05f, 1.0f),
				std::memory_order_relaxed);
			Console::printf("[wii] fov ratio thresholds: ads < %.2f, scoped < %.2f  "
				"(wii_aim_status shows the live ratio)",
				g_ads_threshold.load(), g_scope_threshold.load());
		});

		GameUtil::addCommand("wii_aim_lock_scoped", []()
		{
			Console::printf("[wii] scoped lock-to-centre %s", arg_toggle(g_lock_scoped) ? "ON" : "off");
		});

		GameUtil::addCommand("wii_aim_reticle", []()
		{
			Console::printf("[wii] reticle %s", arg_toggle(g_draw_reticle) ? "ON" : "off");
		});

		GameUtil::addCommand("wii_aim_reticle_size", []()
		{
			g_reticle_size.store(clampf(arg_float(1, g_reticle_size.load()), 6.0f, 120.0f),
				std::memory_order_relaxed);
			Console::printf("[wii] reticle size %.0f px at 1080p", g_reticle_size.load());
		});

		GameUtil::addCommand("wii_aim_showbox", []()
		{
			Console::printf("[wii] bounding box outline %s", arg_toggle(g_draw_box) ? "ON" : "off");
		});
	}
}
