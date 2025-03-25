#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "algorithm"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera;
std::vector<Bullet> bullets;
Player* player;
Map* map;

Game::Game()
{
    isRunning = false;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
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
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            std::cout<<"Created renderer!"<<std::endl;
        }
        isRunning = true;
    }
    player = new Player("assets/images/dot.bmp", 0, 0);
    map = new Map();
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
    std::cout << "Camera: " << camera.x << ", " << camera.y << std::endl;
    player->Update();
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    std::cout<<"destroyed game!"<<std::endl;
}

bool Game::running()
{
    return isRunning;
}
