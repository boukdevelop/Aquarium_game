# 🐟 Projet Aquarium - Simulation de l'intégralité d'un Aquarium

Ce projet est une simulation de l'ecosysteme d'un ocean ou d'un aquarium simple réalisée en **C++** utilisant la bibliothèque **SDL3** pour le rendu graphique et **Dear ImGui** pour l'interface de contrôle.

Il a été réalisé dans le cadre académique par l'étudiant **BOUKALA BONOKO FRANCK GABRIEL**.

## 📋 Fonctionnalités

### ⚙ Fonctionnalités Principales (Grille 4x4)

*   **Système Vivant :** Une simulation de la vie d'un **Poissons** (Mâles/Femelles) et d'**Algues**.
*   **Déplacement :** Les poissons se déplacent aléatoirement dans l'aquarium et de façon non controlée.
*   **Cycle de vie :**
    *   Faim : Lorsqu'un poisson a faim, il perd des Point de vie et pour en recupérer il mange des algues, afin d'avoir de l'énergie.
    *   Vieillissement et Mort.
    *   **Reproduction sexueé** : Pour se reproduire, un mal et une femelle doivent se rencontrer et de cette rencontre ressort donc un bébé poisson en fonction de leur énergie avec conditions (énergie, cooldown).
*   **Algues :** Les algues reçoivent de l'énergie directement du soleil et se reproduisent avant de mourrir.

### ⚡ Fonctionnalités Secondaires & Gestion

*   **Interface Graphique (ImGui) :**
    *   Suivi du nombre de poissons/algues en temps réel.
    *   Bouton **"Nourrir"** Ce bouton permet de soigner les différentes entités présentes dans l'aquarium.
    *   Bouton **"Nettoyer"** Cette foncationnalité permet de nettoyer l'aquarium et d'y retirer toutes les saletés qui y sont presentes.
    *   Bouton **"Réinitialiser"** Cette fonctionnalité relance le jeu à Zéro.
*   **Saleté :** L'eau se trouble avec le temps (filtre visuel vert), affectant la santé des poissons.
*   **Contrôles Clavier :**
    *   `N` : Nettoyer l'aquarium.
    *   `Q` : Quitter l'application.

## 🛠 Technologies Utilisées

*   **Langage :** C++ (Standard C++17 recommandé)
*   **Graphisme :** [SDL3](https://github.com/libsdl-org/SDL) (Utilisation de `SDL_Renderer`, pas d'OpenGL direct).
*   **Interface :** [Dear ImGui](https://github.com/ocornut/imgui).

## 📂 Architecture du Projet

Le projet respecte une séparation stricte entre la logique (`core`) et l'affichage (`Graphics`).

```text
ProjetAquarium/
│   README.md           <-- Ce fichier
│   main.cpp            <-- Point d'entrée
│   generate_assets.py  <-- Script pour créer les images
│
├───assets/             <-- Images (fish.bmp, algae.bmp...)
├───build/              <-- Exécutable final
├───include/
│   ├───core/           <-- En-têtes logique (Aquarium, Poisson...)
│   └───Graphics/       <-- En-têtes graphique (Window, Renderer...)
├───src/
│   ├───core/           <-- Sources logique
│   └───Graphics/       <-- Sources graphique
└───libs/               <-- Bibliothèques externes (SDL3, ImGui)
```

## 🚀 Installation et Compilation

### Prérequis
*   Un compilateur C++ (g++ via MinGW recommandé sous Windows).
*   Les bibliothèques SDL3 installées dans le dossier `libs/`.

### 1. Génération des Assets (Images)

Toutes les images ont été dessinées à la main

### 2. Compilation (Ligne de commande)
Ouvrez un terminal à la racine du projet et lancez cette commande pour compiler :

```bash
mkdir build
g++ main.cpp src/core/*.cpp src/Graphics/*.cpp libs/Imgui/*.cpp libs/Imgui/backends/imgui_impl_sdl3.cpp libs/Imgui/backends/imgui_impl_sdlrenderer3.cpp -o buid/mon_aquarium.exe -I include -I libs/SDL3/include -I libs/Imgui -I libs/Imgui/backends -L libs/SDL3/lib -lSDL3
```

### 3. Exécution
Avant de lancer le jeu, assurez-vous que les fichiers suivants sont présents dans le dossier `build/` :
1.  `mon_aquarium.exe` (généré par la compilation).
2.  `SDL3.dll` (copié depuis `libs/SDL3/lib/`).
3.  Le dossier `assets/` (copié depuis la racine).

Ensuite, double-cliquez sur l'exécutable ou lancez :
```bash
./build/mon_aquarium.exe
```

## 🎮 Contrôles

*   **Souris :** Interagir avec le panneau de contrôle (Nourrir, Reset, etc.).
*   **Touche N :** Nettoyer l'aquarium instantanément.
*   **Touche Q :** Quitter la simulation.

---

*Ce document a été réalisé avec ❤️ par BOUKALA BONOKO FRANCK GABRIEL.*

```
