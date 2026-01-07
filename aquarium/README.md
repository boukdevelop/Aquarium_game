```bash

g++ main.cpp src/core/*.cpp src/Graphics/*.cpp libs/Imgui/*.cpp libs/Imgui/backends/imgui_impl_sdl3.cpp libs/Imgui/backends/imgui_impl_sdlrenderer3.cpp -o mon_aquarium.exe -I include -I libs/SDL3/include -I libs/Imgui -I libs/Imgui/backends -L libs/SDL3/lib -lSDL3

```