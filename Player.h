#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Game.h"
#include "GameObject.h"
enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Player : public GameObject
{
public:

    Player(const char* textureSheet, int x, int y);
    ~Player() {}
    void Update() override;
    void Render() override;
    void handleEvent() override;

    static const int PLAYER_VEL = 5;
    SDL_Rect getdestRect();
private:
    int xpos;
    int ypos;
    int xvel;
    int yvel;
    //int direction;

    SDL_Texture* playerTexture;
    SDL_Rect srcRect, destRect;

    int frame = 0;
    int frameCount = 4;
    int frameDelay = 7;
    int frameTimer = 0;
    Direction direction = DOWN;
};

#endif // _PLAYER_H_
