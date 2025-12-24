#!/usr/bin/env python3
"""
Générateur automatique du projet Aquarium Simulator
Ce script crée toute la structure et tous les fichiers du projet
"""

import os
import shutil

def create_directory_structure():
    """Créer tous les dossiers nécessaires"""
    directories = [
        "AquariumSimulator",
        "AquariumSimulator/src",
        "AquariumSimulator/src/core",
        "AquariumSimulator/src/entities",
        "AquariumSimulator/src/systems",
        "AquariumSimulator/src/managers",
        "AquariumSimulator/src/ui",
        "AquariumSimulator/src/utils",
        "AquariumSimulator/external",
        "AquariumSimulator/assets",
        "AquariumSimulator/assets/textures",
        "AquariumSimulator/assets/textures/fish",
        "AquariumSimulator/assets/textures/decorations",
        "AquariumSimulator/assets/textures/ui",
        "AquariumSimulator/assets/textures/backgrounds",
        "AquariumSimulator/assets/fonts",
        "AquariumSimulator/assets/sounds",
        "AquariumSimulator/assets/sounds/sfx",
        "AquariumSimulator/assets/sounds/music",
        "AquariumSimulator/.vscode",
        "AquariumSimulator/.github",
        "AquariumSimulator/.github/ISSUE_TEMPLATE",
    ]
    
    for directory in directories:
        os.makedirs(directory, exist_ok=True)
        print(f"✓ Créé: {directory}")

def write_file(path, content):
    """Écrire un fichier avec son contenu"""
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"✓ Créé: {path}")

