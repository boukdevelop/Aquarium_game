// ========== Renderer.cpp ==========
#include "Renderer.h"

Renderer::Renderer() : m_renderer(nullptr)
{
}

Renderer::~Renderer()
{
    shutdown();
}

bool Renderer::initialize(SDL_Window *window)
{
    m_renderer = SDL_CreateRenderer(window, nullptr);

    if (!m_renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    return true;
}

void Renderer::shutdown()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(m_renderer);
}
