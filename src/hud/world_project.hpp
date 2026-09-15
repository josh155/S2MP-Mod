#pragma once

// =============================================================================
//  world_project -- world position -> screen pixels, safely
// =============================================================================
//
//  Extracted from demo/dolly.cpp, which is where this was first proven in game.
//  Anything that wants to draw something at a world position (dolly markers,
//  player name tags) shares THIS copy, so a fix lands once.
//
//  ---------------------------------------------------------------------------
//  RULE A21 IS THE WHOLE DESIGN. Do not remove the inlining below.
//  ---------------------------------------------------------------------------
//
//  The obvious call is CG_WorldPosToScreenPos @0x3E6250. It crashed the game the
//  first time the dolly ran, and the reason generalises: that function resolves
//  cg ITSELF, via CG_GetLocalClientGlobals, and then dereferences the result
//  with NO null check --
//
//      3e627b  call CG_GetLocalClientGlobals
//      3e628e  subss xmm4, dword ptr [rax+1E6C44h]     <- faults when cg is NULL
//
//  Validating our own cg pointer said nothing about the one the engine went and
//  fetched: demo_game::cg_globals_for() reads the RENDERER back-pointer while
//  CG_GetLocalClientGlobals reads the engine's own encrypted global, and during a
//  seek teardown they genuinely disagree -- one stale-but-set, the other NULL.
//
//  So we do not call it. Its body is 0x118 bytes and fully decoded, so the
//  wrapper is inlined here and only the LEAF is called --
//  CG_ProjectViewDirToScreenPos @0x38EFD0 -- which touches nothing but the
//  pointers handed to it.
//
//  Every operand below is read off that disassembly:
//      cg + 0x1E6C30 (1993776)  float      tan half fov X   -> xmm3
//      cg + 0x1E6C34 (1993780)  float      tan half fov Y   -> [rsp+20h]
//      cg + 0x1E6C44 (1993796)  float[3]   view origin
//      cg + 0x1E6C50 (1993808)  float[3][3] view axis       -> rcx
//      refdef + 0x20            float[2]   viewport w/h     -> rdx
//  1993776..1993844 is contiguous, so ONE 68-byte probe validates all four.
// =============================================================================

#include <cmath>
#include <cstddef>
#include <cstdint>

#include "game.h"

namespace world_project
{
	// cg byte offsets.
	inline constexpr std::size_t CG_TAN_HALF_FOV_X = 1993776;
	inline constexpr std::size_t CG_TAN_HALF_FOV_Y = 1993780;
	inline constexpr std::size_t CG_REFDEF_VIEW_ORIGIN = 1993796;
	inline constexpr std::size_t CG_REFDEF_VIEW_AXIS = 1993808;
	inline constexpr std::size_t CG_VIEW_BLOCK = 1993776;
	inline constexpr std::size_t CG_VIEW_BLOCK_BYTES = 68;

	// CG_GetRefdefView returns &unk_90BB140 + 108*client; +32/+36 are the
	// viewport width and height in floats, which is the space the leaf's output
	// is in.
	inline constexpr std::size_t REFDEF_VIEWPORT_W = 32;

	// Render-target size -- THE SAME globals InternalConsole::drawConsole uses as
	// windowWidth/windowHeight, and the same two LUI_WorldToScreenPosition
	// normalises by. That is what makes the output directly usable as
	// R_AddCmdDraw* pixel coordinates.
	inline constexpr std::uintptr_t ADDR_SCREEN_W = 0x1C85268;   // IDA 0x1C86268
	inline constexpr std::uintptr_t ADDR_SCREEN_H = 0x1C8526C;   // IDA 0x1C8626C
	inline constexpr std::uintptr_t ADDR_PROJECT_VIEW_DIR = 0x38DFD0;  // IDA 0x38EFD0
	inline constexpr std::uintptr_t ADDR_GET_REFDEF_VIEW = 0x49F170;   // IDA 0x4A0170

	// RULE A17 -- exact widths. The leaf returns `char` (1 = in front, 0 =
	// behind/clamped); declaring it wider reads register residue. Arg slots
	// follow the disassembly: rcx, rdx, r8, xmm3, then [rsp+0x20], [rsp+0x28].
	using CG_ProjectViewDirToScreenPos_t = char(__fastcall*)(
		const float* axis, const float* viewport, const float* dir,
		float tan_half_x, float tan_half_y, float* out_xy);
	using CG_GetRefdefView_t = void*(__fastcall*)(int);

	// RULE A6 -- `if (!p)` is not enough in this game: a global belonging to an
	// idle subsystem holds junk, not zero.
	[[nodiscard]] inline bool readable(const void* p, const std::size_t n)
	{
		if (!p || n == 0)
		{
			return false;
		}
		const auto a = reinterpret_cast<std::uintptr_t>(p);
		if (a < 0x10000 || a > 0x00007FFFFFFFFFFFull)
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
		const auto end = reinterpret_cast<std::uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
		return a + n <= end;
	}

