#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect = {0, 0, 20, 20};
    destRect = {0, 0, 20, 20};

    playerTexture = TextureManager::LoadTexture("assets/images/dot.bmp");
}
void Player::Update()
{
    xpos+=xvel;
    ypos+=yvel;

    destRect.x = xpos;
    destRect.y = ypos;
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
            yvel -= 4;
            break;
        case SDLK_s:
            yvel += 4;
            break;
        case SDLK_a:
            xvel -= 4;
            break;
        case SDLK_d:
            xvel += 4;
            break;
        }
    }
    else if(Game::event.type == SDL_KEYUP && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_w:
            yvel += 4;
            break;
        case SDLK_s:
            yvel -= 4;
            break;
        case SDLK_a:
            xvel += 4;
            break;
        case SDLK_d:
            xvel -= 4;
            break;

        }
    }
}
