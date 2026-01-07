#include "../../include/core/Algue.hpp"
#include "../../include/core/Aquarium.hpp"
#include <cstdlib> // Pour rand()

void Algue::update(Aquarium &aquarium)
{
    // 1. Vieillissement
    age++;

    // 2. Photosynthèse
    photosynthese();

    // 3. Gestion de la mort (si trop vieille ou plus de PV)
    // On garde 60 pour qu'elle vive longtemps
    if (pv <= 0 || age > 60)
    {
        isDead = true;
        return;
    }

    // 4. Reproduction
    // On garde ta nouvelle logique (plus de chance : 40%)
    if (pv > 10 && (rand() % 10 < 4))
    {
        seReproduire(aquarium);
    }
}
// <--- ICI la fonction update est finie.
// Le code qui provoquait l'erreur était ici. Je l'ai supprimé.

void Algue::photosynthese()
{
    // Gagne 1 PV par tour, max 20
    if (pv < 20)
    {
        pv += 1;
    }
}

void Algue::seReproduire(Aquarium &aquarium)
{
    // Cherche une case libre autour
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue; // On ne teste pas sa propre case

            int targetX = x + dx;
            int targetY = y + dy;

            // Vérifie si la case est valide
            if (targetX >= 0 && targetX < Aquarium::WIDTH &&
                targetY >= 0 && targetY < Aquarium::HEIGHT)
            {
                // Vérifie si la case est vide
                if (aquarium.getEntityAt(targetX, targetY) == nullptr)
                {
                    // Création d'une nouvelle algue
                    Entity *bebe = new Algue(targetX, targetY);

                    if (aquarium.ajouterEntity(bebe))
                    {
                        this->pv /= 2; // Coût de reproduction
                        return;        // On ne fait qu'un bébé à la fois
                    }
                    else
                    {
                        delete bebe; // Sécurité
                    }
                }
            }
        }
    }
}