def create_files():
    """Créer tous les fichiers du projet"""
    
    # Je vais créer les fichiers les plus importants
    # Pour avoir TOUS les fichiers, utilisez les artifacts que j'ai créés précédemment
    
    files = {
        # CMakeLists.txt
        "AquariumSimulator/CMakeLists.txt": """cmake_minimum_required(VERSION 3.15)
project(AquariumSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(AquariumSimulator 
    ${SOURCES}
    ${IMGUI_SOURCES}
)

target_include_directories(AquariumSimulator PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(AquariumSimulator 
    PRIVATE SDL3::SDL3
)
""",

        # .gitignore
        "AquariumSimulator/.gitignore": """build/
cmake-build-*/
out/
.vscode/
.idea/
*.swp
*.swo
*~
.DS_Store
*.o
*.obj
*.exe
*.out
*.app
CMakeCache.txt
CMakeFiles/
external/SDL/
external/imgui/
""",

        # README.md principal
        "AquariumSimulator/README.md": """# 🐠 Aquarium Simulator

Simulateur d'aquarium interactif en C++ avec SDL3 et ImGui.

## 🚀 Installation Rapide

### Linux/Mac
```bash
chmod +x setup.sh && ./setup.sh
chmod +x build.sh && ./build.sh
./build/AquariumSimulator
```

### Windows
```bash
build.bat
.\\build\\Release\\AquariumSimulator.exe
```

## 📋 Prérequis

- C++17
- CMake 3.15+
- SDL3
- ImGui (inclus dans external/)

## 🎮 Contrôles

- **Clic gauche** : Ajouter nourriture
- **TAB** : Boutique
- **SPACE** : Pause
- **D** : Debug
- **ESC** : Quitter

## 📚 Documentation

- [Guide de démarrage rapide](QUICKSTART.md)
- [Architecture](ARCHITECTURE.md)
- [Contribution](CONTRIBUTING.md)
- [Roadmap](ROADMAP.md)

## 📝 Licence

MIT License - Voir [LICENSE](LICENSE)
""",

        # LICENSE
        "AquariumSimulator/LICENSE": """MIT License

Copyright (c) 2024 Aquarium Simulator Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
""",

        # Instructions importantes
        "AquariumSimulator/INSTRUCTIONS.txt": """╔══════════════════════════════════════════════════════════════╗
║         AQUARIUM SIMULATOR - INSTRUCTIONS                     ║
╚══════════════════════════════════════════════════════════════╝

📦 CONTENU DU PROJET
--------------------
Ce dossier contient la structure de base du projet Aquarium Simulator.

⚠️  FICHIERS MANQUANTS IMPORTANTS
----------------------------------
Pour que le projet soit COMPLET, vous devez ajouter les fichiers suivants
que j'ai créés dans les artifacts de notre conversation :

1. TOUS les fichiers .h et .cpp dans src/
   (Copiez-les depuis les artifacts de la conversation)

2. Télécharger ImGui :
   cd external
   git clone https://github.com/ocornut/imgui.git

3. Installer SDL3 :
   Suivez les instructions dans README.md

📋 LISTE DES FICHIERS À COPIER DEPUIS LES ARTIFACTS
----------------------------------------------------

src/
├── main.cpp
├── core/
│   ├── Game.h / Game.cpp
│   ├── Window.h / Window.cpp
│   ├── Renderer.h / Renderer.cpp
│   ├── InputManager.h / InputManager.cpp
│   └── TimeManager.h / TimeManager.cpp
├── entities/
│   ├── Entity.h / Entity.cpp
│   ├── Fish.h / Fish.cpp
│   ├── Food.h / Food.cpp
│   └── Decoration.h / Decoration.cpp
├── systems/
│   ├── FishBehavior.h / FishBehavior.cpp
│   ├── FeedingSystem.h / FeedingSystem.cpp
│   ├── CollisionSystem.h / CollisionSystem.cpp
│   └── ParticleSystem.h / ParticleSystem.cpp
├── managers/
│   ├── EntityManager.h / EntityManager.cpp
│   ├── ResourceManager.h / ResourceManager.cpp
│   └── AquariumManager.h / AquariumManager.cpp
├── ui/
│   ├── ImGuiManager.h / ImGuiManager.cpp
│   ├── ShopUI.h / ShopUI.cpp
│   ├── StatsPanel.h / StatsPanel.cpp
│   └── DebugWindow.h / DebugWindow.cpp
└── utils/
    ├── Vector2D.h / Vector2D.cpp
    ├── Math.h / Math.cpp
    └── Config.h

🔧 ÉTAPES POUR COMPLÉTER LE PROJET
-----------------------------------

1. Copiez TOUS les fichiers .h et .cpp depuis les artifacts
2. Téléchargez ImGui dans external/imgui/
3. Installez SDL3 sur votre système
4. Exécutez : ./build.sh (Linux/Mac) ou build.bat (Windows)
5. Lancez : ./build/AquariumSimulator

💡 ASTUCE
---------
Retournez dans la conversation avec Claude et copiez/collez le contenu
de chaque artifact dans le fichier correspondant.

Il y a environ 50 fichiers à copier au total.

📧 BESOIN D'AIDE ?
------------------
Consultez README.md, QUICKSTART.md et ARCHITECTURE.md pour plus d'infos.

Bonne chance ! 🐠
""",

        # setup.sh
        "AquariumSimulator/setup.sh": """#!/bin/bash
echo "🐠 Installation d'Aquarium Simulator..."
echo "⚠️  Ce script installe SDL3 et ImGui"
echo ""

# Détecter l'OS
OS="$(uname -s)"

case "$OS" in
    Linux*)
        sudo apt-get update
        sudo apt-get install -y build-essential cmake git
        ;;
    Darwin*)
        brew install cmake git
        ;;
esac

# Télécharger ImGui
if [ ! -d "external/imgui" ]; then
    cd external
    git clone https://github.com/ocornut/imgui.git
    cd ..
fi

echo ""
echo "✅ Installation terminée !"
echo "💡 Maintenant copiez les fichiers source depuis les artifacts"
""",

        # build.sh
        "AquariumSimulator/build.sh": """#!/bin/bash
echo "🔨 Compilation d'Aquarium Simulator..."

mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j4

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Compilation réussie !"
    echo "🎮 Lancez : ./build/AquariumSimulator"
else
    echo ""
    echo "❌ Erreur de compilation"
    exit 1
fi
""",

    }
    
    # Créer tous les fichiers
    for filepath, content in files.items():
        write_file(filepath, content)

