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

    SDL_Texture* createTextTexture(const char* text, SDL_Color color);
private:
    TTF_Font* gFont;

    SDL_Texture* backgroundTexture;
    SDL_Texture* startTexture;
    SDL_Texture* exitTexture;
    SDL_Texture* soundOnTexture;
    SDL_Texture* soundOffTexture;
    SDL_Texture* musicOnTexture;
    SDL_Texture* musicOffTexture;
    SDL_Texture* helpBackground;
    SDL_Texture* quitTexture;
    SDL_Texture* helpButtonTexture;

    SDL_Rect startRect;
    SDL_Rect exitRect;
    SDL_Rect soundRect;
    SDL_Rect musicRect;
    SDL_Rect quitRect;
    SDL_Rect helpButtonRect;

    bool startHovered = false;
    bool exitHovered = false;
    bool isSoundOn = true;
    bool isMusicOn = true;
    bool needHelp;
    bool helpHovered;
    bool quitHovered;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color hoverColor = {255, 100, 100, 255};
};

#endif // _MAINMENU_H_
