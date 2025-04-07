#include "Enemy.h"
#include "camera.h"
#include "TextureManager.h"

Enemy::Enemy(const char* textureSheet, int x, int y, int hp, int spd, int dmg) : GameObject(textureSheet, x, y), health(hp), speed(spd), damage(dmg)
{

}

void Enemy::Render()
{
    SDL_Rect renderPos = {destRect.x - Camera::camera.x, destRect.y - Camera::camera.y, destRect.w, destRect.h };
    TextureManager::Draw(objTexture, srcRect, renderPos);
}
