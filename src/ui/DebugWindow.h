// ========== DebugWindow.h ==========
#pragma once

class DebugWindow
{
public:
    DebugWindow();
    void render(bool *showDebug);

    float getFishSpeedMultiplier() const { return m_fishSpeedMultiplier; }
    float getFoodSpawnRate() const { return m_foodSpawnRate; }
    bool getShowColliders() const { return m_showColliders; }

private:
    float m_fishSpeedMultiplier;
    float m_foodSpawnRate;
    bool m_showColliders;
    bool m_showFPS;
};