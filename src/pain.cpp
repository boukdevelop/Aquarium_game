#include "core/Game.h"
#include <SDL3/SDL.h>

int main(int argc, char *argv[])
{
    Game game;

    if (!game.initialize())
    {
        SDL_Log("Failed to initialize game!");
        return -1;
    }

    game.run();
    game.shutdown();

    return 0;
}