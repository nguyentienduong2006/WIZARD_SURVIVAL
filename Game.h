#ifndef _GAME_H_
#define _GAME_H_

#include "config.h"
#include <iostream>
#include <vector>
#include "Bullet.h"
#include "BulletManager.h"
#include <ctime>
#include <cstdlib>
#include "MainMenu.h"

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

    void addScore(int points);
private:
    bool isRunning;
    bool isFullScreen = false;
    int cnt = 0;
    SDL_Window* window;
    Uint32 gameStartTime = 0;
    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 5000;
    static const Uint32 FIVE_MINUTE = 300000;
    static const Uint32 ONE_MINUTE = 600000;

    //menu
    MainMenu mainMenu;
    bool inMenu;

    //score system
    int score = 0;
    Uint32 lastScoreTime = 0;
    TTF_Font* scoreFont = NULL;
    SDL_Texture* scoreTexture = NULL;
    SDL_Rect scoreRect;

    SDL_Color white = {255, 255, 255, 255};

    SDL_Texture* createTextTexture(const char* text, SDL_Color color);

    //sound
    Mix_Music* backgroundMusic = nullptr;
    Mix_Chunk* shootSound = nullptr;
    Mix_Chunk* enemyDieSound = nullptr;
    Mix_Chunk* buttonClickSound = nullptr;
    bool bgMusicStarted = false;
    Uint32 bgMusicDelay = 3000;

    //pause
    bool isPaused = false;
    SDL_Texture* pauseTexture;
    SDL_Rect pauseRect;
    Uint32 pauseStartTime = 0;
    Uint32 totalPausedTime = 0;

    //HP text texture
    SDL_Texture* HPTexture = nullptr;
    SDL_Rect HPRect;
    //HP bar
    SDL_Rect currenHealth;
    SDL_Rect healthBackground;

    //highscre
    int highscore;
    SDL_Texture* highscoreTexture = nullptr;
    SDL_Rect highscoreRect;
};
#endif // _GAME_H_
