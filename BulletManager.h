#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "Game.h"
#include <vector>
#include "Bullet.h"

class BulletManager
{
public:
    void addBullet(int x, int y, int dx, int dy, const char* texture);

    void updateBullets();

    void renderBullets();

    std::vector<Bullet> bullets;
private:

};

#endif // _BULLET_MANAGER_H_
