#pragma once

namespace theater_camera
{
	// These ARE the engine's own camera-mode numbers, which is what lets one
	// enum drive both demo systems: CG_IsTheaterFreeCamera tests == 1 and
	// CG_IsTheaterOrbitCamera tests == 2.
	enum camera_mode
	{
		THEATER_CAMERA_FIRST_PERSON = 0,
		THEATER_CAMERA_THIRD_PERSON = 1,
		THEATER_CAMERA_FREECAM = 2,
	};

	void init();

	// The effective mode for whichever demo system is playing. On NATIVE this is
	// the engine's own value (its F2 key still drives it); in the CUSTOM theater
	// it is ours, delivered to the engine by hooking the two theater-camera
	// predicates. The enum values ARE the engine's mode numbers.
	camera_mode get_mode();
	void set_mode(camera_mode mode);

	// Is any demo playing, i.e. is the camera meaningful at all?
	bool available();

	// False means the predicate hooks did not install, so the custom theater
	// cannot leave first person. Surfaced in the UI rather than failing silently.
	bool hooks_installed();

	// True while the CUSTOM theater owns the camera AND it is in free-fly mode.
	// demo_playback's CL_CreateCmd stub strips live input during replay; this is
	// what tells it to keep the movement fields the free-camera mover needs.
	bool custom_theater_freecam_active();

}
