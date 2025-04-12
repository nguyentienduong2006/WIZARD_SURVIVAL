#ifndef _BULLET_H_
#define _BULLET_H_

#include "config.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet(int x, int y, int dx, int dy, const char* textureSheet, bool _enemyBullet);

    void Update() override;
    void Render() override;

    SDL_Rect getDestRect() const {return destRect; }
    int getDamage() const {return damage; }
    bool isEnemyBullet() const {return enemyBullet; }
private:
    int damage = 10;
    bool enemyBullet;
};
#endif // _BULLET_H_
