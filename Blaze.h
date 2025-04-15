#ifndef _BLAZE_H_
#define _BLAZE_H_

#include "Enemy.h"
#include "Player.h"

class Blaze : public Enemy
{
public:
    Blaze(int x, int y);

    void Update() override;
    void Render() override;
    void Attack(Player* player) override;

private:
    static const int DETECTION_RANGE = TILE_SIZE*8;
    static const int ATTACK_RANGE = TILE_SIZE;

    Direction direction = E_DOWN;
};

#endif // _BLAZE_H_
