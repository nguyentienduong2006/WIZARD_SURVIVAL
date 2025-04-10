#include "Game.h"
Game* game = nullptr;
int main(int argc, char* args[])
{
    std::srand(std::time(0));
    const int FPS = 60;
    const int FrameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime;
    game = new Game();
    game->init("Wizard survival");
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
