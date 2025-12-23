// ========== EntityManager.h ==========
#pragma once
#include "entities/Fish.h"
#include "entities/Food.h"
#include "entities/Decoration.h"
#include <vector>
#include <memory>

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void clear();

    // Fish
    Fish *addFish(FishType type, const Vector2D &position);
    std::vector<Fish *> getAllFish() const { return m_fish; }
    int getFishCount() const { return static_cast<int>(m_fish.size()); }

    // Food
    Food *addFood(const Vector2D &position);
    std::vector<Food *> getAllFood() const { return m_food; }
    int getFoodCount() const;

    // Decorations
    Decoration *addDecoration(DecorationType type, const Vector2D &position);
    int getDecorationCount() const { return static_cast<int>(m_decorations.size()); }

    float getAverageHunger() const;

private:
    std::vector<Fish *> m_fish;
    std::vector<Food *> m_food;
    std::vector<Decoration *> m_decorations;

    void cleanupInactive();
};