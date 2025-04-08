#include "Bullet.h"
#include "TextureManager.h"
#include "Game.h"

Bullet::Bullet(int x, int y, int dx, int dy, const char* textureSheet) : GameObject(textureSheet, x, y)
{
    xvel = dx;
    yvel = dy;
    srcRect = {0, 0, 20, 20};
    destRect = {xpos, ypos, 40, 40};
}

void Bullet::Update()
{
    xpos += xvel;
    ypos += yvel;
    destRect.x = xpos;
    destRect.y = ypos;
}

void Bullet::Render()
{
    SDL_Rect adjustedRect = {destRect.x - Camera::camera.x, destRect.y - Camera::camera.y, destRect.w, destRect.h};
    TextureManager::Draw(objTexture, srcRect, adjustedRect);
}

