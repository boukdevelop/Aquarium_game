#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <SDL3/SDL.h>
#include "../core/Aquarium.hpp"

// Ces includes seront nécessaires dans le .cpp, mais on peut les éviter ici
// pour ne pas alourdir la compilation si ce n'est pas nécessaire.

class GuiManager
{
public:
    // Initialise ImGui pour SDL3 et SDL_Renderer
    static void Init(SDL_Window *window, SDL_Renderer *renderer);

    // Gère les événements (souris, clavier) pour ImGui
    static void ProcessEvent(const SDL_Event *event);

    // Construit l'interface (les boutons, les textes)
    // On passe l'aquarium en référence modifiable pour pouvoir agir dessus (Bouton "Nourrir")
    static void Render(Aquarium &aquarium);

    // Nettoie ImGui à la fermeture
    static void Shutdown();

    // Démarre une nouvelle frame ImGui (appelé au début du rendu)
    static void NewFrame();

    // Termine la frame et dessine les données ImGui par dessus le rendu SDL
    static void RenderFrame(SDL_Renderer *renderer);
};

#endif