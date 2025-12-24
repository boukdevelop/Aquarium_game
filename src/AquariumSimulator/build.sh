#!/bin/bash
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
