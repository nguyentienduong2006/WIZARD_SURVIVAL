#ifndef _BULLET_H_
#define _BULLET_H_
#include "Game.h"
class Bullet
{
public:
    Bullet(int x, int y, int dx, int dy, const char* texture);

    void update();

    void render();

    SDL_Rect getRect() const;

    int x, y, dx, dy;
    SDL_Texture* bulletTexture;
    SDL_Rect src, dest;
private:
    const char* textureFile;
};
#endif // _BULLET_H_
