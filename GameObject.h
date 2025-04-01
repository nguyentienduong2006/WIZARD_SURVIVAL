#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "config.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, int x, int y);
    virtual ~GameObject();

    virtual void Update() = 0;
    virtual void Render();

    virtual void handleEvent();

protected:

    int xpos;
    int ypos;

    int speed;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif
