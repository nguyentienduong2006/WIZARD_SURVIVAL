#include "Blaze.h"
#include "Collision.h"
#include "MapData.h"
#include "Player.h"
#include "cmath"
#include "camera.h"
#include "TextureManager.h"
#include "MapData.h"

Blaze::Blaze(int x, int y) : Enemy("assets/images/blaze.png", x, y, 30, 3, 5)
{
}

void Blaze::Update()
{
    extern Player* player;
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
        if(xvel > 0) direction = E_RIGHT;
        if(xvel < 0) direction = E_LEFT;
        if(yvel > 0) direction = E_DOWN;
        if(yvel < 0) direction = E_UP;
    }
    xpos += xvel;
    ypos += yvel;
    //xuyen tuong
    if(xpos < 0 || xpos + TILE_SIZE > MAP_WIDTH)
    {
        xpos -= xvel;
    }
    if(ypos < 0 || ypos + TILE_SIZE > MAP_HEIGHT)
    {
        ypos -= yvel;
    }
    destRect.x = xpos;
    destRect.y = ypos;

    //animation
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

    if(isHit && SDL_GetTicks() - hitTime >= HIT_DURATION)
    {
        isHit = false;
    }
}


void Blaze::Render()
{
    Enemy::Render();
}

void Blaze::Attack(Player* player)
{
    Uint32 currenTime = SDL_GetTicks();
    if( currenTime - lastAttackTime >= ATTACK_COOLDOWN )
    {
        SDL_Rect playeRect = player->getDestRect();
        SDL_Rect enemyRect = getDestRect();
        if(SDL_HasIntersection(&playeRect, &enemyRect))
        {
            player->takeDamage(damage);
            lastAttackTime = currenTime;
        }
    }
}
