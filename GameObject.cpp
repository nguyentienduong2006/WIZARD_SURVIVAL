#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
    srcRect = {0, 0, 20, 20};
    destRect = {0, 0, 20, 20};
}
GameObject::~GameObject()
{

}



void GameObject::Render()
{
    TextureManager::Draw(objTexture, srcRect, destRect);
}

void GameObject::handleEvent()
{

}
