#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect = {0, TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    destRect = {0, 0, TILE_WIDTH, TILE_HEIGHT};

    playerTexture = TextureManager::LoadTexture("assets/images/player.png");
}
void Player::Update()
{
    int newX = xpos + xvel;
    int newY = ypos + yvel;

    if(newX >=0 && newX + TILE_WIDTH <= MAP_WIDTH)
        xpos = newX;
    if(newY >= 0 && newY + TILE_HEIGHT <= MAP_HEIGHT)
        ypos = newY;

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

    srcRect.x = frame*TILE_WIDTH;
    srcRect.y = direction*TILE_HEIGHT;

    Game::camera.x = xpos + (TILE_WIDTH/2) - (SCREEN_WIDTH / 2);
    Game::camera.y = ypos + (TILE_HEIGHT/2) - (SCREEN_HEIGHT / 2);

    if(Game::camera.x < 0) Game::camera.x = 0;
    if(Game::camera.y < 0) Game::camera.y = 0;
    if(Game::camera.x > MAP_WIDTH - Game::camera.w) Game::camera.x = MAP_WIDTH - Game::camera.w;
    if(Game::camera.y > MAP_HEIGHT - Game::camera.h) Game::camera.y = MAP_HEIGHT - Game::camera.h;
}

void Player::Render()
{
    SDL_Rect renderPos = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h};
    TextureManager::Draw(playerTexture, srcRect, renderPos);
}

void Player::handleEvent()
{
    if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
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
