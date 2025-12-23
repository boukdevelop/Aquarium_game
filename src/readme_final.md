# 🐠 Aquarium Simulator

Un simulateur d'aquarium interactif développé en C++ avec SDL3 et ImGui.

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![C++](https://img.shields.io/badge/C++-17-green)
![SDL3](https://img.shields.io/badge/SDL-3.0-red)
![ImGui](https://img.shields.io/badge/ImGui-1.90-orange)

## 📋 Caractéristiques

### Fonctionnalités actuelles

- ✅ **Poissons avec IA** : Comportement de flocking (cohésion, séparation, alignement)
- ✅ **Système de nourrissage** : Nourriture qui tombe et poissons affamés
- ✅ **Décorations** : Plantes, rochers, châteaux
- ✅ **Économie** : Système d'argent et boutique
- ✅ **Particules** : Bulles d'air animées
- ✅ **Interface ImGui** : Boutique, statistiques, debug
- ✅ **Revenu passif** : Gagnez de l'argent avec vos poissons

### Améliorations futures possibles

- 🔄 Sauvegarde/Chargement
- 🔄 Niveaux d'expérience
- 🔄 Plus de types de poissons
- 🔄 Événements aléatoires
- 🔄 Système de reproduction
- 🔄 Maladies et soins
- 🔄 Aquariums multiples
- 🔄 Graphismes améliorés avec textures

## 🛠️ Installation

### Prérequis

- **Compilateur C++17** : GCC 7+, Clang 5+, ou MSVC 2017+
- **CMake 3.15+**
- **SDL3** (voir instructions ci-dessous)
- **Git**

### Installer SDL3

#### Linux (Ubuntu/Debian)

```bash
# Installer les dépendances
sudo apt-get update
sudo apt-get install build-essential cmake git

# Cloner et compiler SDL3
git clone https://github.com/libsdl-org/SDL.git
cd SDL
git checkout main
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
sudo cmake --install .
```

#### macOS

```bash
# Installer Homebrew si nécessaire
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Installer les dépendances
brew install cmake git

# Cloner et compiler SDL3
git clone https://github.com/libsdl-org/SDL.git
cd SDL
git checkout main
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.ncpu)
sudo cmake --install .
```

#### Windows

```powershell
# Télécharger SDL3 depuis GitHub
git clone https://github.com/libsdl-org/SDL.git
cd SDL
git checkout main
mkdir build
cd build

# Compiler avec Visual Studio
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
cmake --install . --prefix "C:/SDL3"
```

### Installer ImGui

```bash
# Dans le dossier du projet
mkdir -p external
cd external
git clone https://github.com/ocornut/imgui.git
```

### Compiler le projet

```bash
# Cloner le projet (ou créer les fichiers manuellement)
git clone https://github.com/votre-repo/AquariumSimulator.git
cd AquariumSimulator

# Copier ImGui dans external/ (si pas déjà fait)
# Voir section précédente

# Créer le dossier de build
mkdir build && cd build

# Générer et compiler
cmake ..
cmake --build . -j$(nproc)  # Linux/Mac
# ou
cmake --build . --config Release  # Windows

# Lancer le jeu
./AquariumSimulator  # Linux/Mac
# ou
.\Release\AquariumSimulator.exe  # Windows
```

## 🎮 Contrôles

### Souris

- **Clic gauche** : Ajouter de la nourriture dans l'aquarium
- **Clic gauche (après achat)** : Placer un poisson ou une décoration
- **Clic droit** : Annuler le placement

### Clavier

- **TAB** : Ouvrir/Fermer la boutique
- **D** : Ouvrir/Fermer la fenêtre de debug
- **SPACE** : Mettre en pause
- **ESC** : Quitter le jeu

### Interface

- Panneau de statistiques (toujours visible en haut à gauche)
- Boutique (TAB pour ouvrir)
- Fenêtre de debug (D pour ouvrir)

## 📁 Structure du projet

```
AquariumSimulator/
├── src/
│   ├── main.cpp                    # Point d'entrée
│   ├── core/                       # Systèmes de base
│   │   ├── Game.cpp/h             # Boucle principale
│   │   ├── Window.cpp/h           # Gestion fenêtre
│   │   ├── Renderer.cpp/h         # Gestion rendu
│   │   ├── InputManager.cpp/h     # Gestion entrées
│   │   └── TimeManager.cpp/h      # Gestion du temps
│   ├── entities/                   # Entités du jeu
│   │   ├── Entity.cpp/h           # Classe de base
│   │   ├── Fish.cpp/h             # Poissons
│   │   ├── Food.cpp/h             # Nourriture
│   │   └── Decoration.cpp/h       # Décorations
│   ├── systems/                    # Systèmes de gameplay
│   │   ├── FishBehavior.cpp/h     # IA des poissons
│   │   ├── FeedingSystem.cpp/h    # Système nourrissage
│   │   ├── CollisionSystem.cpp/h  # Détection collisions
│   │   └── ParticleSystem.cpp/h   # Système particules
│   ├── managers/                   # Gestionnaires
│   │   ├── EntityManager.cpp/h    # Gestion entités
│   │   ├── ResourceManager.cpp/h  # Gestion ressources
│   │   └── AquariumManager.cpp/h  # Manager principal
│   ├── ui/                         # Interface utilisateur
│   │   ├── ImGuiManager.cpp/h     # Gestionnaire ImGui
│   │   ├── ShopUI.cpp/h           # Interface boutique
│   │   ├── StatsPanel.cpp/h       # Panneau stats
│   │   └── DebugWindow.cpp/h      # Fenêtre debug
│   └── utils/                      # Utilitaires
│       ├── Vector2D.cpp/h         # Vecteurs 2D
│       ├── Math.cpp/h             # Fonctions math
│       └── Config.h               # Configuration
├── external/
│   └── imgui/                      # Bibliothèque ImGui
├── assets/
│   ├── textures/                   # Images (à ajouter)
│   ├── fonts/                      # Polices (à ajouter)
│   └── sounds/                     # Sons (à ajouter)
├── CMakeLists.txt
└── README.md
```

## 🎨 Personnalisation

### Modifier les paramètres

Tous les paramètres du jeu sont dans `src/utils/Config.h` :

```cpp
// Vitesse des poissons
constexpr float FISH_MAX_SPEED = 100.0f;

// Prix dans la boutique
constexpr int GOLDFISH_PRICE = 10;

// Taux de faim
constexpr float FISH_HUNGER_RATE = 5.0f;
```

### Ajouter un nouveau type de poisson

1. Ajouter dans `src/entities/Fish.h` :

```cpp
enum class FishType {
    GOLDFISH,
    CLOWNFISH,
    ANGELFISH,
    SHARK  // ← Nouveau type
};
```

2. Implémenter dans `Fish.cpp` :

```cpp
case FishType::SHARK:
    m_color = {128, 128, 128, 255};
    m_size = 50.0f;
    m_maxSpeed = 150.0f;
    break;
```

3. Ajouter dans la boutique (`ShopUI.cpp`)

### Utiliser des textures

1. Placez vos images dans `assets/textures/`
2. Chargez-les avec le ResourceManager :

```cpp
SDL_Texture* fishTexture = 
    ResourceManager::getInstance().loadTexture("assets/textures/fish.bmp");
```

## 🐛 Dépannage

### Erreur : SDL3 non trouvé

```bash
export CMAKE_PREFIX_PATH=/usr/local
# Puis recompiler
```

### Erreur : ImGui introuvable

Vérifiez que `external/imgui/` contient bien tous les fichiers ImGui.

### Performance faible

- Compilez en mode Release : `cmake .. -DCMAKE_BUILD_TYPE=Release`
- Réduisez le nombre de poissons
- Ajustez les paramètres dans Config.h

### Crash au démarrage

- Vérifiez que SDL3 est bien installé
- Sur Windows, assurez-vous que SDL3.dll est dans le même dossier que l'exe

## 🚀 Améliorations suggérées

### Court terme

1. **Textures** : Remplacer les formes simples par des sprites
2. **Sons** : Ajouter des effets sonores (bulles, éclaboussures)
3. **Sauvegarde** : Implémenter save/load avec JSON

### Moyen terme

1. **Plus de poissons** : Requins, tortues, méduses
2. **Éclairage** : Effets de lumière dynamiques
3. **Quêtes** : Système d'objectifs quotidiens

### Long terme

1. **Multijoueur** : Visitez les aquariums d'autres joueurs
2. **Mod support** : Permettre l'ajout de contenu personnalisé
3. **Mode VR** : Immersion totale dans l'aquarium

## 📚 Ressources utilisées

- **SDL3** : https://github.com/libsdl-org/SDL
- **ImGui** : https://github.com/ocornut/imgui
- **Boids Algorithm** : http://www.red3d.com/cwr/boids/
- **C++ Best Practices** : https://isocpp.github.io/CppCoreGuidelines/

## 📝 Licence

Ce projet est sous licence MIT. Libre d'utilisation, modification et distribution.

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :

- Signaler des bugs
- Proposer de nouvelles fonctionnalités
- Soumettre des pull requests
- Améliorer la documentation

## 👨‍💻 Auteur

Créé avec ❤️ pour apprendre SDL3, ImGui et le développement de jeux en C++.

---

**Bon développement et amusez-vous bien ! 🐠🎮**