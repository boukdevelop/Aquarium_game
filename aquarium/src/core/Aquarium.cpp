#include "../../include/core/Aquarium.hpp"
#include <algorithm> // Pour std::remove_if

Aquarium::Aquarium() : niveauSalete(0.0f)
{
    // Initialiser la grille à vide
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            grille[i][j] = nullptr;
        }
    }
}

Aquarium::~Aquarium()
{
    // Nettoyage de la mémoire
    for (Entity *e : entities)
    {
        delete e;
    }
    entities.clear();
}

bool Aquarium::ajouterEntity(Entity *entity)
{
    if (entity == nullptr)
        return false;

    // Vérifie les bornes
    if (entity->x < 0 || entity->x >= WIDTH || entity->y < 0 || entity->y >= HEIGHT)
    {
        return false;
    }

    // Vérifie si la case est occupée
    if (grille[entity->x][entity->y] != nullptr)
    {
        return false;
    }

    // Ajout
    entities.push_back(entity);
    grille[entity->x][entity->y] = entity;
    return true;
}

Entity *Aquarium::getEntityAt(int x, int y) const
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return nullptr;
    return grille[x][y];
}

void Aquarium::nettoyer()
{
    niveauSalete = 0.0f;
}

void Aquarium::update()
{
    // 1. Augmenter la saleté
    niveauSalete += 1.5f;

    // 2. Mise à jour des entités (bouger, manger, etc.)
    // On utilise un index car la liste peut grandir (naissances) pendant la boucle
    size_t nbEntitiesInitial = entities.size();
    for (size_t i = 0; i < nbEntitiesInitial; ++i)
    {
        if (!entities[i]->isDead)
        {
            // Avant update : on enlève de la grille (pour permettre le mouvement)
            grille[entities[i]->x][entities[i]->y] = nullptr;

            entities[i]->update(*this);

            // Après update : on remet dans la grille aux nouvelles coordonnées
            // Si le poisson est mort pendant l'update, on ne le remet pas
            if (!entities[i]->isDead)
            {
                // Petit check de sécurité collision (si deux poissons ont sauté sur la même case)
                // Dans une simulation simple tour par tour, le premier arrivé gagne
                if (grille[entities[i]->x][entities[i]->y] == nullptr)
                {
                    grille[entities[i]->x][entities[i]->y] = entities[i];
                }
                else
                {
                    // Conflit : retour à la case départ ou mort ?
                    // Simplification : le poisson meurt écrasé (ou annuler mouvement)
                    entities[i]->isDead = true;
                }
            }
        }
    }

    // 3. Supprimer les morts
    // Utilisation de l'idiome erase-remove
    auto it = std::remove_if(entities.begin(), entities.end(), [](Entity *e)
                             {
        if (e->isDead) {
            delete e; // Libère la mémoire
            return true;
        }
        return false; });
    entities.erase(it, entities.end());

    // Reconstruction propre de la grille (sécurité)
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
            grille[i][j] = nullptr;

    for (Entity *e : entities)
    {
        grille[e->x][e->y] = e;
    }
}

int Aquarium::getNombrePoissons() const
{
    int count = 0;
    for (Entity *e : entities)
    {
        if (e->type == EntityType::POISSON)
            count++;
    }
    return count;
}

int Aquarium::getNombreAlgues() const
{
    int count = 0;
    for (Entity *e : entities)
    {
        if (e->type == EntityType::ALGUE)
            count++;
    }
    return count;
}