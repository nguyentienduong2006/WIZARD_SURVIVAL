#include "Player.h"
#include "Collision.h"
#include "TextureManager.h"
#include "vector"
#include "Bullet.h"
#include "MapData.h"
#include "Game.h"
#include "BulletManager.h"
#include <vector>


Player::Player(const char* textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
    health = 100;
}
void Player::Update()
{
    xpos += xvel;
    ypos += yvel;

    if( xpos < 0 || xpos + TILE_SIZE > MAP_WIDTH || touchesWall(xpos, ypos, MapData::lv1) )
    {
        xpos -= xvel;
    }
    if( ypos < 0 || ypos + TILE_SIZE > MAP_HEIGHT || touchesWall(xpos, ypos, MapData::lv1) )
    {
        ypos -= yvel;
    }


    destRect.x = xpos;
    destRect.y = ypos;
    //ANIMATION
    if( xvel != 0 || yvel != 0 )
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

    //Camera update
    Camera::camera.x = xpos + (TILE_SIZE/2) - (SCREEN_WIDTH / 2);
    Camera::camera.y = ypos + (TILE_SIZE/2) - (SCREEN_HEIGHT / 2);

    if(Camera::camera.x < 0) Camera::camera.x = 0;
    if(Camera::camera.y < 0) Camera::camera.y = 0;
    if(Camera::camera.x > MAP_WIDTH - Camera::camera.w) Camera::camera.x = MAP_WIDTH - Camera::camera.w;
    if(Camera::camera.y > MAP_HEIGHT - Camera::camera.h) Camera::camera.y = MAP_HEIGHT - Camera::camera.h;

    if(isHit && SDL_GetTicks() - hitTime >= 200)
    {
        isHit = false;
    }
}

void Player::Render()
{
    if(isHit)
    {
        SDL_SetTextureColorMod(objTexture, 255, 100, 100);
    }
    else
    {
        SDL_SetTextureColorMod(objTexture, 255, 255, 255);
    }
    SDL_Rect renderPos = { destRect.x - Camera::camera.x, destRect.y - Camera::camera.y, destRect.w, destRect.h};
    TextureManager::Draw(objTexture, srcRect, renderPos);
}

void Player::handleEvent(BulletManager& bulletManager, Mix_Chunk* shootSound)
{
    if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE && Game::event.key.repeat == 0)
    {
        int dx = 0, dy = 0;
        if(direction == E_UP)
        {
            dx = 0;
            dy = -10;
        }
        if(direction == E_DOWN) {
            dx = 0;
            dy = 10;
        }
        if(direction == E_LEFT) {
            dx = -10;
            dy = 0;
        }
        if(direction == E_RIGHT) {
            dx = 10;
            dy = 0;
        }

        bulletManager.addBullet(xpos + TILE_SIZE/2 - 40/2, ypos + TILE_SIZE/2 - 40/2 + 10 , dx, dy, "assets/images/fireball.png", false);
        if(shootSound) Mix_PlayChannel(-1, shootSound, 0);
    }
    else if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_w:
            yvel -= PLAYER_VEL;
            direction = E_UP;
            break;
        case SDLK_s:
            yvel += PLAYER_VEL;
            direction = E_DOWN;
            break;
        case SDLK_a:
            xvel -= PLAYER_VEL;
            direction = E_LEFT;
            break;
        case SDLK_d:
            xvel += PLAYER_VEL;
            direction = E_RIGHT;
            break;
        }
    }
    else if(Game::event.type == SDL_KEYUP && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_w:
            yvel += PLAYER_VEL;
            break;
        case SDLK_s:
            yvel -= PLAYER_VEL;
            break;
        case SDLK_a:
            xvel += PLAYER_VEL;
            break;
        case SDLK_d:
            xvel -= PLAYER_VEL;
            break;
        }
    }

}

void Player::takeDamage(int damage)
{
    isHit = true;
    hitTime = SDL_GetTicks();
    health -= damage;
}

void Player::checkBulletCollision(BulletManager& bulletManager)
{
    auto& bullets = bulletManager.getBullets();
    for(auto bulletIt = bullets.begin(); bulletIt != bullets.end();)
    {
        bool isEnemyBullet = (*bulletIt)->isEnemyBullet();
        if(isEnemyBullet)
        {
            if(*bulletIt == nullptr)
            {
                bulletIt = bullets.erase(bulletIt);
                continue;
            }
            SDL_Rect bulletRect = (*bulletIt)->getDestRect();
            SDL_Rect playerRect = getDestRect();
            if(SDL_HasIntersection(&bulletRect, &playerRect))
            {
                takeDamage(5);
                delete *bulletIt;
                bulletIt = bullets.erase(bulletIt);
            }
            else bulletIt++;
        }
        else bulletIt++;
    }
}
