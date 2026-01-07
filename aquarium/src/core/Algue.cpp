#include "../../include/core/Algue.hpp"
#include "../../include/core/Aquarium.hpp"
#include <cstdlib> // Pour rand()

void Algue::update(Aquarium &aquarium)
{
    // 1. Vieillissement
    age++;

    // 2. Photosynthèse (Gagne de la vie à chaque tour)
    photosynthese();

    // 3. Gestion de la mort (si trop vieille ou plus de PV)
    if (pv <= 0 || age > 20)
    {
        isDead = true;
        return;
    }

    // 4. Reproduction (Si assez de PV et un peu de chance)
    // On tire un nombre entre 0 et 9, si < 2 (20% de chance), elle essaie
    if (pv > 15 && (rand() % 10 < 2))
    {
        seReproduire(aquarium);
    }
}

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

            // Vérifie si la case est valide et vide
            if (targetX >= 0 && targetX < Aquarium::WIDTH &&
                targetY >= 0 && targetY < Aquarium::HEIGHT)
            {

                if (aquarium.getEntityAt(targetX, targetY) == nullptr)
                {
                    // Création d'une nouvelle algue
                    // On perd la moitié de ses PV pour créer un enfant
                    Entity *bebe = new Algue(targetX, targetY);
                    if (aquarium.ajouterEntity(bebe))
                    {
                        this->pv /= 2;
                        return; // On ne fait qu'un bébé à la fois
                    }
                    else
                    {
                        delete bebe; // Sécurité si l'ajout a échoué
                    }
                }
            }
        }
    }
}