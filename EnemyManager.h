#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "vector"
#include "Enemy.h"
#include "Orc.h"

class EnemyManager
{
private:
    std::vector<Enemy*> enemies;
public:
    EnemyManager();
    ~EnemyManager();

    void addEnemy(Enemy* enemy);
    void updateAll(Player& player);
    void renderAll();
    void removeDeadEnemies();
    void clearAll();
};

#endif // _ENEMYMANAGER_H_
