#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "algorithm"
#include "EnemyManager.h"
#include "Mermaid.h"
#include "BulletManager.h"
#include "Lion.h"
#include "Blaze.h"
#include "SlimeBoss.h"
#include "MapData.h"
#include "Collision.h"
#include <string>
#include <fstream>

SDL_Event Game::event;
Player* player = nullptr;
Map* map = nullptr;
EnemyManager enemyManager;
BulletManager bulletManager;

Game::Game()
{
    isRunning = false;
    currentState = MENU;
    Camera::camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Game::~Game()
{
    clean();
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"SDL initialized!"<<std::endl;

        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if(window){
            std::cout<<"Created window!"<<std::endl;

            SDL_Surface* iconSurface = IMG_Load("assets/images/GameIcon.png");
            SDL_SetWindowIcon(window, iconSurface);
            SDL_FreeSurface(iconSurface);
        }

        Renderer::renderer = SDL_CreateRenderer(window, -1, 0);
        if(Renderer::renderer) {
            std::cout<<"Created renderer!"<<std::endl;
        }

        if(TTF_Init() != -1)
        {
            std::cout<<"TTF initialized!"<<std::endl;
        }

        if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0)
        {
            std::cout<<"Mixer initialized!"<<std::endl;
            Mix_Volume(-1, MIX_MAX_VOLUME/2);
        }

        scoreFont = TTF_OpenFont("assets/fonts/gameFont.ttf", 24);

        backgroundMusic = Mix_LoadMUS("assets/sounds/bgMusic.mp3");
        shootSound = Mix_LoadWAV("assets/sounds/fireball.wav");
        buttonClickSound = Mix_LoadWAV("assets/sounds/buttonClick.wav");
        enemyDieSound = Mix_LoadWAV("assets/sounds/enemyDeath.wav");

        pauseBackgroundTexture = TextureManager::LoadTexture("assets/images/pauseBG.png");
        pauseBackgroundRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

        HPTexture = createTextTexture("HP", white);
        int HPW, HPH;
        SDL_QueryTexture(HPTexture, NULL, NULL, &HPW, &HPH);
        HPRect = {10, 10, HPW, HPH};

        healthBackground = {10 + HPW + 10, 10, 200, HPH};
        currenHealth = {healthBackground.x, 10, 200, HPH};

        gameOverBackground = TextureManager::LoadTexture("assets/images/gameOverBackground.png");

        gameOverTexture = createTextTexture("GAME OVER", white);
        int textW, textH;
        SDL_QueryTexture(gameOverTexture, NULL, NULL, &textW, &textH);
        gameOverRect = {SCREEN_WIDTH/2 - textW/2, SCREEN_HEIGHT/2 - textH/2, textW, textH};

        menuTexture = createTextTexture("MENU", white);
        int menuW, menuH;
        SDL_QueryTexture(menuTexture, NULL, NULL, &menuW, &menuH);
        menuRect = {SCREEN_WIDTH/2 - menuW/2, gameOverRect.y + gameOverRect.h + 30, menuW, menuH};

        replayTexture = createTextTexture("REPLAY", white);
        int replayW, replayH;
        SDL_QueryTexture(replayTexture, NULL, NULL, &replayW, &replayH);
        replayRect = {SCREEN_WIDTH/2 - replayW/2, menuRect.y + menuRect.h + 30, replayW, replayH};

        std::ifstream inFile("highscore.txt");
        if(inFile)
        {
            inFile >> highscore;
        }
        inFile.close();

        isRunning = true;
    }

    mainMenu.init();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&Game::event)) {
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11)
            {
                if(!isFullScreen)
                {
                    isFullScreen = true;
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
                else
                {
                    isFullScreen = false;
                    SDL_SetWindowFullscreen(window, 0);
                }
            }

        switch(currentState)
        {
        case MENU:
            {
                bool startGame = false;
                mainMenu.handleEvent(isRunning, startGame, buttonClickSound);

                if(startGame)
                {
                    if(player) delete player;
                    if(map) delete map;
                    bulletManager.clearBullets();
                    enemyManager.clearEnemies();

                    currentState = PLAYING;
                    player = new Player("assets/images/witch.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                    map = new Map();
                    score = 0;
                    gameStartTime = SDL_GetTicks();
                    totalPausedTime = 0;
                    lastScoreTime = gameStartTime;
                    lastSpawnTime = 0;
                    spawnInterval = 5000;
                    bgMusicStarted = false;
                    lastBossSpawnTime = 0;
                }
            }
            break;
        case PLAYING:
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                currentState = PAUSED;
                player->stopMoving();
                pauseStartTime = SDL_GetTicks();
                Mix_PauseMusic();
            }

            if(player)
            {
                player->handleEvent(bulletManager, shootSound);
            }

            break;
        case PAUSED:
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                currentState = PLAYING;
                totalPausedTime += (SDL_GetTicks() - pauseStartTime);
                Mix_ResumeMusic();
            }
        }
            break;
        case GAME_OVER:
            {
                Mix_HaltMusic();

                if(event.type == SDL_QUIT)
                {
                    isRunning = false;
                }

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point mousePoint = {mouseX, mouseY};

                if(SDL_PointInRect(&mousePoint, &menuRect))
                {
                    menuHovered = true;
                }
                else
                {
                    menuHovered = false;
                }

                if(SDL_PointInRect(&mousePoint, &replayRect))
                {
                    replayHovered = true;
                }
                else
                {
                    replayHovered = false;
                }

                if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                {
                    if(menuHovered)
                    {
                        if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
                        currentState = MENU;
                    }

                    if(replayHovered)
                    {
                        if(player) delete player;
                        if(map) delete map;
                        bulletManager.clearBullets();
                        enemyManager.clearEnemies();

                        player = new Player("assets/images/witch.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                        map = new Map();
                        score = 0;
                        gameStartTime = SDL_GetTicks();
                        totalPausedTime = 0;
                        lastScoreTime = gameStartTime;
                        lastSpawnTime = 0;
                        spawnInterval = 5000;
                        bgMusicStarted = false;
                        lastBossSpawnTime = 0;

                        currentState = PLAYING;
                    }
                }
            }
        }

    }
}

