#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
    Enemy(const char* textureSheet, int x, int y, int speed, int health);
    ~Enemy();

    virtual void Update(Player& player) = 0;
    virtual void Render();

    void takeDamage(int damage);
    bool isDead();

protected:
    int speed;
    int health;
};

#endif // _ENEMY_H_
