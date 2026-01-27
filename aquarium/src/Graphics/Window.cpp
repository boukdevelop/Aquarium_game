#include "../../include/Graphics/Window.hpp"
#include <iostream>

Window::Window(const std::string &title, int w, int h)
    : width(w), height(h), isOpen(true), window(nullptr), renderer(nullptr)
{

    // 1. Initialisation de SDL3
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
        isOpen = false;
        return;
    }

    // 2. Création de la fenêtre
    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Erreur SDL_CreateWindow : " << SDL_GetError() << std::endl;
        isOpen = false;
        return;
    }

    // 3. Création du Renderer (Le "Pinceau" qui utilise la carte graphique en 2D)
    renderer = SDL_CreateRenderer(window, NULL); // NULL pour le driver par défaut
    if (!renderer)
    {
        std::cerr << "Erreur SDL_CreateRenderer : " << SDL_GetError() << std::endl;
        isOpen = false;
        return;
    }
}

Window::~Window()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::handleEvents()
{
    // pour gérer ImGui en même temps, mais je sais pas encore ce que je vais faire avec ceci
}

void Window::clear()
{
    // Couleur de fond : Bleu Océan foncé (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 20, 30, 60, 255);
    SDL_RenderClear(renderer);
}

void Window::display()
{
    SDL_RenderPresent(renderer);
}