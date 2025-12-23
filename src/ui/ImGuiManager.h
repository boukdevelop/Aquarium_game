#pragma once
#include <SDL3/SDL.h>

class ImGuiManager
{
public:
    ImGuiManager();
    ~ImGuiManager();

    bool initialize(SDL_Window *window, SDL_Renderer *renderer);
    void shutdown();

    void beginFrame();
    void endFrame();

    void processEvent(const SDL_Event &event);

    bool wantCaptureMouse() const;
    bool wantCaptureKeyboard() const;

private:
    bool m_initialized;
};