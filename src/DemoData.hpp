#pragma once
#include "structs.h"

// Shared on-disk data model for the custom demo system.
// Ported from Airyzz/s1-mod (demo_data.hpp) via s2-mod. Layout is intentionally
// identical so the .demo file format matches the S1/S2 reference.
namespace demo_data
{
	enum DemoPacketType
	{
		SERVER_MESSAGE = 0x1,
		CLIENT_DATA = 0x2,
	};

	struct demo_client_command_t
	{
		int serverTime;
		int buttons;
		int angles_0;
		int angles_1;
		int angles_2;
	};

	struct demo_client_data_t
	{
		int predictedDataServerTime;
		float origin[3];
		float velocity[3];
		float viewAngles[3];
		int bobCycle;
		int movementDir;
	};
}
