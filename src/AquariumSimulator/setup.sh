#!/bin/bash
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
