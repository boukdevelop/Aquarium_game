// ========== Window.h ==========
#pragma once
#include <SDL3/SDL.h>
#include <string>

class Window
{
public:
    Window();
    ~Window();

    bool initialize(const std::string &title, int width, int height);
    void shutdown();

    SDL_Window *getSDLWindow() const { return m_window; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    SDL_Window *m_window;
    int m_width;
    int m_height;
};