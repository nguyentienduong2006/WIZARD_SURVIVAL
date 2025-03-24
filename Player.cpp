#include "Player.h"
#include "Collision.h"
#include "TextureManager.h"
#include "vector"
#include "Bullet.h"

BulletManager bulletManager;
int arr[MAP_TILE_HEIGHT][MAP_TILE_WIDTH] =
{
{3,0,0,0,4,5,0,0,4,5,0,0,8,0,0,8,0,0,0,0,0,0,4,5,0,0,0,0,0,0},
{3,3,3,0,12,13,0,0,12,13,0,0,16,0,0,16,0,0,11,0,0,0,12,13,0,0,0,0,0,3},
{0,0,3,0,0,0,8,2,0,0,4,5,1,8,0,0,3,3,3,0,8,0,2,0,11,0,0,3,3,3},
{0,9,0,3,0,7,16,0,1,0,12,13,0,16,11,2,3,3,3,0,16,11,0,0,0,0,3,3,0,0},
{0,0,0,3,3,3,0,0,8,0,0,8,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,0,0,0},
{0,4,5,0,0,3,3,0,16,0,0,16,0,0,11,3,3,3,3,3,0,0,8,0,7,3,0,0,0,0},
{0,12,13,0,8,0,3,3,0,11,2,0,8,0,0,3,3,3,3,3,0,0,16,0,3,3,0,4,5,0},
{0,2,2,0,16,0,0,3,3,0,1,0,16,0,7,3,3,3,3,3,0,0,0,3,3,0,0,12,13,0},
{0,0,0,1,0,0,9,0,3,3,0,11,0,0,3,3,3,3,3,3,0,3,3,3,0,0,0,0,0,0},
{0,0,0,0,8,2,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,11,2,0,0,0},
{0,0,4,5,16,0,0,16,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,9,8,0,1,0,0,0},
{0,0,12,13,0,0,0,1,9,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,16,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,4,5,0},
{0,0,0,2,0,8,0,16,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,11,0,0,12,13,0},
{0,1,8,0,0,16,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0},
{0,0,16,4,5,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,0,0,0,0},
{0,0,0,12,13,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,16,1,2,0,0},
{0,0,0,0,0,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,0,0,0,0,0,0},
{0,0,4,5,0,0,16,0,9,0,3,3,3,3,3,3,3,3,3,3,0,0,0,16,0,0,4,5,0,0},
{0,0,12,13,0,1,2,0,0,8,0,0,3,3,3,0,0,0,0,8,0,9,0,0,0,0,12,13,0,0},
{0,0,0,0,0,0,0,0,0,16,0,0,8,1,0,0,8,0,0,16,0,0,0,0,1,0,0,0,0,0},
{0,1,0,0,8,0,0,0,0,0,0,0,16,1,0,0,16,0,0,8,0,0,0,0,0,8,0,0,1,0},
{0,0,0,0,16,0,0,4,5,0,0,0,0,0,0,0,0,0,1,16,0,0,0,4,5,16,0,0,0,0},
{0,0,0,0,0,0,0,12,13,0,0,0,8,0,0,4,5,0,0,0,0,0,0,12,13,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,12,13,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
Player::Player(const char* textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect = {0, TILE_SIZE, TILE_SIZE, TILE_SIZE};
    destRect = {0, 0, TILE_SIZE, TILE_SIZE};

    playerTexture = TextureManager::LoadTexture("assets/images/player.png");
}
void Player::Update()
{
    xpos += xvel;
    ypos += yvel;

    if( xpos < 0 || xpos + TILE_SIZE > MAP_WIDTH || touchesWall(xpos, ypos, arr) )
    {
        xpos -= xvel;
    }
    if( ypos < 0 || ypos + TILE_SIZE > MAP_HEIGHT || touchesWall(xpos, ypos, arr) )
    {
        ypos -= yvel;
    }


    destRect.x = xpos;
    destRect.y = ypos;

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

    Game::camera.x = xpos + (TILE_SIZE/2) - (SCREEN_WIDTH / 2);
    Game::camera.y = ypos + (TILE_SIZE/2) - (SCREEN_HEIGHT / 2);

    if(Game::camera.x < 0) Game::camera.x = 0;
    if(Game::camera.y < 0) Game::camera.y = 0;
    if(Game::camera.x > MAP_WIDTH - Game::camera.w) Game::camera.x = MAP_WIDTH - Game::camera.w;
    if(Game::camera.y > MAP_HEIGHT - Game::camera.h) Game::camera.y = MAP_HEIGHT - Game::camera.h;

    bulletManager.updateBullets();
}

void Player::Render()
{
    SDL_Rect renderPos = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h};
    TextureManager::Draw(playerTexture, srcRect, renderPos);
    bulletManager.renderBullets();
}

void Player::handleEvent()
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

SDL_Rect Player::getdestRect()
{
    return destRect;
}
