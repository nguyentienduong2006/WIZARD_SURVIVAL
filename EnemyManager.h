#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "Enemy.h"
#include "vector"
#include "BulletManager.h"

class EnemyManager
{
public:
    EnemyManager() {}
    ~EnemyManager() { clearEnemies(); }
    void addEnemy(Enemy* enemy);
    void updateEnemies();
    void renderEnemies();
    void clearEnemies();
    int checkBulletCollisions(BulletManager& bulletManager);

private:
    std::vector<Enemy*> enemies;
};

#endif // _ENEMYMANAGER_H_
