// ========== AquariumManager.cpp ==========
#include "AquariumManager.h"
#include "utils/Config.h"
#include "utils/Math.h"

AquariumManager::AquariumManager()
    : m_money(Config::STARTING_MONEY), m_moneyTimer(0.0f)
{
}

void AquariumManager::initialize()
{
    // Spawn quelques poissons de départ
    for (int i = 0; i < 3; i++)
    {
        Vector2D pos(
            Math::randomFloat(200, Config::AQUARIUM_WIDTH - 200),
            Math::randomFloat(Config::WATER_SURFACE_Y + 100,
                              Config::WATER_BOTTOM_Y - 100));
        spawnFish(FishType::GOLDFISH, pos);
    }

    // Ajouter une décoration
    spawnDecoration(DecorationType::PLANT,
                    Vector2D(Config::AQUARIUM_WIDTH / 2, Config::WATER_BOTTOM_Y));
}

void AquariumManager::update(float deltaTime)
{
    // Update entities
    m_entityManager.update(deltaTime);

    // Update particles
    m_particleSystem.update(deltaTime);

    // Apply fish behaviors
    applyFishBehaviors();

    // Check feeding
    checkFeeding();

    // Generate passive income
    generatePassiveIncome(deltaTime);
}

void AquariumManager::render(SDL_Renderer *renderer)
{
    // Render water background
    SDL_SetRenderDrawColor(renderer, 20, 100, 180, 255);
    SDL_RenderClear(renderer);

    // Water surface
    SDL_SetRenderDrawColor(renderer, 100, 150, 220, 100);
    SDL_FRect surface = {0, 0,
                         static_cast<float>(Config::AQUARIUM_WIDTH),
                         Config::WATER_SURFACE_Y};
    SDL_RenderFillRect(renderer, &surface);

    // Render particles (bubbles)
    m_particleSystem.render(renderer);

    // Render entities
    m_entityManager.render(renderer);
}

void AquariumManager::shutdown()
{
    m_entityManager.clear();
}

void AquariumManager::spawnFood(const Vector2D &position)
{
    m_entityManager.addFood(position);
}

void AquariumManager::spawnFish(FishType type, const Vector2D &position)
{
    m_entityManager.addFish(type, position);
}

void AquariumManager::spawnDecoration(DecorationType type, const Vector2D &position)
{
    m_entityManager.addDecoration(type, position);
}

bool AquariumManager::spendMoney(int amount)
{
    if (m_money >= amount)
    {
        m_money -= amount;
        return true;
    }
    return false;
}

AquariumStats AquariumManager::getStats() const
{
    AquariumStats stats;
    stats.fishCount = m_entityManager.getFishCount();
    stats.foodCount = m_entityManager.getFoodCount();
    stats.decorationCount = m_entityManager.getDecorationCount();
    stats.averageHunger = m_entityManager.getAverageHunger();
    stats.money = m_money;
    stats.fps = 0.0f; // Set by Game class
    return stats;
}

void AquariumManager::applyFishBehaviors()
{
    auto allFish = m_entityManager.getAllFish();
    auto allFood = m_entityManager.getAllFood();

    for (auto *fish : allFish)
    {
        if (!fish->isActive())
            continue;

        FishBehavior::applyFlocking(fish, allFish);
        FishBehavior::seekFood(fish, allFood);
        FishBehavior::avoidBorders(fish);
    }
}

void AquariumManager::checkFeeding()
{
    auto allFish = m_entityManager.getAllFish();
    auto allFood = m_entityManager.getAllFood();

    FeedingSystem::checkFeeding(allFish, allFood);
}

void AquariumManager::generatePassiveIncome(float deltaTime)
{
    m_moneyTimer += deltaTime;

    // Gagner 1$ toutes les 5 secondes par poisson
    if (m_moneyTimer >= 5.0f)
    {
        m_moneyTimer = 0.0f;
        int fishCount = m_entityManager.getFishCount();
        addMoney(fishCount);
    }
}
