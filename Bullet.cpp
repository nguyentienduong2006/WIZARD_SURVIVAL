#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(int x, int y, int dx, int dy, const char* texture) : x(x), y(y), dx(dx), dy(dy), textureFile(texture)
{
    src = {0, 0, 20, 20};
    dest = {x, y, 10, 10};

    bulletTexture = TextureManager::LoadTexture(texture);
}

void Bullet::update()
{
    x += dx;
    y += dy;

    dest.x = x;
    dest.y = y;

}

void Bullet::render()
{
    SDL_Rect adjustedRect = dest;
    adjustedRect.x -= Camera::camera.x;
    adjustedRect.y -= Camera::camera.y;
    TextureManager::Draw(bulletTexture, src, adjustedRect);
}

SDL_Rect Bullet::getRect() const
{
    return dest;
}
