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

    //soundButton
    soundOnTexture = TextureManager::LoadTexture("assets/images/soundOn.png");
    soundOffTexture = TextureManager::LoadTexture("assets/images/soundOff.png");
    soundRect = {10, 10, TILE_SIZE, TILE_SIZE};

    //musicButton
    musicOnTexture = TextureManager::LoadTexture("assets/images/musicOn.png");
    musicOffTexture = TextureManager::LoadTexture("assets/images/musicOff.png");
    musicRect = {10, 10 + TILE_SIZE + 10, TILE_SIZE, TILE_SIZE};
}

SDL_Texture* MainMenu::createTextTexture(const char* text, SDL_Color color)
{
    SDL_Surface* tempSurface = TTF_RenderText_Solid(gFont, text, color);
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Renderer::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return newTexture;
}

void MainMenu::handleEvent(bool& isRunning, bool& startGame, Mix_Chunk* buttonClickSound)
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
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            startGame = true;
            isRunning = true;
        }
        if(exitHovered)
        {
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            startGame = false;
            isRunning = false;
        }
        if(SDL_PointInRect(&mousePoint, &soundRect))
        {
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            isSoundOn = !isSoundOn;
            if(isSoundOn)
            {
                Mix_Volume(-1, MIX_MAX_VOLUME);
            }
            else
            {
                Mix_Volume(-1, 0);
            }
        }
        if(SDL_PointInRect(&mousePoint, &musicRect))
        {
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            isMusicOn = !isMusicOn;
            if(isMusicOn)
            {
                Mix_VolumeMusic(MIX_MAX_VOLUME);
            }
            else
            {
                Mix_VolumeMusic(0);
            }
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

    //render volumeButton
    SDL_Texture* currenSoundTexture = isSoundOn?soundOnTexture:soundOffTexture;
    TextureManager::Draw(currenSoundTexture, {0, 0, TILE_SIZE, TILE_SIZE}, soundRect);

    //render musicButton
    SDL_Texture* currentMusicTexture = isMusicOn?musicOnTexture:musicOffTexture;
    TextureManager::Draw(currentMusicTexture, {0, 0, TILE_SIZE, TILE_SIZE}, musicRect);

    SDL_RenderPresent(Renderer::renderer);
}
