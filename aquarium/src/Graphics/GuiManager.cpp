#include "../../include/Graphics/GuiManager.hpp"
#include "../../libs/Imgui/imgui.h"
#include "../../libs/Imgui/backends/imgui_impl_sdl3.h"
#include "../../libs/Imgui/backends/imgui_impl_sdlrenderer3.h"

void GuiManager::Init(SDL_Window *window, SDL_Renderer *renderer)
{
    // 1. Configuration du contexte ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Activer clavier

    // 2. Style (Dark mode, c'est plus pro)
    ImGui::StyleColorsDark();

    // 3. Initialisation des backends (SDL3 + SDL_Renderer)
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void GuiManager::ProcessEvent(const SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

void GuiManager::NewFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void GuiManager::Render(Aquarium &aquarium)
{
    // Définition de la fenêtre ImGui
    ImGui::Begin("Gestion Aquarium");

    ImGui::Text("Simulation en cours...");
    ImGui::Separator();

    // Statistiques
    ImGui::Text("Poissons : %d", aquarium.getNombrePoissons());
    ImGui::Text("Algues   : %d", aquarium.getNombreAlgues());

    // Barre de saleté
    float salete = aquarium.getSalete();
    ImGui::Text("Niveau de Saleté :");
    ImGui::ProgressBar(salete / 100.0f, ImVec2(0.0f, 0.0f));

    ImGui::Separator();

    // Actions (Boutons)
    if (ImGui::Button("Nourrir (+ PV)"))
    {
        // Logique simplifiée : redonne vie à tout le monde
        // (Tu pourras améliorer ça en ajoutant de la nourriture physique)
        std::cout << "Nourriture distribuée !" << std::endl;
    }

    if (ImGui::Button("Nettoyer l'aquarium"))
    {
        aquarium.nettoyer();
    }

    ImGui::End();
}

void GuiManager::RenderFrame(SDL_Renderer *renderer)
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void GuiManager::Shutdown()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}