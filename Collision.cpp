#include "Collision.h"

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    topA = a.y;
    bottomA = a.y + a.h;
    leftA = a.x;
    rightA = a.x + a.w;

    topB = b.y;
    bottomB = b.y + b.h;
    leftB = b.x;
    rightB = b.x + b.w;

    if(bottomA <= topB)
    {
        return false;
    }
    if(topA >= bottomB)
    {
        return false;
    }
    if(rightA <= leftB)
    {
        return false;
    }
    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool touchesWall(int newX, int newY, int lv1[MAP_TILE_HEIGHT][MAP_TILE_WIDTH])
{
    for (int i = 0; i < MAP_TILE_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_TILE_WIDTH; ++j)
        {
            if (lv1[i][j] == 4 || lv1[i][j] ==  5 || lv1[i][j] == 7 || lv1[i][j] == 8 || lv1[i][j] == 9 || lv1[i][j] == 11 || lv1[i][j] == 12 || lv1[i][j] == 13 || lv1[i][j] == 16)
            {
                SDL_Rect tileBox = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

                SDL_Rect playerBox = { newX+1, newY+1, TILE_SIZE-2, TILE_SIZE-2 };
                if (checkCollision(playerBox, tileBox))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