void Game::update()
{
    if(currentState == PLAYING)
    {
            Uint32 currentTime = SDL_GetTicks()- totalPausedTime;
            cnt++;
            std::cout<<"cnt: "<<cnt<<"         ";
            std::cout << "Camera: " << Camera::camera.x << ", " << Camera::camera.y << std::endl;

            if(!bgMusicStarted && currentTime - gameStartTime >= bgMusicDelay)
            {
                bgMusicStarted = true;
                if(backgroundMusic)
                {
                    Mix_PlayMusic(backgroundMusic, -1);
                }
            }

            Uint32 elapsedTIme = currentTime - gameStartTime;

            if(currentTime - lastScoreTime >= 100)
            {
                score += (currentTime - lastScoreTime)/100;
                lastScoreTime = currentTime;
            }

            if(currentTime - lastSpawnTime >= spawnInterval)
            {
                int spawnX;
                int spawnY;
                do
                {
                    spawnX = std::rand()%(MAP_WIDTH - TILE_SIZE);
                    spawnY = std::rand()%(MAP_HEIGHT - TILE_SIZE);
                }
                while(touchesWall(spawnX, spawnY, MapData::lv1));

                int enemyType = std::rand()%3;
                switch(enemyType)
                {
                case 0:
                    enemyManager.addEnemy(new Mermaid(spawnX, spawnY));
                    break;
                case 1:
                    enemyManager.addEnemy(new Lion(spawnX, spawnY));
                    break;
                case 2:
                    enemyManager.addEnemy(new Blaze(spawnX, spawnY));
                    break;
                }

                lastSpawnTime = currentTime;

                if(spawnInterval > 1000)
                {
                    spawnInterval -= 50;
                }

                if(elapsedTIme >= ONE_MINUTE && (currentTime - lastBossSpawnTime) >= ONE_MINUTE)
                {
                    enemyManager.addEnemy(new SlimeBoss(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2));
                    lastBossSpawnTime = currentTime;
                }

            }

            player->Update();
            enemyManager.updateEnemies();
            bulletManager.updateBullets();

            int enemiesKilled = enemyManager.checkBulletCollisions(bulletManager);
            if(enemiesKilled >0)
            {
                score += enemiesKilled*10;
                if(enemyDieSound) Mix_PlayChannel(-1, enemyDieSound, 0);
            }
            player->checkBulletCollision(bulletManager);

            if(score > highscore)
            {
                highscore = score;
                std::ofstream outFile("highscore.txt");
                if(outFile)
                {
                    outFile << highscore;
                }
                outFile.close();
            }

            if(player->getHealth() <= 0)
            {
                currentState = GAME_OVER;
            }

        std::string scoreText = "Score " + std::to_string(score);
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = createTextTexture(scoreText.c_str(), white);
        int scoreW, scoreH;
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreW, &scoreH);
        scoreRect = {SCREEN_WIDTH - scoreW - 10, 10, scoreW, scoreH};

        std::string highscoreText = "Highscore " + std::to_string(highscore);
        SDL_DestroyTexture(highscoreTexture);
        highscoreTexture = createTextTexture(highscoreText.c_str(), white);
        int hsW, hsH;
        SDL_QueryTexture(highscoreTexture, NULL, NULL, &hsW, &hsH);
        highscoreRect = {SCREEN_WIDTH/2 - hsW/2, 10, hsW, hsH};

        currenHealth.w = 200*player->getHealth()/PLAYER_HEALTH;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer::renderer);

    switch(currentState)
    {
    case MENU:
        mainMenu.render();
        break;
    case PLAYING: case PAUSED:
        if(map) map->DrawMap();
        if(player) player->Render();
        enemyManager.renderEnemies();
        bulletManager.renderBullets();

        TextureManager::Draw(scoreTexture, {0, 0, scoreRect.w, scoreRect.h}, scoreRect);
        TextureManager::Draw(highscoreTexture, {0, 0, highscoreRect.w, highscoreRect.h}, highscoreRect);

        TextureManager::Draw(HPTexture, {0, 0, HPRect.w, HPRect.h}, HPRect);
        SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(Renderer::renderer, &healthBackground);
        SDL_SetRenderDrawColor(Renderer::renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Renderer::renderer, &currenHealth);
        SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(Renderer::renderer, &healthBackground);

        if(currentState == PAUSED && pauseBackgroundTexture)
        {
            TextureManager::Draw(pauseBackgroundTexture, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, pauseBackgroundRect);
        }
        break;

    case GAME_OVER:
        TextureManager::Draw(gameOverBackground, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
        TextureManager::Draw(gameOverTexture, {0, 0, gameOverRect.w, gameOverRect.h}, gameOverRect);

        SDL_Color menuColor = menuHovered?hoverColor:white;
        SDL_DestroyTexture(menuTexture);
        menuTexture = createTextTexture("MENU", menuColor);
        TextureManager::Draw(menuTexture, {0, 0, menuRect.w, menuRect.h}, menuRect);

        SDL_Color replayColor = replayHovered?hoverColor:white;
        SDL_DestroyTexture(replayTexture);
        replayTexture = createTextTexture("REPLAY", replayColor);
        TextureManager::Draw(replayTexture, {0, 0, replayRect.w, replayRect.h}, replayRect);

        TextureManager::Draw(scoreTexture, {0, 0, scoreRect.w, scoreRect.h}, scoreRect);
        TextureManager::Draw(highscoreTexture, {0, 0, highscoreRect.w, highscoreRect.h}, highscoreRect);
        break;

    }
    SDL_RenderPresent(Renderer::renderer);
}

