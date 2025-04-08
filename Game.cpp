#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "algorithm"
#include "EnemyManager.h"
#include "Orc.h"
#include "BulletManager.h"
#include "Lion.h"
#include "Blaze.h"
#include <string>

SDL_Event Game::event;
Player* player = nullptr;
Map* map = nullptr;
EnemyManager enemyManager;
BulletManager bulletManager;

Game::Game()
{
    isRunning = false;
    inMenu = true;
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
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"SDL initialized!"<<std::endl;
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if(window){
            std::cout<<"Created window!"<<std::endl;
            //LoadIcon
            SDL_Surface* iconSurface = IMG_Load("assets/images/GameIcon.png");
            SDL_SetWindowIcon(window, iconSurface);
            SDL_FreeSurface(iconSurface);
        }
        Renderer::renderer = SDL_CreateRenderer(window, -1, 0);
        if(Renderer::renderer) {
            std::cout<<"Created renderer!"<<std::endl;
        }

        //init TTF
        if(TTF_Init() != -1)
        {
            std::cout<<"TTF initialized!"<<std::endl;
        }
        scoreFont = TTF_OpenFont("assets/fonts/gameFont.ttf", 24);

        //init Mixer
        if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0)
        {
            std::cout<<"Mixer initialized!"<<std::endl;
        }

        backgroundMusic = Mix_LoadMUS("assets/sounds/bgMusic.mp3");
        shootSound = Mix_LoadWAV("assets/sounds/fireball.wav");
        buttonClickSound = Mix_LoadWAV("assets/sounds/buttonClick.wav");
        enemyDieSound = Mix_LoadWAV("assets/sounds/enemyDeath.wav");

        //Pause
        pauseTexture = createTextTexture("PAUSE", white);
        int pauseW,pauseH;
        SDL_QueryTexture(pauseTexture, NULL, NULL, &pauseW, &pauseH);
        pauseRect = {SCREEN_WIDTH/2 - pauseW/2, SCREEN_HEIGHT/2 - pauseH/2, pauseW, pauseH};

        isRunning = true;
    }
    mainMenu.init();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&Game::event)) {

        //fullscreen
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

        if(inMenu)
        {
            bool startGame = false;
            mainMenu.handleEvent(isRunning, startGame, buttonClickSound);
            if(startGame)
            {
                inMenu = false;
                player = new Player("assets/images/witch.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
                map = new Map();
                gameStartTime = SDL_GetTicks();
                lastScoreTime = gameStartTime;
            }
        }
        else
        {
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                isPaused = !isPaused;
                if(isPaused)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }
            }
            if(event.type == SDL_QUIT){
                    isRunning = false;
            }
            if(!isPaused && player){
                player->handleEvent(Game::event, bulletManager, shootSound);
            }
        }
    }
}

void Game::update()
{
    if(!inMenu)
    {
        Uint32 currentTime = SDL_GetTicks();

        if(!isPaused)
        {
            cnt++;
            std::cout<<"cnt: "<<cnt<<"         ";
            std::cout << "Camera: " << Camera::camera.x << ", " << Camera::camera.y << std::endl;
            //spawn

            if(!bgMusicStarted && currentTime - gameStartTime >= bgMusicDelay)
            {
                bgMusicStarted = true;
                if(backgroundMusic)
                {
                    Mix_PlayMusic(backgroundMusic, -1);
                }
            }

            Uint32 elapsedTIme = currentTime - gameStartTime;

            //score by time survive
            if(currentTime - lastScoreTime >= 100)
            {
                score += (currentTime - lastScoreTime)/100;
                lastScoreTime = currentTime;
            }

            if(currentTime - lastSpawnTime >= spawnInterval)
            {
                int spawnX = std::rand()%(MAP_WIDTH - TILE_SIZE);
                int spawnY = std::rand()%(MAP_HEIGHT - TILE_SIZE);

                int enemyType = std::rand()%3;

                switch(enemyType)
                {
                case 0:
                    enemyManager.addEnemy(new Orc(spawnX, spawnY));
                    break;
                case 1:
                    enemyManager.addEnemy(new Lion(spawnX, spawnY));
                    break;
                case 2:
                    enemyManager.addEnemy(new Blaze(spawnX, spawnY));
                    break;
                }

                if(spawnInterval > 500)
                {
                    spawnInterval -= 100;
                }
                lastSpawnTime = currentTime;

                if(elapsedTIme >= FIVE_MINUTE && (currentTime - lastSpawnTime) % ONE_MINUTE == 0)
                {
                    //int spawnX = std::rand()%(MAP_WIDTH - TILE_SIZE);
                    //int spawnY = std::rand()%(MAP_HEIGHT - TILE_SIZE);
                    //spawn BOSS
                }
            }

            player->Update();
            enemyManager.updateEnemies();
            bulletManager.updateBullets();

            //score by killing enemy
            int enemiesKilled = enemyManager.checkBulletCollisions(bulletManager);
            if(enemiesKilled >0)
            {
                score += enemiesKilled*10;
                if(enemyDieSound) Mix_PlayChannel(-1, enemyDieSound, 0);
            }

            if(player->getHealth() <= 0)
            {
                isRunning = false;
            }
        }

        //score Texture
        std::string scoreText = "Score " + std::to_string(score);
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = createTextTexture(scoreText.c_str(), white);
        int scoreW, scoreH;
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreW, &scoreH);
        scoreRect = {SCREEN_WIDTH - scoreW - 10, 10, scoreW, scoreH};
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer::renderer);

    if(inMenu)
    {
        mainMenu.render();
    }
    else
    {
        map->DrawMap();
        player->Render();
        enemyManager.renderEnemies();
        bulletManager.renderBullets();

        //render score
        TextureManager::Draw(scoreTexture, {0, 0, scoreRect.w, scoreRect.h}, scoreRect);

        if(isPaused && pauseTexture)
        {
            SDL_Rect optimizedRect = pauseRect;
            optimizedRect.w = 5*optimizedRect.w;
            optimizedRect.h = 5*optimizedRect.h;
            optimizedRect.x = SCREEN_WIDTH/2 - optimizedRect.w/2;
            optimizedRect.y = SCREEN_HEIGHT/2 - optimizedRect.h/2;
            TextureManager::Draw(pauseTexture, {0, 0, pauseRect.w, pauseRect.h}, optimizedRect);
        }

        SDL_RenderPresent(Renderer::renderer);
    }
}

void Game::clean()
{
    delete player;
    enemyManager.clearEnemies();
    delete map;
    bulletManager.clearBullets();

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
    score += points;
}

SDL_Texture* Game::createTextTexture(const char* text, SDL_Color color)
{
    SDL_Surface* tempSurface = TTF_RenderText_Solid(scoreFont, text, color);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return newTexture;
}
