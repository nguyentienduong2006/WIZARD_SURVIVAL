#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int TILE_SIZE = 64;

const int MAP_WIDTH = 1920;
const int MAP_HEIGHT = 1600;

const int MAP_TILE_WIDTH = 30;
const int MAP_TILE_HEIGHT = 25;

const int BULLET_VEL = 10;

const int PLAYER_HEALTH = 100;

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

enum EnemyDirection
{
    E_UP,
    E_RIGHT,
    E_DOWN,
    E_LEFT
};

#endif // _CONFIG_H_