void Game::clean()
{
    if(player)
    {
        delete player;
        player = nullptr;
    }

    if(map)
    {
        delete map;
        map = nullptr;
    }

    enemyManager.clearEnemies();
    bulletManager.clearBullets();

    if(scoreFont) TTF_CloseFont(scoreFont);
    if(scoreTexture) SDL_DestroyTexture(scoreTexture);
    if(highscoreTexture) SDL_DestroyTexture(highscoreTexture);
    if(pauseBackgroundTexture) SDL_DestroyTexture(pauseBackgroundTexture);
    if(HPTexture) SDL_DestroyTexture(HPTexture);
    if(gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    if(gameOverBackground) SDL_DestroyTexture(gameOverBackground);
    if(menuTexture) SDL_DestroyTexture(menuTexture);
    if(replayTexture) SDL_DestroyTexture(replayTexture);

    if(backgroundMusic) Mix_FreeMusic(backgroundMusic);
    if(shootSound) Mix_FreeChunk(shootSound);
    if(enemyDieSound) Mix_FreeChunk(enemyDieSound);
    if(buttonClickSound) Mix_FreeChunk(buttonClickSound);
    Mix_CloseAudio();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer::renderer);

    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    std::cout<<"destroyed game!"<<std::endl;
}

bool Game::running()
{
    return isRunning;
}

void Game::addScore(int points)
{
    if(currentState == PLAYING)
        score += points;
}

SDL_Texture* Game::createTextTexture(const char* text, SDL_Color color)
{
    SDL_Surface* tempSurface = TTF_RenderText_Solid(scoreFont, text, color);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return newTexture;
}
