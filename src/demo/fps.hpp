#pragma once

#include <cstdint>

namespace demo_timescale
{
	namespace fps
	{
		inline float g_smooth = 60.0f;
		inline bool g_init = false;

		inline void record_frame_time(const std::int32_t msec)
		{
			if (msec <= 0)
			{
				return;
			}
			const float instant = 1000.0f / static_cast<float>(msec);
			if (!g_init)
			{
				g_smooth = instant;
				g_init = true;
			}
			else
			{
				g_smooth = g_smooth * 0.9f + instant * 0.1f;
			}
		}

		inline float avg()
		{
			return g_init ? g_smooth : 60.0f;
		}
	}
}
