#ifndef _SLIMEBOSS_H_
#define _SLIMEBOSS_H_

#include "Enemy.h"
#include "Player.h"

class SlimeBoss : public Enemy
{
public:
    SlimeBoss(int x, int y);

    void Update() override;
    void Render() override;
    void Attack(Player* player) override;
    void ShootBulletHell();
    void BulletExplosion();

private:
    BossDirection direction = B_DOWN;

    static const int DETECTION_RANGE = TILE_SIZE*20;
    static const int ATTACK_RANGE = 2*TILE_SIZE;
    static const int BULLET_HELL_INTERVAL = 3000;
    static const int EXPLOSION_INTERVAL = 10000;

    Uint32 lastBulletHellTime = 0;
    Uint32 lastExplosionTime = 0;
};

#endif // _SLIMEBOSS_H_
