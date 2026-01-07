#ifndef ENTITY_HPP
#define ENTITY_HPP

// On utilise une énumération pour savoir si c'est un poisson ou une algue
enum class EntityType
{
    POISSON,
    ALGUE
};

// Forward declaration (on dit que la classe Aquarium existe, on verra les détails plus tard)
class Aquarium;

class Entity
{
public:
    int x, y;        // Position sur la grille (0-3)
    int age;         // Âge en tours
    int pv;          // Points de vie / Energie
    EntityType type; // POISSON ou ALGUE
    bool isDead;     // Si true, l'aquarium devra le supprimer

    Entity(int startX, int startY, EntityType t)
        : x(startX), y(startY), age(0), pv(10), type(t), isDead(false) {}

    virtual ~Entity() = default;

    // Méthode virtuelle pure : chaque enfant DOIT définir son comportement
    // On passe une référence à l'aquarium pour que l'entité puisse "voir" autour d'elle
    virtual void update(Aquarium &aquarium) = 0;
};

#endif