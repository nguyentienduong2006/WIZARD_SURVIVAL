#ifndef _MAP_H_
#include "config.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[MAP_TILE_HEIGHT][MAP_TILE_WIDTH]);
    void DrawMap();
private:
    SDL_Texture* ground;
    SDL_Texture* grass;
    SDL_Texture* flower;
    SDL_Texture* road;
    SDL_Texture* bigbush_1;
    SDL_Texture* bigbush_2;
    SDL_Texture* bigbush_3;
    SDL_Texture* bigbush_4;
    SDL_Texture* sign;
    SDL_Texture* tree_1;
    SDL_Texture* tree_2;
    SDL_Texture* bush1;
    SDL_Texture* bush2;

    SDL_Rect src, dest;

    int map[MAP_TILE_HEIGHT][MAP_TILE_WIDTH];
};

#endif // _MAP_H_
