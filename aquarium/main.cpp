#include <iostream>
#include <ctime>      // Pour le srand
#include <cstdlib>    // Pour le rand
#include <SDL3/SDL.h> // Pour la gestion du temps (GetTicks)

// Inclusions de nos propres fichiers d'en-tête
#include "include/Graphics/Window.hpp"
#include "include/Graphics/Renderer.hpp"
#include "include/Graphics/GuiManager.hpp"
#include "include/core/Aquarium.hpp"
#include "include/core/Poisson.hpp"
#include "include/core/Algue.hpp"

int main(int argc, char *argv[])
{
    // 1. Initialisation de l'aléatoire
    // Indispensable pour que les poissons ne fassent pas toujours la même chose
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Lancement de la simulation Aquarium..." << std::endl;

    // 2. Création de la Fenêtre et du Renderer
    // Dimensions : 800x800 pour avoir des cases carrées de 200px (4x4)
    Window window("Projet Aquarium - Boukala Franck", 800, 800);

    if (!window.isRunning())
    {
        std::cerr << "Impossible de lancer la fenêtre." << std::endl;
        return -1;
    }

    Renderer renderer(window.getRenderer(), window.getWidth(), window.getHeight());
    renderer.loadTexture("fond", "assets/fond.bmp");

    // 3. Chargement des Textures (Optionnel)
    // Assure-toi d'avoir les images dans le dossier de l'exécutable ou assets/
    // Si les images ne sont pas trouvées, le Renderer utilisera des carrés de couleur.
    renderer.loadTexture("poisson", "assets/fish.bmp");
    renderer.loadTexture("algue", "assets/algae.bmp");

    // 4. Initialisation de l'Interface (ImGui)
    GuiManager::Init(window.getNativeWindow(), window.getRenderer());

    // 5. Initialisation de la Logique (Aquarium)
    Aquarium aquarium;

    // --- Peuplement initial de l'aquarium ---
    aquarium.initialiser();

    // AJOUTE BEAUCOUP D'ALGUES AU DEPART (Exemple : 5 algues)
    // Essaye de remplir les cases vides pour voir si elles s'affichent
    aquarium.ajouterEntity(new Algue(0, 3));
    aquarium.ajouterEntity(new Algue(1, 2));
    aquarium.ajouterEntity(new Algue(2, 1));
    aquarium.ajouterEntity(new Algue(3, 0));
    aquarium.ajouterEntity(new Algue(2, 2));

    // 6. Boucle Principale
    bool running = true;

    // Gestion du temps pour la simulation (Logique)
    // On veut que la logique avance toutes les 1 seconde (1000 ms),
    // mais que l'affichage soit fluide (60 FPS).
    Uint64 lastSimulationTime = SDL_GetTicks();
    const Uint64 simulationDelay = 1000; // 1000ms = 1 seconde par tour

    while (running && window.isRunning())
    {
        // A. Gestion des événements (Clavier, Souris, Fermeture)
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Passer l'événement à ImGui
            GuiManager::ProcessEvent(&event);

            // Gestion de la fermeture de fenêtre
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            // Fonctionnalité secondaire : Touches Clavier
            // 'N' pour nettoyer, 'Q' pour quitter
            // ... à l'intérieur de la boucle while(SDL_PollEvent(&event)) ...

            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                // CORRECTION SDL3 : On utilise event.key.key et les majuscules (SDLK_N, SDLK_Q)
                if (event.key.key == SDLK_N)
                {
                    aquarium.nettoyer();
                    std::cout << "Aquarium nettoyé via clavier !" << std::endl;
                }
                if (event.key.key == SDLK_Q)
                {
                    running = false;
                }
            }
        }

        // B. Mise à jour de la logique (Update)
        Uint64 currentTime = SDL_GetTicks();
        if (currentTime - lastSimulationTime > simulationDelay)
        {
            // C'est ici que les poissons bougent et mangent
            aquarium.update();
            lastSimulationTime = currentTime;

            // Debug console pour suivre ce qu'il se passe
            std::cout << "--- Tour suivant ---" << std::endl;
            std::cout << "Salete: " << aquarium.getSalete() << std::endl;
        }

        // C. Rendu Graphique (Draw)
        // 1. Préparer ImGui
        GuiManager::NewFrame();

        // 2. Effacer l'écran
        window.clear();

        // 3. Dessiner le jeu
        renderer.draw(aquarium);

        // 4. Dessiner l'interface ImGui
        GuiManager::Render(aquarium);

        // 5. Afficher les données ImGui par dessus le jeu
        GuiManager::RenderFrame(window.getRenderer());

        // 6. Afficher le tout à l'écran
        window.display();
    }

    // 7. Nettoyage final
    GuiManager::Shutdown();
    // Le destructeur de Window et Aquarium se chargera du reste

    return 0;
}