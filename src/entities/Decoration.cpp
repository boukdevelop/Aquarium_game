// ========== Decoration.cpp ==========
#include "Decoration.h"
#include "utils/Config.h"

Decoration::Decoration(DecorationType type, const Vector2D &position)
    : Entity(EntityType::DECORATION), m_decorationType(type)
{
    m_position = position;

    switch (type)
    {
    case DecorationType::PLANT:
        m_width = 30.0f;
        m_height = 80.0f;
        m_color = {34, 139, 34, 255}; // Vert forêt
        break;
    case DecorationType::ROCK:
        m_width = 50.0f;
        m_height = 40.0f;
        m_color = {128, 128, 128, 255}; // Gris
        break;
    case DecorationType::CASTLE:
        m_width = 80.0f;
        m_height = 100.0f;
        m_color = {160, 82, 45, 255}; // Brun
        break;
    }
}

void Decoration::update(float deltaTime)
{
    // Les décorations sont statiques
}

void Decoration::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);

    if (m_decorationType == DecorationType::PLANT)
    {
        // Dessiner une plante (tige + feuilles)
        SDL_FRect stem = {
            m_position.x - 5,
            m_position.y - m_height,
            10,
            m_height};
        SDL_RenderFillRect(renderer, &stem);

        // Feuilles
        for (int i = 0; i < 3; i++)
        {
            SDL_FRect leaf = {
                m_position.x - 15 + (i % 2) * 20,
                m_position.y - m_height + i * 25,
                20,
                15};
            SDL_RenderFillRect(renderer, &leaf);
        }
    }
    else if (m_decorationType == DecorationType::ROCK)
    {
        // Dessiner un rocher (ellipse)
        SDL_FRect rock = {
            m_position.x - m_width / 2,
            m_position.y - m_height / 2,
            m_width,
            m_height};
        SDL_RenderFillRect(renderer, &rock);
    }
    else if (m_decorationType == DecorationType::CASTLE)
    {
        // Dessiner un château simple
        SDL_FRect base = {
            m_position.x - m_width / 2,
            m_position.y - m_height,
            m_width,
            m_height};
        SDL_RenderFillRect(renderer, &base);

        // Tours
        SDL_FRect tower1 = {
            m_position.x - m_width / 2,
            m_position.y - m_height - 20,
            20,
            20};
        SDL_RenderFillRect(renderer, &tower1);

        SDL_FRect tower2 = {
            m_position.x + m_width / 2 - 20,
            m_position.y - m_height - 20,
            20,
            20};
        SDL_RenderFillRect(renderer, &tower2);
    }
}
