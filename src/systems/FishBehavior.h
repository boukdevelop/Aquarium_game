// ========== FishBehavior.h ==========
#pragma once
#include "entities/Fish.h"
#include "entities/Food.h"
#include <vector>

class FishBehavior {
public:
    static void applyFlocking(Fish* fish, const std::vector<Fish*>& allFish);
    static void seekFood(Fish* fish, const std::vector<Food*>& allFood);
    static void avoidBorders(Fish* fish);
    
private:
    static Vector2D calculateCohesion(Fish* fish, const std::vector<Fish*>& neighbors);
    static Vector2D calculateSeparation(Fish* fish, const std::vector<Fish*>& neighbors);
    static Vector2D calculateAlignment(Fish* fish, const std::vector<Fish*>& neighbors);
    static std::vector<Fish*> getNeighbors(Fish* fish, const std::vector<Fish*>& allFish);
};