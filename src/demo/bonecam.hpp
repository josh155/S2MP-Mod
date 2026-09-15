#pragma once

#include <string>
#include <vector>

// =============================================================================
//  BONE CAM — lock the demo camera to a player's bone, keep free mouse look
// =============================================================================
//
// Rides a bone on a player's skeleton (hands, head, weapon tag, spine...) while
// the mouse still aims freely. The result is the handheld/helmet-cam look:
// the camera inherits the animation's real motion — recoil, sprint bob, the
// lurch when they get hit — which is impossible to fake with a smooth path.
//
// Works in BOTH demo systems, because it writes only the free camera's ORIGIN
// after the engine's own CL_Demo_FreeCameraMove has run. That function sets the
// angles from the usercmd (i.e. your mouse) and integrates position; overwriting
// just the position leaves mouse look completely untouched.
//
// Requires FREE CAMERA mode — it is the only mode the engine routes through
// CL_Demo_FreeCameraMove at all.
namespace bonecam
{
	struct bone_entry
	{
		int index{};
		std::string name;      // "bone N" when the model's name table is unreadable
	};

	void init();

	// Once per frame on the client thread, from demo_native's existing
	// CG_PublishHudModel desc-100 call-out. Keeps the bone list up to date
	// INDEPENDENTLY of whether the lock is on or the camera is in free mode —
	// otherwise you could never see the list in order to pick a bone from it,
	// and nothing would appear at all if the engine's mover were not running.
	void tick();

	// Called from dolly's existing CL_Demo_FreeCameraMove hook (RULE A3.1 — that
	// address must not be hooked twice). Runs on the client thread, after the
	// engine's mover, so the angles it just wrote from your mouse survive.
	void apply();

	bool enabled();
	void set_enabled(bool on);

	// Bone selection. set_bone_by_name matches case-insensitively against the
	// model's own bone table and returns false if nothing matched.
	int  bone_index();
	void set_bone_index(int index);
	bool set_bone_by_name(const char* name);
	const char* bone_name();

	// Which player to ride. -1 = the demo's own local client (the default).
	int  entity();
	void set_entity(int ent);

	// Camera-RELATIVE offset: forward / right / up along the direction you are
	// currently looking, which is what makes framing a shot practical.
	void get_offset(float& fwd, float& right, float& up);
	void set_offset(float fwd, float right, float up);

	// 0 = rigid (every animation jolt), ->1 = heavier damping. Position only;
	// aim is never smoothed because that would fight the mouse.
	float smoothing();
	void set_smoothing(float value);

	// The live bone list for the attached player, rebuilt when the model changes.
	std::vector<bone_entry> bones();

	// Human-readable state for the UI/console, including why it is not running.
	std::string status();
}
