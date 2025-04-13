#include "Mermaid.h"
#include "Collision.h"
#include "MapData.h"
#include "Player.h"
#include "cmath"
#include "camera.h"
#include "TextureManager.h"
#include "MapData.h"

Mermaid::Mermaid(int x, int y) : Enemy("assets/images/mermaid.png", x, y, 50, 2, 10)
{
}

void Mermaid::Update()
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


void Mermaid::Render()
{
    Enemy::Render();
}

void Mermaid::Attack(Player* player)
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
