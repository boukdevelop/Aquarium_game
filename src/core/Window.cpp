// ========== Window.cpp ==========
#include "Window.h"
#include <SDL3/SDL.h>

Window::Window() : m_window(nullptr), m_width(0), m_height(0) {
}

Window::~Window() {
    shutdown();
}

bool Window::initialize(const std::string& title, int width, int height) {
    m_width = width;
    m_height = height;
    
    m_window = SDL_CreateWindow(
        title.c_str(),
        width, height,
        SDL_WINDOW_RESIZABLE
    );
    
    if (!m_window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    return true;
}

void Window::shutdown() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}