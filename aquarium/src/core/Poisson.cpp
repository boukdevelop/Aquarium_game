#include "../../include/core/Poisson.hpp"
#include "../../include/core/Aquarium.hpp"
#include "../../include/core/Algue.hpp"
#include <cstdlib> // Pour rand()

void Poisson::update(Aquarium &aquarium)
{
    age++;
    pv--; // Le poisson a faim à chaque tour !

    // Influence de la saleté sur la vie
    if (aquarium.getSalete() > 50.0f)
    {
        pv--; // Perd un PV supplémentaire si c'est sale
    }

    if (pv <= 0 || age > 40)
    { // Meurt de faim ou de vieillesse
        isDead = true;
        return;
    }

    // Actions principales
    manger(aquarium);       // Essaie de manger d'abord
    seReproduire(aquarium); // Essaie de se reproduire
    seDeplacer(aquarium);   // Bouge ensuite
}

void Poisson::manger(Aquarium &aquarium)
{
    // Regarde autour de lui s'il y a une algue
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int targetX = x + dx;
            int targetY = y + dy;

            // Vérification des bornes
            if (targetX >= 0 && targetX < Aquarium::WIDTH &&
                targetY >= 0 && targetY < Aquarium::HEIGHT)
            {

                Entity *cible = aquarium.getEntityAt(targetX, targetY);

                // Si c'est une algue, on mange !
                if (cible != nullptr && cible->type == EntityType::ALGUE)
                {
                    pv += 5;              // Miam
                    cible->isDead = true; // L'algue est mangée
                    cible->pv = 0;
                    return; // On mange une seule chose par tour
                }
            }
        }
    }
}

void Poisson::seDeplacer(Aquarium &aquarium)
{
    // Mouvement aléatoire simple
    int dx = (rand() % 3) - 1; // -1, 0, 1
    int dy = (rand() % 3) - 1;

    int newX = x + dx;
    int newY = y + dy;

    // Vérifie bornes
    if (newX >= 0 && newX < Aquarium::WIDTH &&
        newY >= 0 && newY < Aquarium::HEIGHT)
    {

        // On ne bouge que si la case est vide
        if (aquarium.getEntityAt(newX, newY) == nullptr)
        {
            // Mise à jour de la grille dans l'aquarium (manuellement ici pour simplifier)
            // Idéalement l'aquarium devrait avoir une méthode moveEntity()
            // Pour l'instant, on change juste les coordonnées, l'Aquarium mettra à jour sa grille au prochain tour

            // Note: Pour une grille stricte, il faut prévenir l'aquarium :
            // Cette partie est délicate sans méthode moveEntity dans Aquarium,
            // mais l'Aquarium reconstruit souvent sa grille basée sur les coord x,y
            x = newX;
            y = newY;
        }
    }
}

void Poisson::seReproduire(Aquarium &aquarium)
{
    // Si pas assez d'énergie, pas de reproduction
    if (pv < 10)
        return;

    // Cherche un partenaire
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            Entity *voisin = aquarium.getEntityAt(x + dx, y + dy);

            if (voisin != nullptr && voisin->type == EntityType::POISSON)
            {
                Poisson *partenaire = static_cast<Poisson *>(voisin);

                // Si sexes opposés
                if (partenaire->sexe != this->sexe)
                {
                    // Trouver une case vide pour le bébé (simplifié : n'importe où dans l'aquarium pour l'instant
                    // ou juste à côté si possible).
                    // Pour simplifier ici : on ne crée le bébé que s'il y a une case libre adjacente
                    // ... (logique de placement similaire à l'algue)

                    // On coupe court pour l'exemple :
                    // Creation bébé aléatoire
                    Sexe sexeBebe = (rand() % 2 == 0) ? Sexe::MALE : Sexe::FEMELLE;

                    // On cherche une case vide aléatoire pour le spawn (simplification grille 4x4)
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (aquarium.getEntityAt(i, j) == nullptr)
                            {
                                Poisson *bebe = new Poisson(i, j, sexeBebe, "Bebe");
                                aquarium.ajouterEntity(bebe);
                                this->pv -= 5; // Coût énergétique
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}