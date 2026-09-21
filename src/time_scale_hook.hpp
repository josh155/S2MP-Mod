#pragma once

/**
 * @brief Time Scale Hook Interface for LUI Elements (MWR-style)
 */

extern float g_latestDeltaTime;
extern int g_latestDeltaTimeVersion;
extern bool enable_time_scale_ui;
extern float scale_factor;

void LUI_Layout_hook(float& delta, float scale);

#define SCALE_LUI_LAYOUT(delta, scale) \
    do { \
        if (enable_time_scale_ui && g_latestDeltaTimeVersion > 0) { \
            setLatestDeltaTime((delta) * (scale)); \
        } \
    } while(0)

#define GET_SCALED_DELTA(delta, scale) \
    ((enable_time_scale_ui && g_latestDeltaTimeVersion > 0) ? getLatestDeltaTime() : (delta))

void TimeScale_Init();
void TimeScale_SetFactor(float factor);
void TimeScale_Enable(bool enable);
float TimeScale_GetFactor();

void setLatestDeltaTime(float dt);
float getLatestDeltaTime();
