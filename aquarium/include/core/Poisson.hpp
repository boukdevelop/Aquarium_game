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
    std::string nom; // Pour voir ce qui se passe
    int cooldownReproduction;

    // Modifie le constructeur pour initialiser le cooldown à 0
    Poisson(int px, int py, Sexe s, std::string n = "Nemo")
        : Entity(px, py, EntityType::POISSON), sexe(s), nom(n), cooldownReproduction(0)
    {
        this->pv = 20;
    }

    // Implémentation de la logique spécifique au poisson
    void update(Aquarium &aquarium) override;

    // Méthodes spécifiques (à implementer dans le .cpp)
    void seDeplacer(Aquarium &aquarium);
    void manger(Aquarium &aquarium);
    void seReproduire(Aquarium &aquarium);
};

#endif