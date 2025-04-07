#ifndef _GAME_H_
#define _GAME_H_

#include "config.h"
#include <iostream>
#include <vector>
#include "Bullet.h"
#include "BulletManager.h"
#include <ctime>
#include <cstdlib>

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

    static SDL_Event event;
    static std::vector<Bullet> bullets;
    void spawnEnemy(int x, int y);
private:
    bool isRunning;
    int cnt = 0;
    SDL_Window* window;
    Uint32 gameStartTime = 0;
    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 5000;
    static const Uint32 FIVE_MINUTE = 300000;
    static const Uint32 ONE_MINUTE = 600000;
};
#endif // _GAME_H_
