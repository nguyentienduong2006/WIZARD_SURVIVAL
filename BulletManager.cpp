#include "BulletManager.h"
#include "TextureManager.h"
#include "config.h"

BulletManager::~BulletManager()
{
    clearBullets();
}

void BulletManager::addBullet(int x, int y, int dx, int dy, const char* texture, bool _enemyBullet)
{
    bullets.push_back(new Bullet(x, y, dx, dy, texture, _enemyBullet));
}

void BulletManager::updateBullets()
{
    for(auto it = bullets.begin(); it != bullets.end();)
    {
        (*it)->Update();
        SDL_Rect bulletRect = (*it)->getDestRect();
        if(bulletRect.x < 0 || bulletRect.x > MAP_WIDTH || bulletRect.y < 0 || bulletRect.y > MAP_HEIGHT)
        {
            delete *it;
            it = bullets.erase(it);
        }
        else{
            ++it;
        }
    }
}

void BulletManager::renderBullets()
{
    for(auto& bullet : bullets)
    {
        bullet->Render();
    }
}

void BulletManager::clearBullets()
{
    for(auto& bullet : bullets)
    {
        delete bullet;
    }
    bullets.clear();
}
