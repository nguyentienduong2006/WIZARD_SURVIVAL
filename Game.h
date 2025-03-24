#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
class Bullet;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

const int TILE_SIZE = 64;

const int MAP_WIDTH = 1920;
const int MAP_HEIGHT = 1600;

const int MAP_TILE_WIDTH = 30;
const int MAP_TILE_HEIGHT = 25;

const int BULLET_VEL = 10;

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
    static std::vector<Bullet> bullets;
private:

    bool isRunning;
    int cnt = 0;
    SDL_Window* window;

};
#endif // _GAME_H_
