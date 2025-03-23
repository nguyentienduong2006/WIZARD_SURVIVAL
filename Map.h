#include "Game.h"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][20]);
    void DrawMap();
private:

    SDL_Rect src, dest;

    SDL_Texture* dirt;
    SDL_Texture* bush;

    int map[20][20];
};
