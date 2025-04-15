#include "SlimeBoss.h"
#include "Collision.h"
#include "MapData.h"
#include "Player.h"
#include <cmath>
#include "camera.h"
#include "TextureManager.h"
#include "MapData.h"
#include <vector>
#include "BulletManager.h"

SlimeBoss::SlimeBoss(int x, int y) : Enemy("assets/images/slime.png", x, y, 300, 2, 20)
{
    destRect = {x, y, 2*TILE_SIZE, 2*TILE_SIZE};
}

void SlimeBoss::Update()
{
    extern Player* player;

    Uint32 currentTime = SDL_GetTicks();

    if(player)
    {
        int dx = player->getX() - xpos;
        int dy = player->getY() - ypos;
        float distance = sqrt(dx*dx + dy*dy);

        if(distance < DETECTION_RANGE)
        {
            if(distance > 0)
            {
                xvel = (dx/distance) * speed;
                yvel = (dy/distance) * speed;
            }
            if(distance <= ATTACK_RANGE)
            {
                Attack(player);
            }
        }
        else
        {
            xvel = 0;
            yvel = 0;
        }

        if(xvel > 0) direction = B_RIGHT;
        if(xvel < 0) direction = B_LEFT;
        if(yvel > 0) direction = B_DOWN;
        if(yvel < 0) direction = B_UP;
    }

    xpos += xvel;
    ypos += yvel;

    if(xpos < 0 || xpos + TILE_SIZE > MAP_WIDTH || touchesWall(xpos, ypos, MapData::lv1))
    {
        xpos -= xvel;
    }
    if(ypos < 0 || ypos + TILE_SIZE > MAP_HEIGHT || touchesWall(xpos, ypos, MapData::lv1))
    {
        ypos -= yvel;
    }

    destRect.x = xpos;
    destRect.y = ypos;

    if( xvel != 0 || yvel != 0)
    {
        frameTimer++;
        if(frameTimer >= frameDelay)
        {
            frame = (frame+1) % frameCount;
            frameTimer = 0;
        }
    }
    else
    {
        frame = 0;
    }

    srcRect.x = frame*TILE_SIZE;
    srcRect.y = direction*TILE_SIZE;

    if(currentTime - lastBulletHellTime >= BULLET_HELL_INTERVAL)
    {
        ShootBulletHell();
        lastBulletHellTime = currentTime;
    }

    if(currentTime - lastExplosionTime >= EXPLOSION_INTERVAL)
    {
        BulletExplosion();
        lastExplosionTime = currentTime;
    }

    if(isHit && SDL_GetTicks() - hitTime >= HIT_DURATION)
    {
        isHit = false;
    }
}


void SlimeBoss::Render()
{
    Enemy::Render();
}

void SlimeBoss::Attack(Player* player)
{
    Uint32 currentTime = SDL_GetTicks();

    if( currentTime - lastAttackTime >= ATTACK_COOLDOWN )
    {
        SDL_Rect playeRect = player->getDestRect();
        SDL_Rect enemyRect = getDestRect();
        if(SDL_HasIntersection(&playeRect, &enemyRect))
        {
            player->takeDamage(damage);
            lastAttackTime = currentTime;
        }
    }
}

void SlimeBoss::ShootBulletHell()
{
    extern BulletManager bulletManager;
    const int bulletCount = 8;

    for(int i = 0; i < bulletCount; ++i)
    {
        float angle = i*2*M_PI/bulletCount;
        float vx = cos(angle)*(BULLET_VEL/2);
        float vy = sin(angle)*(BULLET_VEL/2);
        bulletManager.addBullet(xpos + TILE_SIZE, ypos + TILE_SIZE, vx, vy, "assets/images/darkball.png", true);
    }
}

void SlimeBoss::BulletExplosion()
{
    extern BulletManager bulletManager;
    const int bulletCount = 24;

    for(int i = 0; i < bulletCount; ++i)
    {
        float angle = i*2*M_PI/bulletCount;
        float vx = cos(angle)*(BULLET_VEL/2);
        float vy = sin(angle)*(BULLET_VEL/2);
        bulletManager.addBullet(xpos + TILE_SIZE, ypos + TILE_SIZE, vx, vy, "assets/images/darkball.png", true);
    }
}
