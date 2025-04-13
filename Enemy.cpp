#include "Enemy.h"
#include "camera.h"
#include "TextureManager.h"

Enemy::Enemy(const char* textureSheet, int x, int y, int hp, int spd, int dmg) : GameObject(textureSheet, x, y), health(hp), speed(spd), damage(dmg)
{

}

void Enemy::Render()
{
    SDL_Rect renderPos = {destRect.x - Camera::camera.x, destRect.y - Camera::camera.y, destRect.w, destRect.h };
    if(isHit)
    {
        SDL_SetTextureColorMod(objTexture, 255, 100, 100);
    }
    else
    {
        SDL_SetTextureColorMod(objTexture, 255, 255, 255);
    }
    TextureManager::Draw(objTexture, srcRect, renderPos);

    SDL_SetTextureColorMod(objTexture, 255, 255, 255);
}

void Enemy::takeDamage(int damage)
{
    health -= damage;
    isHit = true;
    hitTime = SDL_GetTicks();
}
