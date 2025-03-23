#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "Game.h"
#include <set>

bool checkCollision(SDL_Rect a, SDL_Rect b);

bool touchesWall(int newX, int newY, int lvl1[MAP_TILE_HEIGHT][MAP_TILE_WIDTH]);

#endif // _COLLISION_H_
