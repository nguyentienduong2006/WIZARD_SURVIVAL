#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Player* player;
Map* map;

Game::Game()
{

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
    std::cout<<cnt<<std::endl;
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
