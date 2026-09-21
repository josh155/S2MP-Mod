#include "pch.h"
#include "demo/demo_game.hpp"
#include "time_scale_hook.hpp"
#include "Console.hpp"
#include "DevDef.h"

float g_latestDeltaTime = 0.0f;
int g_latestDeltaTimeVersion = 0;
bool enable_time_scale_ui = true;
float scale_factor = 1.0f;

static int now_ms_local()
{
	return demo_game::now_ms();
}

float calculateFrameDelta(int lastTimeMs, int currentTimeMs)
{
	if (lastTimeMs == -1 || currentTimeMs <= lastTimeMs)
	{
		return 0.0f;
	}
	return static_cast<float>(currentTimeMs - lastTimeMs) / 1000.0f;
}

void hookGameLoopForTimeScale(int& lastFrameTime)
{
	if (!enable_time_scale_ui || g_latestDeltaTimeVersion == 0) return;

	int currentTimeMs = now_ms_local();
	float rawDelta = calculateFrameDelta(lastFrameTime, currentTimeMs);
	lastFrameTime = currentTimeMs;
	float scaledDelta = rawDelta * scale_factor;

	g_latestDeltaTimeVersion++;
	setLatestDeltaTime(scaledDelta);
}

void LUI_Layout_hook(float& delta, float scale)
{
	if (!enable_time_scale_ui || g_latestDeltaTimeVersion == 0) return;
	setLatestDeltaTime(delta * scale);
}

float getLatestDeltaTime()
{
	if (!enable_time_scale_ui || g_latestDeltaTimeVersion == 0)
	{
		return now_ms_local() / 1000.0f;
	}
	return g_latestDeltaTime;
}

void setLatestDeltaTime(float dt)
{
	g_latestDeltaTime = dt;
}

void TimeScale_Init()
{
	scale_factor = 1.0f;
	enable_time_scale_ui = true;
	DEV_PRINTF("Time Scale Support initialized\n");
}

void TimeScale_SetFactor(float factor)
{
	if (factor < 0.05f || factor > 8.0f)
	{
		DEV_PRINTF("Time Scale: Invalid factor %f\n", factor);
		return;
	}
	scale_factor = factor;
	g_latestDeltaTimeVersion++;
	DEV_PRINTF("Time Scale Factor set to: %.2fx\n", scale_factor);
}

void TimeScale_Enable(bool enable)
{
	enable_time_scale_ui = enable;
	if (enable) g_latestDeltaTimeVersion++;
}

float TimeScale_GetFactor()
{
	return scale_factor;
}
