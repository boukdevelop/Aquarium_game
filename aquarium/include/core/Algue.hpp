#ifndef ALGUE_HPP
#define ALGUE_HPP

#include "Entity.hpp"

class Algue : public Entity
{
public:
    // Constructeur
    // Une algue commence avec 10 PV et une position donnée
    Algue(int px, int py) : Entity(px, py, EntityType::ALGUE)
    {
        this->pv = 10;
    }

    // Destructeur
    virtual ~Algue() = default;

    // Implémentation obligatoire de la méthode update de Entity
    // C'est ici qu'on définit ce que fait l'algue à chaque tour
    void update(Aquarium &aquarium) override;

    // Méthodes spécifiques à l'algue
    // L'algue gagne de la vie ou de l'énergie
    void photosynthese();

    // L'algue tente de créer une nouvelle algue sur une case adjacente
    void seReproduire(Aquarium &aquarium);
};

#endif