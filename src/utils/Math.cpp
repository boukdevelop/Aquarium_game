#include "Math.h"

// Les implémentations sont déjà inline dans Math.h
// Ce fichier est requis pour la compilation même s'il est vide

namespace Math {
    // Vous pouvez ajouter des fonctions supplémentaires ici
    
    // Exemple : fonction pour mapper une valeur d'une plage à une autre
    float map(float value, float inMin, float inMax, float outMin, float outMax) {
        return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));
    }
    
    // Distance entre deux points
    float distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }
}
