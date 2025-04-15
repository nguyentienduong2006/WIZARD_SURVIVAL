#include "EnemyManager.h"

void EnemyManager::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void EnemyManager::updateEnemies()
{
    for( auto it = enemies.begin(); it != enemies.end(); )
    {
        (*it)->Update();

        if((*it)->getHealth() <= 0)
        {
            delete *it;
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EnemyManager::renderEnemies()
{
    for( auto enemy : enemies )
    {
        enemy->Render();
    }
}

void EnemyManager::clearEnemies()
{
    for(auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

int EnemyManager::checkBulletCollisions(BulletManager& bulletManager)
{
    int killed = 0;

    auto& bullets = bulletManager.getBullets();

    for(auto enemyIt = enemies.begin(); enemyIt != enemies.end(); )
    {
        bool enemyHit = false;

        for( auto bulletIt = bullets.begin(); bulletIt != bullets.end(); )
        {
            bool isEnemyBullet;
            isEnemyBullet = (*bulletIt)->isEnemyBullet();

            if(!isEnemyBullet)
            {
                if(*bulletIt == nullptr)
                {
                    bulletIt = bullets.erase(bulletIt);
                    continue;
                }

                SDL_Rect enemyRect = (*enemyIt)->getDestRect();
                SDL_Rect bulletRect = (*bulletIt)->getDestRect();
                if(SDL_HasIntersection(&enemyRect, &bulletRect))
                {
                    (*enemyIt) -> takeDamage((*bulletIt)->getDamage());
                    delete *bulletIt;
                    bulletIt = bullets.erase(bulletIt);
                    enemyHit = true;
                }
                else
                {
                    ++bulletIt;
                }
            }
            else ++bulletIt;
        }

        if(enemyHit && (*enemyIt)->getHealth() <= 0)
        {
            delete *enemyIt;
            enemyIt = enemies.erase(enemyIt);
            killed++;
        }
        else
        ++enemyIt;
    }

    return killed;
}
