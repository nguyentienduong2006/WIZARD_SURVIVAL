#include "Game.h"

Game* game = nullptr;

int main(int argc, char* args[])
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    const int FPS = 60;
    const int FrameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Wizard survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);

    while( game->running() )
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(FrameDelay > frameTime){
            SDL_Delay(FrameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}
