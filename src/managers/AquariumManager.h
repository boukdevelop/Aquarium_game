// ========== AquariumManager.h ==========
#pragma once
#include "EntityManager.h"
#include "systems/FishBehavior.h"
#include "systems/FeedingSystem.h"
#include "systems/ParticleSystem.h"
#include "ui/StatsPanel.h"

class AquariumManager
{
public:
    AquariumManager();

    void initialize();
    void update(float deltaTime);
    void render(SDL_Renderer *renderer);
    void shutdown();

    // Game actions
    void spawnFood(const Vector2D &position);
    void spawnFish(FishType type, const Vector2D &position);
    void spawnDecoration(DecorationType type, const Vector2D &position);

    // Money system
    int getMoney() const { return m_money; }
    void addMoney(int amount) { m_money += amount; }
    bool spendMoney(int amount);

    // Stats
    AquariumStats getStats() const;

private:
    EntityManager m_entityManager;
    ParticleSystem m_particleSystem;

    int m_money;
    float m_moneyTimer;

    void applyFishBehaviors();
    void checkFeeding();
    void generatePassiveIncome(float deltaTime);
};