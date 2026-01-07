cmake_minimum_required(VERSION 3.10)
project(Aquarium)

# Configuration C++
set(CMAKE_CXX_STANDARD 17)

# Où trouver les fichiers .h
include_directories(include libs/SDL3/include libs/Imgui libs/Imgui/backends)

# Où trouver les fichiers .lib/.dll
link_directories(libs/SDL3/lib)

# Liste de tous les fichiers sources
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "libs/Imgui/*.cpp"
    "libs/Imgui/backends/imgui_impl_sdl3.cpp"
    "libs/Imgui/backends/imgui_impl_sdlrenderer3.cpp"
    "main.cpp"
)

# Créer l'exécutable
add_executable(Aquarium ${SOURCES})

# Lier SDL3 (Sur Windows c'est souvent SDL3.lib)
target_link_libraries(Aquarium SDL3)