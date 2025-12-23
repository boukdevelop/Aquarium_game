// ========== Decoration.h ==========
#pragma once
#include "Entity.h"

enum class DecorationType {
    PLANT,
    ROCK,
    CASTLE
};

class Decoration : public Entity {
public:
    Decoration(DecorationType type, const Vector2D& position);
    ~Decoration() override = default;
    
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    
    DecorationType getDecorationType() const { return m_decorationType; }
    
private:
    DecorationType m_decorationType;
    float m_width;
    float m_height;
    SDL_Color m_color;
};