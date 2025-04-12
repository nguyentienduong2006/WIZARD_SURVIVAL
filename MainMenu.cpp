#include "MainMenu.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

MainMenu::MainMenu()
{
    gFont = NULL;
    backgroundTexture = NULL;
    startTexture = NULL;
    menuTexture = NULL;
    soundOnTexture = NULL;
    soundOffTexture = NULL;
    musicOnTexture = NULL;
    musicOffTexture = NULL;

    startHovered = false;
    menuHovered = false;
    isSoundOn = true;
    isMusicOn = true;
}

MainMenu::~MainMenu()
{
    if(gFont) TTF_CloseFont(gFont);
    if(backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if(startTexture) SDL_DestroyTexture(startTexture);
    if(menuTexture) SDL_DestroyTexture(menuTexture);
    if(soundOnTexture) SDL_DestroyTexture(soundOnTexture);
    if(soundOffTexture) SDL_DestroyTexture(soundOffTexture);
    if(musicOnTexture) SDL_DestroyTexture(musicOnTexture);
    if(musicOffTexture) SDL_DestroyTexture(musicOffTexture);
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

    //create menuTexture
    menuTexture = createTextTexture("EXIT", white);
    int exitW, exitH;
    SDL_QueryTexture(menuTexture, NULL, NULL, &exitW, &exitH);
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
    if(!gFont || !Renderer::renderer) return nullptr;
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
        return;
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point mousePoint = {mouseX, mouseY};

    startHovered = SDL_PointInRect(&mousePoint, &startRect);
    menuHovered = SDL_PointInRect(&mousePoint, &exitRect);

    if(Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT)
    {
        if(startHovered)
        {
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            startGame = true;
            isRunning = true;
        }
        if(menuHovered)
        {
            if(buttonClickSound) Mix_PlayChannel(-1, buttonClickSound, 0);
            startGame = false;
            isRunning = false;
            return;
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
    if(startTexture) TextureManager::Draw(startTexture, {0, 0, startRect.w, startRect.h}, startRect);

    //render exit
    SDL_Color exitColor = menuHovered?hoverColor:white;
    SDL_DestroyTexture(menuTexture);
    menuTexture = createTextTexture("Exit", exitColor);
    if(menuTexture) TextureManager::Draw(menuTexture, {0, 0, exitRect.w, exitRect.h}, exitRect);

    //render volumeButton
    SDL_Texture* currenSoundTexture = isSoundOn?soundOnTexture:soundOffTexture;
    if(currenSoundTexture) TextureManager::Draw(currenSoundTexture, {0, 0, TILE_SIZE, TILE_SIZE}, soundRect);

    //render musicButton
    SDL_Texture* currentMusicTexture = isMusicOn?musicOnTexture:musicOffTexture;
    if(currentMusicTexture) TextureManager::Draw(currentMusicTexture, {0, 0, TILE_SIZE, TILE_SIZE}, musicRect);

}
