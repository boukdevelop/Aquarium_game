#pragma once
#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "managers/AquariumManager.h"
#include "ui/ImGuiManager.h"
#include "ui/ShopUI.h"
#include "ui/StatsPanel.h"
#include "ui/DebugWindow.h"

class Game
{
public:
    Game();
    ~Game();

    bool initialize();
    void run();
    void shutdown();

private:
    void handleEvents();
    void update();
    void render();

    // Callbacks pour la boutique
    void onBuyFish(FishType type);
    void onBuyDecoration(DecorationType type);

    // État du jeu
    Window m_window;
    Renderer m_renderer;
    InputManager m_inputManager;
    TimeManager m_timeManager;

    // Managers
    AquariumManager m_aquariumManager;

    // UI
    ImGuiManager m_imguiManager;
    ShopUI m_shopUI;
    StatsPanel m_statsPanel;
    DebugWindow m_debugWindow;

    // État
    bool m_running;
    bool m_showShop;
    bool m_showDebug;

    // Mode placement
    bool m_placingFish;
    bool m_placingDecoration;
    FishType m_fishToPlace;
    DecorationType m_decorationToPlace;
};
