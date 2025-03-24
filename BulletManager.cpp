#include "BulletManager.h"
#include "TextureManager.h"

void BulletManager::addBullet(int x, int y, int dx, int dy, const char* texture)
{
    bullets.push_back(Bullet(x, y, dx, dy, texture));
}

void BulletManager::updateBullets()
{
    for(auto& bullet : bullets)
    {
        bullet.update();
    }
}

void BulletManager::renderBullets()
{
    for(auto& bullet : bullets)
    {
        bullet.render();
    }
}
