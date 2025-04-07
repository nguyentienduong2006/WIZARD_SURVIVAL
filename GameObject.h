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
    //obj position
    int xpos;
    int ypos;
    //obj velocity
    int xvel;
    int yvel;
    //objTexture
    SDL_Texture* objTexture;
    //object source/destination Rect
    SDL_Rect srcRect, destRect;
};

#endif
