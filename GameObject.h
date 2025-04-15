#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "config.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, int x, int y);
    virtual ~GameObject() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

    int getX() const { return xpos; }
    int getY() const { return ypos; }
    SDL_Rect getDestRect() const { return destRect; }
protected:
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

    int xpos;
    int ypos;

    int xvel;
    int yvel;

    int frame = 0;
    int frameCount = 3;
    int frameDelay = 7;
    int frameTimer = 0;
};

#endif
