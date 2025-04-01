#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "algorithm"

SDL_Event Game::event;
std::vector<Bullet> bullets;
Player* player;
Map* map;
std::vector<Enemy*> Game::enemies;

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
    player = new Player("assets/images/dot.bmp", 0, 0);
    map = new Map();
    spawnEnemy(1, 1);
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&Game::event)) {
        if(event.type == SDL_QUIT){
            isRunning = false;
        }
        player->handleEvent();
    }


}

void Game::update()
{
    cnt++;
    std::cout<<"cnt: "<<cnt<<"         ";
    std::cout << "Camera: " << Camera::camera.x << ", " << Camera::camera.y << std::endl;
    player->Update();
    for(auto enemy : enemies) {
        enemy->Update(*player);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(Renderer::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer::renderer);
    map->DrawMap();
    player->Render();
    for(auto enemy : enemies)
        enemy->Render();
    SDL_RenderPresent(Renderer::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer::renderer);

    SDL_Quit();
    std::cout<<"destroyed game!"<<std::endl;
}

bool Game::running()
{
    return isRunning;
}

void Game::spawnEnemy(int x, int y)
{
    enemies.push_back(new Orc(x,y));
}