def create_placeholder_files():
    """Créer des fichiers placeholder pour indiquer où mettre les vrais fichiers"""
    
    placeholders = {
        "AquariumSimulator/src/COPIER_ICI.txt": """
╔══════════════════════════════════════════════════════════════╗
║  COPIEZ TOUS LES FICHIERS .h ET .cpp ICI                     ║
╚══════════════════════════════════════════════════════════════╝

Depuis les artifacts de la conversation Claude, copiez :

1. main.cpp (dans ce dossier)
2. Tous les fichiers dans core/
3. Tous les fichiers dans entities/
4. Tous les fichiers dans systems/
5. Tous les fichiers dans managers/
6. Tous les fichiers dans ui/
7. Tous les fichiers dans utils/

Total : environ 50 fichiers à copier
""",
        
        "AquariumSimulator/external/TELECHARGER_IMGUI.txt": """
╔══════════════════════════════════════════════════════════════╗
║  TÉLÉCHARGER IMGUI ICI                                       ║
╚══════════════════════════════════════════════════════════════╝

Exécutez dans ce dossier (external/) :

    git clone https://github.com/ocornut/imgui.git

Ou téléchargez manuellement depuis :
https://github.com/ocornut/imgui

La structure devrait être :
external/
└── imgui/
    ├── imgui.h
    ├── imgui.cpp
    ├── backends/
    │   ├── imgui_impl_sdl3.h
    │   ├── imgui_impl_sdl3.cpp
    │   ├── imgui_impl_sdlrenderer3.h
    │   └── imgui_impl_sdlrenderer3.cpp
    └── ...
""",
        
        "AquariumSimulator/assets/README.txt": """
╔══════════════════════════════════════════════════════════════╗
║  DOSSIER DES ASSETS                                          ║
╚══════════════════════════════════════════════════════════════╝

Ce dossier contiendra :

📁 textures/
   ├── fish/          - Sprites des poissons
   ├── decorations/   - Sprites des décorations
   ├── ui/            - Éléments d'interface
   └── backgrounds/   - Arrière-plans

📁 fonts/
   └── Polices TTF

📁 sounds/
   ├── sfx/   - Effets sonores
   └── music/ - Musique d'ambiance

💡 Pour l'instant, le jeu utilise des formes géométriques simples.
   Les assets sont optionnels pour la version 1.0.

Consultez assets/README.md (à copier depuis les artifacts) 
pour plus d'informations.
""",
    }
    
    for filepath, content in placeholders.items():
        write_file(filepath, content)

def create_archive():
    """Créer une archive du projet"""
    print("\n📦 Création de l'archive...")
    
    try:
        shutil.make_archive(
            "AquariumSimulator_structure",
            'zip',
            '.',
            'AquariumSimulator'
        )
        print("✅ Archive créée : AquariumSimulator_structure.zip")
        print("\n📝 Cette archive contient la STRUCTURE du projet.")
        print("⚠️  Vous devez encore ajouter les fichiers source (.h et .cpp)")
        print("   depuis les artifacts de la conversation.")
    except Exception as e:
        print(f"❌ Erreur lors de la création de l'archive: {e}")

def main():
    """Fonction principale"""
    print("╔══════════════════════════════════════════════════════════════╗")
    print("║     GÉNÉRATEUR DE PROJET - AQUARIUM SIMULATOR               ║")
    print("╚══════════════════════════════════════════════════════════════╝")
    print()
    
    print("📁 Création de la structure des dossiers...")
    create_directory_structure()
    
    print("\n📄 Création des fichiers de base...")
    create_files()
    
    print("\n📝 Création des fichiers d'instructions...")
    create_placeholder_files()
    
    print("\n" + "="*60)
    print("✅ Structure du projet créée avec succès !")
    print("="*60)
    
    # Demander si on veut créer l'archive
    response = input("\n📦 Voulez-vous créer une archive ZIP ? (o/n) : ")
    if response.lower() in ['o', 'y', 'oui', 'yes']:
        create_archive()
    
    print("\n" + "="*60)
    print("📋 PROCHAINES ÉTAPES :")
    print("="*60)
    print("1. Ouvrez le dossier 'AquariumSimulator'")
    print("2. Lisez le fichier 'INSTRUCTIONS.txt'")
    print("3. Copiez TOUS les fichiers .h et .cpp depuis les artifacts")
    print("4. Téléchargez ImGui dans external/imgui/")
    print("5. Installez SDL3")
    print("6. Exécutez build.sh (Linux/Mac) ou build.bat (Windows)")
    print("\n💡 Consultez README.md pour plus d'informations")
    print("\nBonne chance ! 🐠🎮")

if __name__ == "__main__":
    main()
