#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>
#include <map>
#include <string>
#include "../core/Aquarium.hpp" // Pour lire l'état de la grille

class Renderer
{
private:
    SDL_Renderer *renderer; // Référence vers le renderer de la fenêtre

    // Stockage des textures (Images) pour ne pas les recharger à chaque image
    // Clé = nom ("poisson", "algue"), Valeur = Pointeur SDL_Texture
    std::map<std::string, SDL_Texture *> textures;

    // Dimensions d'une case de la grille (calculé selon la taille fenêtre)
    float cellWidth;
    float cellHeight;

public:
    // J'initialise avec le renderer de la fenêtre
    Renderer(SDL_Renderer *ren, int windowWidth, int windowHeight);
    ~Renderer();

    // Charge une image depuis un fichier
    bool loadTexture(const std::string &name, const std::string &filepath);

    // La fonction principale : Dessine tout l'aquarium
    void draw(const Aquarium &aquarium);

private:
    // Fonctions d'aide internes
    void drawGrid();                               // Dessine les lignes de la grille 4x4
    void drawEntity(Entity *entity, int x, int y); // Dessine un poisson ou une algue
    void drawOverlay(float salete);                // Dessine un filtre sale si nécessaire
};

#endif