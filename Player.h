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

    static const int PLAYER_VEL = 5;

    SDL_Rect getDestRect() const {return destRect; }
    int getX() const {return xpos;}
    int getY() const {return ypos;}
    int getHealth() const {return health; }
    void takeDamage(int damage);
    void checkBulletCollision(BulletManager& bulletManager);
    void stopMoving();
private:
    int health;
    int frame = 0;
    int frameCount = 3;
    int frameDelay = 7;
    int frameTimer = 0;
    EnemyDirection direction = E_DOWN;

    bool isHit;
    Uint32 hitTime = 0;

    Mix_Chunk* hurtSound = nullptr;
};

#endif // _PLAYER_H_
