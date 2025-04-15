#ifndef _Mermaid_H_
#define _Mermaid_H_

#include "Enemy.h"
#include "Player.h"

class Mermaid : public Enemy
{
public:
    Mermaid(int x, int y);

    void Update() override;
    void Render() override;
    void Attack(Player* player) override;
    void shootBullet(int dx, int dy, int distance);

private:
    Direction direction = E_DOWN;

    static const int DETECTION_RANGE = TILE_SIZE*10;
    static const int ATTACK_RANGE = TILE_SIZE;
    static const int LONG_ATTACK_RANGE = 8*TILE_SIZE;

    const Uint32 BULLET_INTERVAL = 2000;
    Uint32 lastBulletTime = 0;
};

#endif // _MERMAID_H_
