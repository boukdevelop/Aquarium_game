// ========== TimeManager.h ==========
#pragma once
#include <SDL3/SDL.h>

class TimeManager
{
public:
    TimeManager();

    void update();
    float getDeltaTime() const { return m_deltaTime; }
    float getFPS() const { return m_fps; }

    void setPaused(bool paused) { m_paused = paused; }
    bool isPaused() const { return m_paused; }

private:
    Uint64 m_lastTime;
    float m_deltaTime;
    float m_fps;
    bool m_paused;
};