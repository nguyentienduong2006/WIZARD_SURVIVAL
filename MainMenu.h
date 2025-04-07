#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "config.h"

class MainMenu
{
public:
    MainMenu();
    ~MainMenu();

    void init();
    void handleEvent(bool &isRunning, bool& startGame);
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
};

#endif // _MAINMENU_H_
