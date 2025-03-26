#include "EnemyManager.h"
#include <algorithm>

EnemyManager::EnemyManager()
{
    clearAll();
}

void EnemyManager::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void EnemyManager::updateAll(Player& player)
{
    for(auto& enemy : enemies)
    {
        enemy->Update(player);
    }
    removeDeadEnemies();
}

void EnemyManager::renderAll()
{
    for(auto& enemy : enemies)
    {
        enemy->Render();
    }
}

void EnemyManager::removeDeadEnemies()
{
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](Enemy* enemy) {
        if(enemy->isDead())
        {
            delete enemy;
            return true;
        }
        return false;
    }),
    enemies.end() );
}

void EnemyManager::clearAll() {
    for(auto enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}
