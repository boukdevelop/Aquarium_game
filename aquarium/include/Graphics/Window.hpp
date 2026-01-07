#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <string>

class Window
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer; // Le moteur de rendu SDL (pas d'OpenGL direct)
    int width;
    int height;
    bool isOpen;

public:
    // Constructeur : Titre, Largeur, Hauteur
    Window(const std::string &title, int w, int h);

    // Destructeur : Nettoie la SDL
    ~Window();

    // Gestion de la boucle
    void handleEvents(); // On traitera les événements ici (clavier, croix rouge)
    void clear();        // Efface l'écran (généralement en noir ou bleu)
    void display();      // Affiche ce qu'on vient de dessiner (swap buffers)

    // Getters utiles pour les autres classes
    bool isRunning() const { return isOpen; }
    SDL_Window *getNativeWindow() const { return window; }
    SDL_Renderer *getRenderer() const { return renderer; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif