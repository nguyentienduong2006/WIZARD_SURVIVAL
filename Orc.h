#ifndef _ORC_H_
#define _ORC_H_

#include "Enemy.h"
#include "TextureManager.h"

class Orc : public Enemy
{
    public:
    Orc(int x, int y) : Enemy("assets/images/orc_test.png", x, y, 2, 100) {}

    void Update() override {}

    void Update(Player& player) override
    {
        if(player.getX() > xpos) xpos += speed;
        else if(player.getX() < xpos) xpos -= speed;

        if(player.getY() > ypos) ypos += speed;
        else if(player.getY() < ypos) ypos -= speed;

        if(xpos < 0 || xpos + 64 > MAP_WIDTH) xpos -= speed;
        if(ypos < 0 || ypos + 64 > MAP_HEIGHT) ypos -= speed;
    }

    void Render() override {
        SDL_Rect destRect = {xpos, ypos, 64, 64};
        TextureManager::Draw(textureSheet, NULL, destRect);
    }
};

#endif // _ORC_H_
