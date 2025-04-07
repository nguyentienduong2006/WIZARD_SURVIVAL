#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
    destRect = {xpos, ypos, TILE_SIZE, TILE_SIZE};
}




