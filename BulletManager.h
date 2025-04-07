#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include <vector>
#include "Bullet.h"

class BulletManager
{
public:
    BulletManager() = default;
    ~BulletManager();
    void addBullet(int x, int y, int dx, int dy, const char* texture);
    void updateBullets();
    void renderBullets();
    void clearBullets();

    std::vector<Bullet*>& getBullets() { return bullets; }
private:
    std::vector<Bullet*> bullets;

};

#endif // _BULLET_MANAGER_H_
