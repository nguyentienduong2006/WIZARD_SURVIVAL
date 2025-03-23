#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Game.h"
#include "GameObject.h"

class Player : public GameObject
{
public:

    Player(const char* textureSheet, int x, int y);
    ~Player() {}
    void Update() override;
    void Render() override;
    void handleEvent() override;
private:
    int xpos;
    int ypos;
    int xvel;
    int yvel;
    //int direction;

    SDL_Texture* playerTexture;
    SDL_Rect srcRect, destRect;
};

#endif // _PLAYER_H_