	// BACKSTOP, not the fix. The fix is that every pointer handed to the engine
	// is one we validated. This catches a page unmapped between the VirtualQuery
	// and the call. Deliberately a LEAF with no C++ objects so __try is legal.
	[[nodiscard]] inline bool project_guarded(const CG_ProjectViewDirToScreenPos_t fn,
		const float* axis, const float* viewport, const float* dir,
		const float tan_half_x, const float tan_half_y, float* out_xy,
		char& in_front)
	{
		__try
		{
			in_front = fn(axis, viewport, dir, tan_half_x, tan_half_y, out_xy);
			return true;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			in_front = 0;
			return false;
		}
	}

	struct Projector
	{
		CG_ProjectViewDirToScreenPos_t fn{};
		const float* viewport{};
		const float* view_origin{};
		const float* view_axis{};
		float tan_half_x{};
		float tan_half_y{};
		float screen_w{};
		float screen_h{};
		float scale_x = 1.0f;
		float scale_y = 1.0f;

		[[nodiscard]] bool valid() const
		{
			return fn && viewport && view_origin && view_axis;
		}

		// False when the point is behind the camera OR the call could not be made
		// safely. The engine still writes clamped edge coordinates for a point
		// behind, so its return value is the only way to tell -- and the guarded
		// failure path reports false too, so a caller can never draw from
		// uninitialised output.
		[[nodiscard]] bool project(const float world[3], float& sx, float& sy) const
		{
			const float dx = world[0] - view_origin[0];
			const float dy = world[1] - view_origin[1];
			const float dz = world[2] - view_origin[2];
			float len = std::sqrt(dx * dx + dy * dy + dz * dz);
			if (!(len > 0.0f))
			{
				len = 1.0f;
			}
			const float inv = 1.0f / len;
			const float dir[3] = { dx * inv, dy * inv, dz * inv };

			float out[2]{};
			char in_front = 0;
			if (!project_guarded(fn, view_axis, viewport, dir,
				tan_half_x, tan_half_y, out, in_front))
			{
				sx = 0.0f;
				sy = 0.0f;
				return false;
			}
			sx = out[0] * scale_x;
			sy = out[1] * scale_y;
			if (!std::isfinite(sx) || !std::isfinite(sy))
			{
				return false;   // a NaN would propagate into every draw call
			}
			return in_front != 0;
		}

		[[nodiscard]] float distance_to(const float world[3]) const
		{
			const float dx = world[0] - view_origin[0];
			const float dy = world[1] - view_origin[1];
			const float dz = world[2] - view_origin[2];
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}
	};

	// `cg` must already be a pointer the CALLER validated -- see RULE A21 above.
	[[nodiscard]] inline bool make_projector(void* cg, Projector& p)
	{
		if (!cg)
		{
			return false;
		}
		p.fn = reinterpret_cast<CG_ProjectViewDirToScreenPos_t>(_b(ADDR_PROJECT_VIEW_DIR));

		const auto* vb = reinterpret_cast<const float*>(
			static_cast<char*>(cg) + CG_VIEW_BLOCK);
		if (!readable(vb, CG_VIEW_BLOCK_BYTES))
		{
			return false;
		}
		p.tan_half_x = vb[0];
		p.tan_half_y = vb[1];
		p.view_origin = vb + (CG_REFDEF_VIEW_ORIGIN - CG_VIEW_BLOCK) / 4;
		p.view_axis = vb + (CG_REFDEF_VIEW_AXIS - CG_VIEW_BLOCK) / 4;

		// A zero or absurd fov means cg is STALE rather than merely mapped --
		// exactly the state a null engine cg would have produced. Refusing here
		// is what turns "wrong pointer" into "nothing drawn this frame".
		if (!std::isfinite(p.tan_half_x) || !std::isfinite(p.tan_half_y)
			|| p.tan_half_x <= 0.0001f || p.tan_half_y <= 0.0001f
			|| p.tan_half_x > 100.0f || p.tan_half_y > 100.0f)
		{
			return false;
		}

		const auto get_view = reinterpret_cast<CG_GetRefdefView_t>(_b(ADDR_GET_REFDEF_VIEW));
		void* refdef = get_view(0);
		if (!readable(refdef, 108))
		{
			return false;
		}
		p.viewport = reinterpret_cast<const float*>(
			static_cast<char*>(refdef) + REFDEF_VIEWPORT_W);

		const auto* sw = reinterpret_cast<const int*>(_b(ADDR_SCREEN_W));
		const auto* sh = reinterpret_cast<const int*>(_b(ADDR_SCREEN_H));
		if (!readable(sw, 4) || !readable(sh, 4) || *sw <= 0 || *sh <= 0)
		{
			return false;
		}
		p.screen_w = static_cast<float>(*sw);
		p.screen_h = static_cast<float>(*sh);

		// The leaf emits REFDEF VIEWPORT pixels. Usually that is the render
		// target, but not while a viewport is inset, so rescale rather than
		// assume.
		if (p.viewport[0] > 1.0f && p.viewport[1] > 1.0f)
		{
			p.scale_x = p.screen_w / p.viewport[0];
			p.scale_y = p.screen_h / p.viewport[1];
		}
		return p.valid();
	}
}
