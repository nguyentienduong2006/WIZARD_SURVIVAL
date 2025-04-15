#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "BulletManager.h"
#include "config.h"

class Player : public GameObject
{
public:
    Player(const char* textureSheet, int x, int y);
    ~Player() {}

    void Update() override;
    void Render() override;
    void handleEvent(BulletManager& bulletManager, Mix_Chunk* shootSound);

    void takeDamage(int damage);
    void checkBulletCollision(BulletManager& bulletManager);
    void stopMoving();

    int getHealth() const {return health;}

    static const int PLAYER_VEL = 5;
private:
    Mix_Chunk* hurtSound = nullptr;

    int health;

    bool isHit;

    Direction direction = E_DOWN;

    Uint32 hitTime = 0;
};

#endif // _PLAYER_H_
