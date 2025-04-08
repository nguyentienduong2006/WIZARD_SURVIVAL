#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "config.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    void init();
    void handleEvent(bool &isRunning, bool& startGame, Mix_Chunk* buttonClickSound);
    void render();

private:
    TTF_Font* gFont;
    SDL_Texture* backgroundTexture;
    SDL_Texture* startTexture;
    SDL_Texture* exitTexture;
    SDL_Rect startRect;
    SDL_Rect exitRect;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color hoverColor = {255, 200, 200, 255};

    bool startHovered = false;
    bool exitHovered = false;

    SDL_Texture* createTextTexture(const char* text, SDL_Color color);

    SDL_Texture* soundOnTexture;
    SDL_Texture* soundOffTexture;
    SDL_Rect soundRect;
    bool isSoundOn = true;

    SDL_Texture* musicOnTexture;
    SDL_Texture* musicOffTexture;
    SDL_Rect musicRect;
    bool isMusicOn = true;
};

#endif // _MAINMENU_H_
