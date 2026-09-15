#pragma once
// =============================================================================
//  demo/dolly.hpp — dolly camera for NATIVE demo playback
// =============================================================================
//
//  A dolly is a list of camera POINTS, each stamped with a demo time. While the
//  demo plays, the camera is interpolated between them, so the shot is tied to
//  the footage rather than to a wall clock — seek, rewind, pause and timescale
//  all work for free because the demo clock drives it.
//
//  DRAWING IS ENGINE-DRIVEN, NOT IMGUI. Markers and the path are projected with
//  the engine's own CG_WorldPosToScreenPos and drawn with R_AddCmdDrawStretchPic
//  / R_AddCmdDrawText from the existing R_EndFrame hook, so they sit correctly
//  in the world at any FOV and resolution. ImGui is used ONLY to edit the list.
//
//  ---------------------------------------------------------------------------
//  TWO CORRECTIONS TO THE PLAN, both found by decompiling before writing code
//  ---------------------------------------------------------------------------
//
//  1. DO NOT HOOK CL_Demo_FreeCameraIntegrate. The plan named it as the place to
//     write the camera pose. It is never reached during native playback:
//     CL_Demo_FreeCameraMove @0x913AE0 opens with
//
//         if (playbackData && (clc[...+262772] || playbackData[3336304] == 3))
//             return sub_917240(client);          // <-- native playback, mode 3
//
//     and only the OTHER branch calls the integrator. A hook there would simply
//     never fire. We hook CL_Demo_FreeCameraMove itself, which covers both.
//
//  2. sub_917240 IS ALREADY A CAMERA INTERPOLATOR — the engine's clip/segment
//     camera. It lerps origin and angles from a pose pair in PlaybackData
//     (+5439296 target / +5439324 previous, fraction at cg[498397]) using the
//     same shortest-arc angle handling a dolly needs. Feeding IT would be
//     elegant, but nothing has established who owns that pose pair or when it is
//     written, so per the doctrine we do not write it. We let it run and
//     overwrite the RESULT, which is the same field the engine's own camera
//     functions write, at the same point in the frame.
//
//  ---------------------------------------------------------------------------
//  PROVEN FIELDS (all confirmed from the engine this session, not inferred)
//  ---------------------------------------------------------------------------
//
//    cg + 2355648  freecam ORIGIN    float[3]   (= float index 588912)
//    cg + 2355660  freecam ANGLES    float[3]   (= float index 588915)
//    cg + 2355672  freecam VELOCITY  float[3]   (= float index 588918)
//    cg + 1993796  refdef VIEW ORIGIN float[3]  (= float index 498449)
//
//  Cross-checked two ways. CL_Demo_FreeCameraMove damps [588918..588920] as a
//  velocity and writes [588915..588917] from the usercmd angle shorts; and
//  CL_Demo_SetCameraMode(client, 2) seeds the freecam origin from the refdef
//  view origin with `cg[588912..914] = cg[498449..451]`, which pins BOTH offset
//  triples in one statement.
//
//  Camera mode lives at playbackData + 6297228 (0 first / 1 third / 2 free);
//  CG_IsTheaterOrbitCamera tests it == 2, and mode 2 is the only mode in which
//  CG_PredictPlayerState routes to CL_Demo_FreeCameraMove at all. So the dolly
//  drives only in free camera, which is also the only mode where it makes sense.
// =============================================================================

#include <cstdint>
#include <vector>

namespace dolly
{
	struct point_t
	{
		std::int32_t time{};        // demo time (cl.snap.serverTime), ms
		float pos[3]{};
		float angles[3]{};          // pitch, yaw, roll
	};

	void init();

	// ---- editing ----------------------------------------------------------
	// Captures the CURRENT free-camera pose and stamps it with the current demo
	// time. Fails (with a printed reason) when there is no native demo playing,
	// when the camera is not in free mode, or when cg is not readable yet.
	bool add_point();
	bool delete_point(int index);
	void clear_points();
	// Re-stamps a point with the current demo time, then re-sorts.
	bool retime_point(int index, std::int32_t time);

	std::vector<point_t> points();       // a copy; the list is touched by 3 threads
	int point_count();

	// ---- driving ----------------------------------------------------------
	bool enabled();
	void set_enabled(bool on);

	// Called from the CL_Demo_FreeCameraMove hook, after the original.
	// Public only so the hook stub can reach it.
	void drive();

	// ---- drawing ----------------------------------------------------------
	// Called from InternalConsole's EXISTING R_EndFrame hook (RULE A3.1 — do NOT
	// add a second hook on R_EndFrame). Draws nothing unless a native demo is
	// playing and there is something to show.
	void render();

	bool show_markers();
	void set_show_markers(bool on);
}
