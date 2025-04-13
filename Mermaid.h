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

private:
    static const int DETECTION_RANGE = TILE_SIZE*6;
    static const int ATTACK_RANGE = TILE_SIZE;
    //animation
    int frame = 0;
    int frameCount = 3;
    int frameDelay = 7;
    int frameTimer = 0;
    EnemyDirection direction = E_DOWN;
};

#endif // _Mermaid_H_
