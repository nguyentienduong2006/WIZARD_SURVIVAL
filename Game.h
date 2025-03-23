#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int width, int height, bool fullscreen = false);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    static SDL_Renderer* renderer;
    static SDL_Event event;
private:

    bool isRunning;
    int cnt = 0;
    SDL_Window* window;
};
#endif // _GAME_H_
