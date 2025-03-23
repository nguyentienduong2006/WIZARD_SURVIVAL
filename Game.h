#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

const int MAP_WIDTH = 1280;
const int MAP_HEIGHT = 1280;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT, bool fullscreen = false);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static SDL_Rect camera;
private:

    bool isRunning;
    int cnt = 0;
    SDL_Window* window;

};
#endif // _GAME_H_
