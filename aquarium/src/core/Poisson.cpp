#include "../../include/core/Poisson.hpp"
#include "../../include/core/Aquarium.hpp"
#include "../../include/core/Algue.hpp"
#include <cstdlib> // Pour rand()

void Poisson::update(Aquarium &aquarium)
{
    age++;
    pv--; // Le poisson a faim à chaque tour !

    // GESTION DU COOLDOWN
    if (cooldownReproduction > 0)
    {
        cooldownReproduction--;
    }

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
    // 1. VERIFICATION STRICTE
    // Il faut 10 PV, mais aussi que le cooldown soit à 0
    if (pv < 10 || cooldownReproduction > 0)
        return;

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

                // Si sexes opposés ET que le partenaire est aussi dispo (optionnel mais mieux)
                if (partenaire->sexe != this->sexe)
                {

                    // CHANCE DE REPRODUCTION (Pas automatique !)
                    // 1 chance sur 4 seulement si ils se rencontrent
                    if (rand() % 4 != 0)
                        return;

                    Sexe sexeBebe = (rand() % 2 == 0) ? Sexe::MALE : Sexe::FEMELLE;

                    // Chercher case vide pour le bébé
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            if (aquarium.getEntityAt(i, j) == nullptr)
                            {
                                Poisson *bebe = new Poisson(i, j, sexeBebe, "Bebe");
                                if (aquarium.ajouterEntity(bebe))
                                {
                                    // SUCCES :
                                    // 1. On perd de l'énergie
                                    this->pv -= 10;
                                    // 2. On active le cooldown (attendre 10 tours avant de recommencer)
                                    this->cooldownReproduction = 10;
                                    // 3. Le partenaire aussi est fatigué (optionnel)
                                    partenaire->cooldownReproduction = 10;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}