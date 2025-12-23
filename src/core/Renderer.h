// ========== Renderer.h ==========
#pragma once
#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool initialize(SDL_Window *window);
    void shutdown();

    void clear();
    void present();

    SDL_Renderer *getSDLRenderer() const { return m_renderer; }

private:
    SDL_Renderer *m_renderer;
};