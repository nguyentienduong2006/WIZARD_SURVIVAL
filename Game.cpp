#include "Game.h"
using namespace std;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Game::Game()
{
    running = false;
}
Game::~Game()
{

}

bool Game::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout<<"INIT FAILD!"<<endl;
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Wizard Survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
        if(!gWindow)
        {
            cout<<"CREATE WINDOW FAILED"<<endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
            if(!gRenderer)
            {
                cout<<"CREATE RENDERER FAILED!"<<endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            }
        }
    }
    if(success) running = true;
    return success;
}
void Game::handleEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT) running = false;
    }
}
void Game::update()
{

}
void Game::render()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
}
void Game::close()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    SDL_Quit();
}
