#include "../../include/Graphics/Renderer.hpp"
#include <iostream>

Renderer::Renderer(SDL_Renderer *ren, int windowWidth, int windowHeight)
    : renderer(ren)
{
    // Calcul de la taille d'une case (Fenêtre divisée par 4)
    cellWidth = (float)windowWidth / Aquarium::WIDTH;
    cellHeight = (float)windowHeight / Aquarium::HEIGHT;
}

Renderer::~Renderer()
{
    // Nettoyer les textures chargées
    for (auto const &[key, texture] : textures)
    {
        SDL_DestroyTexture(texture);
    }
}

bool Renderer::loadTexture(const std::string &name, const std::string &filepath)
{
    // Chargement d'une image BMP (Format natif SDL)
    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());
    if (!surface)
    {
        std::cerr << "Erreur chargement image " << filepath << " : " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // On n'a plus besoin de la surface CPU

    if (texture)
    {
        textures[name] = texture;
        return true;
    }
    return false;
}

void Renderer::draw(const Aquarium &aquarium)
{
    if (textures.find("fond") != textures.end())
    {
        SDL_RenderTexture(renderer, textures["fond"], NULL, NULL); // NULL = Tout l'écran
    }

    // 1. Dessiner la grille (lignes blanches)
    drawGrid();

    // 2. Dessiner les entités
    for (int x = 0; x < Aquarium::WIDTH; ++x)
    {
        for (int y = 0; y < Aquarium::HEIGHT; ++y)
        {
            Entity *e = aquarium.getEntityAt(x, y);
            if (e != nullptr)
            {
                drawEntity(e, x, y);
            }
        }
    }

    // 3. Dessiner le filtre de saleté si besoin
    if (aquarium.getSalete() > 10.0f)
    {
        drawOverlay(aquarium.getSalete());
    }
}

void Renderer::drawGrid()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200); // Gris

    // Lignes verticales
    for (int i = 1; i < Aquarium::WIDTH; ++i)
    {
        float x = i * cellWidth;
        SDL_RenderLine(renderer, x, 0, x, Aquarium::HEIGHT * cellHeight);
    }
    // Lignes horizontales
    for (int j = 1; j < Aquarium::HEIGHT; ++j)
    {
        float y = j * cellHeight;
        SDL_RenderLine(renderer, 0, y, Aquarium::WIDTH * cellWidth, y);
    }
}

void Renderer::drawEntity(Entity *entity, int x, int y)
{
    SDL_FRect dstRect;
    dstRect.x = x * cellWidth;
    dstRect.y = y * cellHeight;
    dstRect.w = cellWidth;
    dstRect.h = cellHeight;

    SDL_Texture *textureToDraw = nullptr;

    if (entity->type == EntityType::POISSON)
    {
        // Cherche la texture, sinon dessine un carré rouge (fallback)
        if (textures.find("poisson") != textures.end())
        {
            textureToDraw = textures["poisson"];
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 250, 100, 100, 205); // Rouge
            SDL_RenderFillRect(renderer, &dstRect);
            return;
        }
    }
    else if (entity->type == EntityType::ALGUE)
    {
        if (textures.find("algue") != textures.end())
        {
            textureToDraw = textures["algue"];
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255); // Vert algue
            SDL_RenderFillRect(renderer, &dstRect);
            return;
        }
    }

    if (textureToDraw)
    {
        SDL_RenderTexture(renderer, textureToDraw, NULL, &dstRect);
    }
}

void Renderer::drawOverlay(float salete)
{
    // Plus c'est sale, plus c'est opaque (max 150 alpha)
    int alpha = (int)(salete * 2);
    if (alpha > 150)
        alpha = 150;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 100, 120, 0, alpha); // Vert caca d'oie
    SDL_FRect fullScreen = {0, 0, Aquarium::WIDTH * cellWidth, Aquarium::HEIGHT * cellHeight};
    SDL_RenderFillRect(renderer, &fullScreen);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}