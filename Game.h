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

    void spawnEnemy(int x, int y);
    void addScore(int points);

    bool running();

    static SDL_Event event;
    static std::vector<Bullet> bullets;
private:
    SDL_Window* window;

    MainMenu mainMenu;

    GameState currentState;

    TTF_Font* scoreFont = NULL;

    SDL_Texture* gameOverBackground = nullptr;
    SDL_Texture* scoreTexture = NULL;
    SDL_Texture* createTextTexture(const char* text, SDL_Color color);
    SDL_Texture* pauseBackgroundTexture;
    SDL_Texture* HPTexture = nullptr;
    SDL_Texture* highscoreTexture = nullptr;
    SDL_Texture* gameOverTexture = nullptr;
    SDL_Texture* menuTexture = nullptr;
    SDL_Texture* replayTexture = nullptr;

    SDL_Rect scoreRect;
    SDL_Rect pauseBackgroundRect;
    SDL_Rect HPRect;
    SDL_Rect currenHealth;
    SDL_Rect healthBackground;
    SDL_Rect highscoreRect;
    SDL_Rect gameOverRect;
    SDL_Rect menuRect;
    SDL_Rect replayRect;

    Mix_Music* backgroundMusic = nullptr;
    Mix_Chunk* shootSound = nullptr;
    Mix_Chunk* enemyDieSound = nullptr;
    Mix_Chunk* buttonClickSound = nullptr;

    bool isRunning;
    bool isFullScreen = false;
    bool bgMusicStarted = false;
    bool menuHovered = false;
    bool replayHovered = false;

    int cnt = 0;
    int score = 0;
    int highscore;

    static const Uint32 ONE_MINUTE = 60000;
    Uint32 gameStartTime = 0;
    Uint32 lastSpawnTime = 0;
    Uint32 spawnInterval = 5000;
    Uint32 lastScoreTime = 0;
    Uint32 bgMusicDelay = 3000;
    Uint32 pauseStartTime = 0;
    Uint32 totalPausedTime = 0;
    Uint32 bossInterval = 18000;
    Uint32 gameTime = 0;
    Uint32 lastBossSpawnTime = 0;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color hoverColor = {255, 100, 100, 255};

};
#endif // _GAME_H_
