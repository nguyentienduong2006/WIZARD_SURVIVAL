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


SDL_Event Game::event;
Player* player;
Map* map;
EnemyManager enemyManager;
BulletManager bulletManager;

Game::Game()
{
    isRunning = false;
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
            SDL_Surface* iconSurface = IMG_Load("assets/images/GameIcon.png");
            SDL_SetWindowIcon(window, iconSurface);
            SDL_FreeSurface(iconSurface);
        }
        Renderer::renderer = SDL_CreateRenderer(window, -1, 0);
        if(Renderer::renderer) {
            std::cout<<"Created renderer!"<<std::endl;
        }
        isRunning = true;
    }
    player = new Player("assets/images/witch.png", MAP_WIDTH/2, MAP_HEIGHT/2);
    map = new Map();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&Game::event)) {
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
        player->handleEvent(Game::event, bulletManager);
    }
}

void Game::update()
{
    cnt++;
    std::cout<<"cnt: "<<cnt<<"         ";
    std::cout << "Camera: " << Camera::camera.x << ", " << Camera::camera.y << std::endl;
    //spawn
    Uint32 currentTIme = SDL_GetTicks();
    Uint32 elapsedTIme = currentTIme - gameStartTime;

    if(currentTIme - lastSpawnTime >= spawnInterval)
    {
        int spawnX = std::rand()%(MAP_WIDTH - TILE_SIZE);
        int spawnY = std::rand()%(MAP_HEIGHT - TILE_SIZE);

        int enemyType = std::rand()%2;

        switch(enemyType)
        {
        case 0:
            enemyManager.addEnemy(new Orc(spawnX, spawnY));
            break;
        case 1:
            enemyManager.addEnemy(new Lion(spawnX, spawnY));
            break;
        }

        if(spawnInterval > 500)
        {
            spawnInterval -= 100;
        }
        lastSpawnTime = currentTIme;

        if(elapsedTIme >= FIVE_MINUTE && (currentTIme - lastSpawnTime) % ONE_MINUTE == 0)
        {
            int spawnX = std::rand()%(MAP_WIDTH - TILE_SIZE);
            int spawnY = std::rand()%(MAP_HEIGHT - TILE_SIZE);
            //spawn BOSS
        }
    }

    player->Update();
    enemyManager.updateEnemies();
    bulletManager.updateBullets();
    enemyManager.checkBulletCollisions(bulletManager);
    if(player->getHealth() <= 0)
    {
        isRunning = false;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer::renderer);
    map->DrawMap();
    player->Render();
    enemyManager.renderEnemies();
    bulletManager.renderBullets();
    SDL_RenderPresent(Renderer::renderer);
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
    std::cout<<"destroyed game!"<<std::endl;
}

bool Game::running()
{
    return isRunning;
}

