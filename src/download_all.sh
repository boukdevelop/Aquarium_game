#!/bin/bash

# Script complet d'installation d'Aquarium Simulator
# Ce script fait TOUT automatiquement

set -e

echo "╔══════════════════════════════════════════════════════════════╗"
echo "║  INSTALLATION COMPLÈTE - AQUARIUM SIMULATOR                  ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo ""

# Couleurs
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

# Vérifier l'OS
OS="$(uname -s)"
echo "📋 Système détecté: $OS"

# Fonction pour afficher les étapes
step() {
    echo ""
    echo -e "${GREEN}▶${NC} $1"
    echo "----------------------------------------"
}

# Étape 1 : Installer les dépendances système
step "Étape 1/6 : Installation des dépendances système"

case "$OS" in
    Linux*)
        if command -v apt-get &> /dev/null; then
            sudo apt-get update
            sudo apt-get install -y build-essential cmake git wget unzip
        elif command -v dnf &> /dev/null; then
            sudo dnf install -y gcc-c++ cmake git wget unzip
        else
            echo -e "${RED}Gestionnaire de paquets non supporté${NC}"
            exit 1
        fi
        ;;
    Darwin*)
        if ! command -v brew &> /dev/null; then
            echo "Installation de Homebrew..."
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        fi
        brew install cmake git wget
        ;;
    *)
        echo -e "${RED}OS non supporté: $OS${NC}"
        exit 1
        ;;
esac

echo -e "${GREEN}✓${NC} Dépendances système installées"

# Étape 2 : Créer la structure du projet
step "Étape 2/6 : Création de la structure du projet"

mkdir -p AquariumSimulator
cd AquariumSimulator

# Créer tous les dossiers
mkdir -p src/{core,entities,systems,managers,ui,utils}
mkdir -p external
mkdir -p assets/{textures/{fish,decorations,ui,backgrounds},fonts,sounds/{sfx,music}}
mkdir -p build
mkdir -p .vscode
mkdir -p .github/ISSUE_TEMPLATE

echo -e "${GREEN}✓${NC} Structure créée"

# Étape 3 : Télécharger et compiler SDL3
step "Étape 3/6 : Installation de SDL3"

if [ ! -d "external/SDL" ]; then
    cd external
    echo "📥 Téléchargement de SDL3..."
    git clone https://github.com/libsdl-org/SDL.git
    cd SDL
    git checkout main
    
    echo "🔨 Compilation de SDL3 (cela peut prendre quelques minutes)..."
    mkdir -p build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    echo "📦 Installation de SDL3..."
    sudo cmake --install .
    
    cd ../../..
    echo -e "${GREEN}✓${NC} SDL3 installé"
else
    echo -e "${YELLOW}⚠${NC} SDL3 déjà présent"
fi

# Étape 4 : Télécharger ImGui
step "Étape 4/6 : Téléchargement d'ImGui"

if [ ! -d "external/imgui" ]; then
    cd external
    echo "📥 Téléchargement d'ImGui..."
    git clone https://github.com/ocornut/imgui.git
    cd ..
    echo -e "${GREEN}✓${NC} ImGui téléchargé"
else
    echo -e "${YELLOW}⚠${NC} ImGui déjà présent"
fi

# Étape 5 : Créer les fichiers de base
step "Étape 5/6 : Création des fichiers de configuration"

# CMakeLists.txt
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.15)
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
EOF

# .gitignore
cat > .gitignore << 'EOF'
build/
cmake-build-*/
external/SDL/
.vscode/
.idea/
*.o
*.obj
*.exe
CMakeCache.txt
CMakeFiles/
EOF

# README.md
cat > README.md << 'EOF'
# 🐠 Aquarium Simulator

Simulateur d'aquarium interactif en C++ avec SDL3 et ImGui.

## ⚠️ FICHIERS SOURCE MANQUANTS

Ce projet contient la structure et les dépendances, mais vous devez
encore ajouter les fichiers source (.h et .cpp) depuis les artifacts
de votre conversation avec Claude.

Environ 50 fichiers à copier dans src/

## 🚀 Compilation

```bash
cd build
cmake ..
cmake --build .
./AquariumSimulator
```

## 📝 Licence

MIT License
EOF

# build.sh
cat > build.sh << 'EOF'
#!/bin/bash
echo "🔨 Compilation..."
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j4
echo "✅ Compilé ! Lancez : ./build/AquariumSimulator"
EOF

chmod +x build.sh

# INSTRUCTIONS
cat > INSTRUCTIONS.txt << 'EOF'
╔══════════════════════════════════════════════════════════════╗
║         AQUARIUM SIMULATOR - INSTRUCTIONS                     ║
╚══════════════════════════════════════════════════════════════╝

✅ STRUCTURE ET DÉPENDANCES INSTALLÉES

Le projet est presque prêt ! Il ne manque que les fichiers source.

📋 FICHIERS À AJOUTER (depuis les artifacts Claude)
----------------------------------------------------

Vous devez copier environ 50 fichiers .h et .cpp dans le dossier src/

Liste complète :
- src/main.cpp
- src/core/*.h et *.cpp (10 fichiers)
- src/entities/*.h et *.cpp (8 fichiers)
- src/systems/*.h et *.cpp (8 fichiers)
- src/managers/*.h et *.cpp (6 fichiers)
- src/ui/*.h et *.cpp (8 fichiers)
- src/utils/*.h et *.cpp (5 fichiers)

🔧 UNE FOIS LES FICHIERS COPIÉS
--------------------------------

1. Exécutez : ./build.sh
2. Lancez : ./build/AquariumSimulator

💡 ASTUCE
---------
Retournez dans votre conversation avec Claude et copiez le contenu
de chaque artifact dans le fichier correspondant.

Bonne chance ! 🐠
EOF

echo -e "${GREEN}✓${NC} Fichiers de configuration créés"

# Étape 6 : Résumé
step "Étape 6/6 : Résumé"

echo ""
echo "╔══════════════════════════════════════════════════════════════╗"
echo "║  ✅ INSTALLATION TERMINÉE !                                  ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo ""
echo "📁 Projet créé dans : $(pwd)"
echo ""
echo "✅ SDL3 installé"
echo "✅ ImGui téléchargé"
echo "✅ Structure du projet créée"
echo "✅ Fichiers de configuration prêts"
echo ""
echo "⚠️  IL MANQUE ENCORE :"
echo "   Les fichiers source (.h et .cpp) à copier depuis les artifacts"
echo ""
echo "📋 PROCHAINES ÉTAPES :"
echo "   1. Lisez INSTRUCTIONS.txt"
echo "   2. Copiez les ~50 fichiers source depuis les artifacts Claude"
echo "   3. Exécutez : ./build.sh"
echo "   4. Lancez : ./build/AquariumSimulator"
echo ""
echo "💡 Pour un guide détaillé, consultez les artifacts de la conversation"
echo ""
echo "🎮 Bon développement !"
echo ""
