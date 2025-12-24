# 📋 Checklist complète des fichiers du projet

## ✅ Fichiers à créer

### 📁 Racine du projet
- [ ] `CMakeLists.txt`
- [ ] `README.md`
- [ ] `setup.sh` (optionnel, pour Linux/Mac)

### 📁 src/
- [ ] `main.cpp`

### 📁 src/core/
- [ ] `Game.h`
- [ ] `Game.cpp`
- [ ] `Window.h`
- [ ] `Window.cpp`
- [ ] `Renderer.h`
- [ ] `Renderer.cpp`
- [ ] `InputManager.h`
- [ ] `InputManager.cpp`
- [ ] `TimeManager.h`
- [ ] `TimeManager.cpp`

### 📁 src/entities/
- [ ] `Entity.h`
- [ ] `Entity.cpp`
- [ ] `Fish.h`
- [ ] `Fish.cpp`
- [ ] `Food.h`
- [ ] `Food.cpp`
- [ ] `Decoration.h`
- [ ] `Decoration.cpp`

### 📁 src/systems/
- [ ] `FishBehavior.h`
- [ ] `FishBehavior.cpp`
- [ ] `FeedingSystem.h`
- [ ] `FeedingSystem.cpp`
- [ ] `CollisionSystem.h`
- [ ] `CollisionSystem.cpp`
- [ ] `ParticleSystem.h`
- [ ] `ParticleSystem.cpp`

### 📁 src/managers/
- [ ] `EntityManager.h`
- [ ] `EntityManager.cpp`
- [ ] `ResourceManager.h`
- [ ] `ResourceManager.cpp`
- [ ] `AquariumManager.h`
- [ ] `AquariumManager.cpp`

### 📁 src/ui/
- [ ] `ImGuiManager.h`
- [ ] `ImGuiManager.cpp`
- [ ] `ShopUI.h`
- [ ] `ShopUI.cpp`
- [ ] `StatsPanel.h`
- [ ] `StatsPanel.cpp`
- [ ] `DebugWindow.h`
- [ ] `DebugWindow.cpp`

### 📁 src/utils/
- [ ] `Vector2D.h`
- [ ] `Vector2D.cpp`
- [ ] `Math.h`
- [ ] `Math.cpp`
- [ ] `Config.h`

### 📁 external/
- [ ] `imgui/` (cloner depuis GitHub)
  - [ ] Vérifier la présence de `imgui.h`, `imgui.cpp`, etc.
  - [ ] Vérifier la présence du dossier `backends/`

### 📁 assets/
- [ ] `textures/` (vide pour l'instant)
- [ ] `fonts/` (vide pour l'instant)
- [ ] `sounds/` (vide pour l'instant)

## 📊 Statistiques du projet

- **Nombre total de fichiers** : ~50 fichiers
- **Fichiers headers (.h)** : 25
- **Fichiers implémentation (.cpp)** : 24
- **Fichiers de configuration** : 3

## 🔍 Vérification de l'arborescence

Commande pour vérifier la structure :

```bash
tree -L 3 AquariumSimulator/
```

Résultat attendu :
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

## 🚀 Ordre de création recommandé

### Étape 1 : Configuration de base
1. Créer l'arborescence des dossiers
2. Copier ImGui dans `external/imgui/`
3. Créer `CMakeLists.txt`

### Étape 2 : Utilitaires
4. `src/utils/Config.h`
5. `src/utils/Vector2D.h` et `.cpp`
6. `src/utils/Math.h` et `.cpp`

### Étape 3 : Entités de base
7. `src/entities/Entity.h` et `.cpp`
8. `src/entities/Fish.h` et `.cpp`
9. `src/entities/Food.h` et `.cpp`
10. `src/entities/Decoration.h` et `.cpp`

### Étape 4 : Systèmes
11. `src/systems/CollisionSystem.h` et `.cpp`
12. `src/systems/FishBehavior.h` et `.cpp`
13. `src/systems/FeedingSystem.h` et `.cpp`
14. `src/systems/ParticleSystem.h` et `.cpp`

### Étape 5 : Managers
15. `src/managers/EntityManager.h` et `.cpp`
16. `src/managers/ResourceManager.h` et `.cpp`
17. `src/managers/AquariumManager.h` et `.cpp`

### Étape 6 : Interface ImGui
18. `src/ui/ImGuiManager.h` et `.cpp`
19. `src/ui/StatsPanel.h` et `.cpp`
20. `src/ui/ShopUI.h` et `.cpp`
21. `src/ui/DebugWindow.h` et `.cpp`

### Étape 7 : Core du jeu
22. `src/core/TimeManager.h` et `.cpp`
23. `src/core/InputManager.h` et `.cpp`
24. `src/core/Window.h` et `.cpp`
25. `src/core/Renderer.h` et `.cpp`
26. `src/core/Game.h` et `.cpp`

### Étape 8 : Point d'entrée
27. `src/main.cpp`

### Étape 9 : Documentation
28. `README.md`
29. `setup.sh` (optionnel)

## 🔨 Commandes de compilation

```bash
# À la racine du projet
mkdir build && cd build
cmake ..
cmake --build . -j4

# Lancer le jeu
./AquariumSimulator
```

## ✅ Tests de validation

Après la compilation, on vérifiera que :
- [ ] Le jeu se lance sans erreur
- [ ] La fenêtre s'affiche correctement
- [ ] Les poissons nagent
- [ ] Le clic gauche ajoute de la nourriture
- [ ] TAB ouvre la boutique
- [ ] Les achats fonctionnent
- [ ] Le panneau de stats s'affiche
- [ ] D ouvre la fenêtre de debug
- [ ] SPACE met en pause
- [ ] ESC quitte le jeu

## 🐛 Problèmes courants

### Erreur de compilation avec ImGui
**Solution** : Vérifiez que tous les fichiers ImGui sont présents dans `external/imgui/`

### Erreur "SDL3 not found"

**Solution** :

```bash
export CMAKE_PREFIX_PATH=/usr/local
cmake ..
```

### Erreur de linkage
**Solution** : Vérifiez que tous les `.cpp` sont listés dans `CMakeLists.txt`

### Warnings sur les conversions
**Solution** : Ajoutez des casts explicites ou désactivez les warnings :
```cmake
target_compile_options(AquariumSimulator PRIVATE -Wno-conversion)
```

## 📝 Notes importantes

1. **Ordre d'inclusion** : Toujours inclure les headers SDL3 avant ImGui
2. **Namespaces** : Pas de `using namespace` dans les headers
3. **Forward declarations** : Utilisez-les pour réduire les dépendances
4. **RAII** : Utilisez toujours RAII pour la gestion mémoire
5. **Const correctness** : Marquez les méthodes const quand approprié

## 🎯 Prochaines étapes après compilation

1. Tester toutes les fonctionnalités
2. Ajuster les paramètres dans `Config.h`
3. Ajouter des textures dans `assets/textures/`
4. Implémenter la sauvegarde/chargement
5. Ajouter plus de types de poissons
6. Créer un système de niveaux

---