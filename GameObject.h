#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "Game.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, int x, int y);
    virtual ~GameObject();

    virtual void Update();
    virtual void Render();

    virtual void handleEvent();

private:

    int xpos;
    int ypos;
    int xvel;
    int yvel;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif
