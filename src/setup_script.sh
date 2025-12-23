#!/bin/bash

# Script d'installation automatique pour Aquarium Simulator
# Ce script installe toutes les dépendances et compile le projet

set -e  # Arrêter en cas d'erreur

echo "🐠 ============================================"
echo "   Installation d'Aquarium Simulator"
echo "============================================"

# Détecter l'OS
OS="$(uname -s)"
echo "📋 Système détecté: $OS"

# Fonction d'installation pour Linux
install_linux() {
    echo "🐧 Installation pour Linux..."
    
    # Installer les dépendances
    if command -v apt-get &> /dev/null; then
        echo "📦 Installation des dépendances avec apt-get..."
        sudo apt-get update
        sudo apt-get install -y build-essential cmake git
    elif command -v dnf &> /dev/null; then
        echo "📦 Installation des dépendances avec dnf..."
        sudo dnf install -y gcc-c++ cmake git
    else
        echo "❌ Gestionnaire de paquets non supporté"
        exit 1
    fi
}

# Fonction d'installation pour macOS
install_macos() {
    echo "🍎 Installation pour macOS..."
    
    # Vérifier si Homebrew est installé
    if ! command -v brew &> /dev/null; then
        echo "📦 Installation de Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    
    echo "📦 Installation des dépendances..."
    brew install cmake git
}

# Installer selon l'OS
case "$OS" in
    Linux*)
        install_linux
        ;;
    Darwin*)
        install_macos
        ;;
    *)
        echo "❌ OS non supporté: $OS"
        exit 1
        ;;
esac

# Créer la structure du projet
echo "📁 Création de la structure du projet..."
mkdir -p AquariumSimulator
cd AquariumSimulator

mkdir -p src/{core,entities,systems,managers,ui,utils}
mkdir -p assets/{textures,fonts,sounds}
mkdir -p external
mkdir -p build

# Télécharger et compiler SDL3
if [ ! -d "external/SDL" ]; then
    echo "📥 Téléchargement de SDL3..."
    cd external
    git clone https://github.com/libsdl-org/SDL.git
    cd SDL
    git checkout main
    
    echo "🔨 Compilation de SDL3..."
    mkdir -p build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    echo "📦 Installation de SDL3..."
    sudo cmake --install .
    
    cd ../../..
else
    echo "✅ SDL3 déjà présent"
fi

# Télécharger ImGui
if [ ! -d "external/imgui" ]; then
    echo "📥 Téléchargement d'ImGui..."
    cd external
    git clone https://github.com/ocornut/imgui.git
    cd ..
else
    echo "✅ ImGui déjà présent"
fi

echo ""
echo "✅ ============================================"
echo "   Installation terminée !"
echo "============================================"
echo ""
echo "📝 Prochaines étapes:"
echo "   1. Copiez tous les fichiers source (.h et .cpp) dans leurs dossiers respectifs"
echo "   2. Copiez le CMakeLists.txt à la racine du projet"
echo "   3. Exécutez les commandes suivantes:"
echo ""
echo "      cd build"
echo "      cmake .."
echo "      cmake --build ."
echo "      ./AquariumSimulator"
echo ""
echo "🎮 Bon développement !"
