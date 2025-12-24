#pragma once
#include "utils/Vector2D.h"
#include <SDL3/SDL.h>
#include <vector>

struct Bubble
{
    Vector2D position;
    Vector2D velocity;
    float size;
    float lifetime;
    float age;
    bool active;
};

class ParticleSystem
{
public:
    ParticleSystem();

    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void spawnBubble(const Vector2D &position);

private:
    std::vector<Bubble> m_bubbles;
    float m_spawnTimer;
};