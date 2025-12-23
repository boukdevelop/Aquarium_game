// ========== TimeManager.cpp ==========
#include "TimeManager.h"

TimeManager::TimeManager()
    : m_lastTime(SDL_GetTicks()), m_deltaTime(0.0f), m_fps(0.0f), m_paused(false)
{
}

void TimeManager::update()
{
    Uint64 currentTime = SDL_GetTicks();
    float frameTime = (currentTime - m_lastTime) / 1000.0f;
    m_lastTime = currentTime;

    // Cap deltaTime to prevent huge jumps
    if (frameTime > 0.1f)
    {
        frameTime = 0.1f;
    }

    m_deltaTime = m_paused ? 0.0f : frameTime;

    // Calculate FPS
    if (frameTime > 0.0f)
    {
        m_fps = 1.0f / frameTime;
    }
}
