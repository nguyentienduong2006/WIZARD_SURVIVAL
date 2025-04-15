#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "config.h"
#include "GameObject.h"

class Player;

class Enemy : public GameObject
{
public:
    Enemy(const char* textureSheet, int x, int y, int hp, int spd, int dmg);
    virtual ~Enemy() {}

    virtual void Update() override = 0;
    virtual void Render() override;
    virtual void Attack(Player* player) = 0;

    int getHealth() const {return health; }
    void takeDamage(int damage);
    bool isDead() const {return health <= 0; }

protected:
    static const int HIT_DURATION = 200;
    int health;
    int speed;
    int damage;

    bool isHit = false;

    static const Uint32 ATTACK_COOLDOWN = 1000;
    Uint32 lastAttackTime = 0;
    Uint32 hitTime = 0;
};

#endif // _ENEMY_H_
