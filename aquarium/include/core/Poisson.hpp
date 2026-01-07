#ifndef POISSON_HPP
#define POISSON_HPP

#include "Entity.hpp"
#include <string>

// Enum pour le sexe
enum class Sexe
{
    MALE,
    FEMELLE
};

class Poisson : public Entity
{
public:
    Sexe sexe;
    std::string nom; // Juste pour le fun ou le debug

    // Constructeur
    Poisson(int px, int py, Sexe s, std::string n = "Nemo")
        : Entity(px, py, EntityType::POISSON), sexe(s), nom(n)
    {
        this->pv = 20; // Un poisson commence avec plus de vie qu'une algue
    }

    // Implémentation de la logique spécifique au poisson
    void update(Aquarium &aquarium) override;

    // Méthodes spécifiques (qu'on implémentera dans le .cpp)
    void seDeplacer(Aquarium &aquarium);
    void manger(Aquarium &aquarium);
    void seReproduire(Aquarium &aquarium);
};

#endif