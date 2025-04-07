#include "Player.h"
#include "Collision.h"
#include "TextureManager.h"
#include "vector"
#include "Bullet.h"
#include "MapData.h"
#include "Game.h"


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
}

void Player::Render()
{
    SDL_Rect renderPos = { destRect.x - Camera::camera.x, destRect.y - Camera::camera.y, destRect.w, destRect.h};
    TextureManager::Draw(objTexture, srcRect, renderPos);
}

void Player::handleEvent(SDL_Event& event, BulletManager& bulletManager)
{
    if(Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE)
    {
        int dx = 0, dy = 0;
        if(direction == UP)
        {
            dx = 0;
            dy = -10;
        }
        if(direction == DOWN) {
            dx = 0;
            dy = 10;
        }
        if(direction == LEFT) {
            dx = -10;
            dy = 0;
        }
        if(direction == RIGHT) {
            dx = 10;
            dy = 0;
        }

        bulletManager.addBullet(xpos + TILE_SIZE/2, ypos + TILE_SIZE/2, dx, dy, "assets/images/dot.bmp");
    }
    else if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_w:
            yvel -= PLAYER_VEL;
            direction = UP;
            break;
        case SDLK_s:
            yvel += PLAYER_VEL;
            direction = DOWN;
            break;
        case SDLK_a:
            xvel -= PLAYER_VEL;
            direction = LEFT;
            break;
        case SDLK_d:
            xvel += PLAYER_VEL;
            direction = RIGHT;
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
    health -= damage;
}
