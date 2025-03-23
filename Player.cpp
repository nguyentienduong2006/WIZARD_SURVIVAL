#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect = {64, 0, 64, 64};
    destRect = {0, 0, 64, 64};

    playerTexture = TextureManager::LoadTexture("assets/images/player.png");
}
void Player::Update()
{
    xpos+=xvel;
    ypos+=yvel;

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

    srcRect.x = frame*64;
    srcRect.y = direction*64;
}

void Player::Render()
{
    TextureManager::Draw(playerTexture, srcRect, destRect);
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
