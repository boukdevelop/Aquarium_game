#include "Game.h"
#include "utils/Config.h"
#include <SDL3/SDL.h>

Game::Game()
    : m_running(false), m_showShop(false), m_showDebug(false), m_placingFish(false), m_placingDecoration(false), m_fishToPlace(FishType::GOLDFISH), m_decorationToPlace(DecorationType::PLANT)
{
}

Game::~Game()
{
    shutdown();
}

bool Game::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!m_window.initialize(Config::WINDOW_TITLE,
                             Config::WINDOW_WIDTH,
                             Config::WINDOW_HEIGHT))
    {
        return false;
    }

    if (!m_renderer.initialize(m_window.getSDLWindow()))
    {
        return false;
    }

    if (!m_imguiManager.initialize(m_window.getSDLWindow(),
                                   m_renderer.getSDLRenderer()))
    {
        return false;
    }

    // Setup callbacks
    m_shopUI.setOnBuyFish([this](FishType type)
                          { onBuyFish(type); });
    m_shopUI.setOnBuyDecoration([this](DecorationType type)
                                { onBuyDecoration(type); });

    // Initialize game
    m_aquariumManager.initialize();

    m_running = true;
    return true;
}

void Game::run()
{
    while (m_running)
    {
        handleEvents();
        update();
        render();
    }
}

void Game::shutdown()
{
    m_aquariumManager.shutdown();
    m_imguiManager.shutdown();
    m_renderer.shutdown();
    m_window.shutdown();
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        m_imguiManager.processEvent(event);

        if (event.type == SDL_EVENT_QUIT)
        {
            m_running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            // Ne pas traiter les touches si ImGui les capture
            if (!m_imguiManager.wantCaptureKeyboard())
            {
                switch (event.key.key)
                {
                case SDLK_ESCAPE:
                    m_running = false;
                    break;
                case SDLK_TAB:
                    m_showShop = !m_showShop;
                    break;
                case SDLK_SPACE:
                    m_timeManager.setPaused(!m_timeManager.isPaused());
                    break;
                case SDLK_D:
                    m_showDebug = !m_showDebug;
                    break;
                }
            }
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (!m_imguiManager.wantCaptureMouse())
            {
                Vector2D mousePos = m_inputManager.getMousePosition();

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (m_placingFish)
                    {
                        m_aquariumManager.spawnFish(m_fishToPlace, mousePos);
                        m_placingFish = false;
                    }
                    else if (m_placingDecoration)
                    {
                        m_aquariumManager.spawnDecoration(m_decorationToPlace, mousePos);
                        m_placingDecoration = false;
                    }
                    else
                    {
                        // Ajouter de la nourriture
                        m_aquariumManager.spawnFood(mousePos);
                    }
                }

                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    // Clic droit annule le placement
                    m_placingFish = false;
                    m_placingDecoration = false;
                }
            }
        }
    }

    m_inputManager.update();
}

void Game::update()
{
    m_timeManager.update();

    if (!m_timeManager.isPaused())
    {
        m_aquariumManager.update(m_timeManager.getDeltaTime());
    }
}

void Game::render()
{
    m_renderer.clear();

    // Render aquarium
    m_aquariumManager.render(m_renderer.getSDLRenderer());

    // Render UI
    m_imguiManager.beginFrame();

    // Stats panel (toujours visible)
    AquariumStats stats = m_aquariumManager.getStats();
    stats.fps = m_timeManager.getFPS();
    m_statsPanel.render(stats);

    // Shop (si ouvert)
    if (m_showShop)
    {
        int money = m_aquariumManager.getMoney();
        m_shopUI.render(money);
        // Le money est modifié par référence dans ShopUI
    }

    // Debug window
    if (m_showDebug)
    {
        m_debugWindow.render(&m_showDebug);
    }

    // Indicateur de placement
    if (m_placingFish || m_placingDecoration)
    {
        ImGui::SetNextWindowPos(ImVec2(Config::WINDOW_WIDTH / 2 - 150, 20),
                                ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 60), ImGuiCond_Always);
        ImGui::Begin("##placement", nullptr,
                     ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove);

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
                           "Cliquez pour placer");
        ImGui::Text("Clic droit pour annuler");
        ImGui::End();
    }

    // Pause indicator
    if (m_timeManager.isPaused())
    {
        ImGui::SetNextWindowPos(ImVec2(Config::WINDOW_WIDTH / 2 - 50,
                                       Config::WINDOW_HEIGHT / 2 - 25),
                                ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Always);
        ImGui::Begin("##pause", nullptr,
                     ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove);
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "  PAUSE");
        ImGui::End();
    }

    m_imguiManager.endFrame();

    m_renderer.present();
}

void Game::onBuyFish(FishType type)
{
    int price = 0;
    switch (type)
    {
    case FishType::GOLDFISH:
        price = Config::GOLDFISH_PRICE;
        break;
    case FishType::CLOWNFISH:
        price = Config::CLOWNFISH_PRICE;
        break;
    case FishType::ANGELFISH:
        price = Config::ANGELFISH_PRICE;
        break;
    }

    if (m_aquariumManager.spendMoney(price))
    {
        m_placingFish = true;
        m_fishToPlace = type;
        m_placingDecoration = false;
    }
}

void Game::onBuyDecoration(DecorationType type)
{
    int price = 0;
    switch (type)
    {
    case DecorationType::PLANT:
        price = Config::PLANT_PRICE;
        break;
    case DecorationType::ROCK:
        price = Config::ROCK_PRICE;
        break;
    case DecorationType::CASTLE:
        price = Config::CASTLE_PRICE;
        break;
    }

    if (m_aquariumManager.spendMoney(price))
    {
        m_placingDecoration = true;
        m_decorationToPlace = type;
        m_placingFish = false;
    }
}
