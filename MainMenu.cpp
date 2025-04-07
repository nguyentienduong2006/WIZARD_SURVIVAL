#include "MainMenu.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

MainMenu::MainMenu()
{
    gFont = NULL;
    backgroundTexture = NULL;
    startTexture = NULL;
    exitTexture = NULL;
}

MainMenu::~MainMenu()
{
    TTF_CloseFont(gFont);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(exitTexture);
}

void MainMenu::init()
{
    if(TTF_Init() == -1)
    {
        std::cout<<"Failed to init SDL_ttf"<<std::endl;
    }
    //Load font
    gFont = TTF_OpenFont("assets/fonts/gameFont.ttf", 54);
    if(!gFont) std::cout<<"Failed to load Font"<<std::endl;

    //Load background
    backgroundTexture = TextureManager::LoadTexture("assets/images/mainmenu.png");

    //create startTexture
    startTexture = createTextTexture("START", white);
    int startW, startH;
    SDL_QueryTexture(startTexture, NULL, NULL, &startW, &startH);
    startRect = {SCREEN_WIDTH/2- startW/2, SCREEN_HEIGHT*6/10 - 50, startW, startH};

    //create exitTexture
    exitTexture = createTextTexture("EXIT", white);
    int exitW, exitH;
    SDL_QueryTexture(exitTexture, NULL, NULL, &exitW, &exitH);
    exitRect = {SCREEN_WIDTH/2 - exitW/2, SCREEN_HEIGHT*6/10 + 50, exitW, exitH};
}

SDL_Texture* MainMenu::createTextTexture(const char* text, SDL_Color color)
{
    SDL_Surface* tempSurface = TTF_RenderText_Solid(gFont, text, color);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return newTexture;
}

void MainMenu::handleEvent(bool& isRunning, bool& startGame)
{
    if(Game::event.type == SDL_QUIT)
    {
        isRunning = false;
        startGame = false;
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mousePoint = {mouseX, mouseY};

    startHovered = SDL_PointInRect(&mousePoint, &startRect);
    exitHovered = SDL_PointInRect(&mousePoint, &exitRect);

    if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT)
    {
        if(startHovered)
        {
            startGame = true;
            isRunning = true;
        }
        if(exitHovered)
        {
            startGame = false;
            isRunning = false;
        }
    }
}

void MainMenu::render()
{
    //render bg
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    TextureManager::Draw(backgroundTexture, bgRect, bgRect);

    //render start
    SDL_Color startColor = startHovered?hoverColor:white;
    SDL_DestroyTexture(startTexture);
    startTexture = createTextTexture("START", startColor);
    TextureManager::Draw(startTexture, {0, 0, startRect.w, startRect.h}, startRect);

    //render exit
    SDL_Color exitColor = exitHovered?hoverColor:white;
    SDL_DestroyTexture(exitTexture);
    exitTexture = createTextTexture("Exit", exitColor);
    TextureManager::Draw(exitTexture, {0, 0, exitRect.w, exitRect.h}, exitRect);

    SDL_RenderPresent(Renderer::renderer);
}
