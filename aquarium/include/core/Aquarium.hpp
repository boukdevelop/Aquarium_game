#ifndef AQUARIUM_HPP
#define AQUARIUM_HPP

#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "Poisson.hpp"
#include "Algue.hpp"
// Tu ajouteras #include "Algue.hpp" quand on le créera

class Aquarium
{
public:
    // Constantes de la grille (4x4 comme demandé)
    static const int WIDTH = 4;
    static const int HEIGHT = 4;

private:
    // La grille contient des pointeurs vers les entités (ou nullptr si vide)
    Entity *grille[WIDTH][HEIGHT];

    // Liste pour itérer facilement sans parcourir toute la grille vide
    std::vector<Entity *> entities;

    // Gestion de la saleté (Fonctionnalité secondaire)
    float niveauSalete;

public:
    // Constructeur et Destructeur
    Aquarium();
    ~Aquarium();

    // Méthodes principales
    void update();      // Appelé chaque seconde : fait vivre l'aquarium
    void nettoyer();    // Remet la saleté à 0
    void reset();       // Vide tout et remet à zéro
    void initialiser(); // Ajoute Nemo, Dory et les algues de base

    // Gestion des entités
    bool ajouterEntity(Entity *entity); // Retourne false si la case est occupée
    void supprimerEntity(Entity *entity);

    // Getters pour l'interface graphique (ImGui/SDL)
    Entity *getEntityAt(int x, int y) const;
    float getSalete() const { return niveauSalete; }
    int getNombrePoissons() const;
    int getNombreAlgues() const;
};

#endif