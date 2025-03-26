#include "Map.h"
#include "TextureManager.h"

int lv1[MAP_TILE_HEIGHT][MAP_TILE_WIDTH] =
{
{3,0,0,0,4,5,0,0,4,5,0,0,8,0,0,8,0,0,0,0,0,0,4,5,0,0,0,0,0,0},
{3,3,3,0,12,13,0,0,12,13,0,0,16,0,0,16,0,0,11,0,0,0,12,13,0,0,0,0,0,3},
{0,0,3,0,0,0,8,2,0,0,4,5,1,8,0,0,3,3,3,0,8,0,2,0,11,0,0,3,3,3},
{0,9,0,3,0,7,16,0,1,0,12,13,0,16,11,2,3,3,3,0,16,11,0,0,0,0,3,3,0,0},
{0,0,0,3,3,3,0,0,8,0,0,8,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,0,0,0},
{0,4,5,0,0,3,3,0,16,0,0,16,0,0,11,3,3,3,3,3,0,0,8,0,7,3,0,0,0,0},
{0,12,13,0,8,0,3,3,0,11,2,0,8,0,0,3,3,3,3,3,0,0,16,0,3,3,0,4,5,0},
{0,2,2,0,16,0,0,3,3,0,1,0,16,0,7,3,3,3,3,3,0,0,0,3,3,0,0,12,13,0},
{0,0,0,1,0,0,9,0,3,3,0,11,0,0,3,3,3,3,3,3,0,3,3,3,0,0,0,0,0,0},
{0,0,0,0,8,2,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,11,2,0,0,0},
{0,0,4,5,16,0,0,16,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,9,8,0,1,0,0,0},
{0,0,12,13,0,0,0,1,9,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,16,0,0,0,0,0},
{0,0,0,0,0,0,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,4,5,0},
{0,0,0,2,0,8,0,16,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,11,0,0,12,13,0},
{0,1,8,0,0,16,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0},
{0,0,16,4,5,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,0,0,0,0},
{0,0,0,12,13,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,16,1,2,0,0},
{0,0,0,0,0,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,0,0,0,0,0,0},
{0,0,4,5,0,0,16,0,9,0,3,3,3,3,3,3,3,3,3,3,0,0,0,16,0,0,4,5,0,0},
{0,0,12,13,0,1,2,0,0,8,0,0,3,3,3,0,0,0,0,8,0,9,0,0,0,0,12,13,0,0},
{0,0,0,0,0,0,0,0,0,16,0,0,8,1,0,0,8,0,0,16,0,0,0,0,1,0,0,0,0,0},
{0,1,0,0,8,0,0,0,0,0,0,0,16,1,0,0,16,0,0,8,0,0,0,0,0,8,0,0,1,0},
{0,0,0,0,16,0,0,4,5,0,0,0,0,0,0,0,0,0,1,16,0,0,0,4,5,16,0,0,0,0},
{0,0,0,0,0,0,0,12,13,0,0,0,8,0,0,4,5,0,0,0,0,0,0,12,13,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,12,13,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


Map::Map()
{
    ground = TextureManager::LoadTexture("assets/maps/1_ground.png");
    grass = TextureManager::LoadTexture("assets/maps/2_grass.png");
    flower = TextureManager::LoadTexture("assets/maps/3_flower.png");
    road = TextureManager::LoadTexture("assets/maps/4_road.png");
    bigbush_1 = TextureManager::LoadTexture("assets/maps/5_bigbush_1.png");
    bigbush_2 = TextureManager::LoadTexture("assets/maps/6_bigbush_2.png");
    bigbush_3 = TextureManager::LoadTexture("assets/maps/13_bigbush_3.png");
    bigbush_4 = TextureManager::LoadTexture("assets/maps/14_bigbush_4.png");
    sign = TextureManager::LoadTexture("assets/maps/8_sign.png");
    tree_1 = TextureManager::LoadTexture("assets/maps/9_tree_1.png");
    tree_2 = TextureManager::LoadTexture("assets/maps/17_tree_2.png");
    bush1 = TextureManager::LoadTexture("assets/maps/10_bush1.png");
    bush2 = TextureManager::LoadTexture("assets/maps/12_bush2.png");

    LoadMap(lv1);

    src.x = src.y = 0;
    src.w = src.h = TILE_SIZE;
    dest.x = dest.y = 0;
    dest.w = dest.h = TILE_SIZE;
}

Map::~Map()
{

}

void Map::LoadMap(int arr[MAP_TILE_HEIGHT][MAP_TILE_WIDTH])
{
    for(int row = 0; row < MAP_TILE_HEIGHT; ++row)
    {
        for(int col = 0; col < MAP_TILE_WIDTH ; ++col)
        {
            map[row][col] = arr[row][col];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;

    for(int row = 0; row < MAP_TILE_HEIGHT; ++row)
    {
        for(int col = 0; col < MAP_TILE_WIDTH; ++col)
        {
            type = map[row][col];

            dest.x = col*64 - Camera::camera.x;
            dest.y = row*64 - Camera::camera.y;

            switch(type)
            {
            case 0:
                TextureManager::Draw(ground, src, dest);
                break;
            case 1:
                TextureManager::Draw(grass, src, dest);
                break;
            case 2:
                TextureManager::Draw(flower, src, dest);
                break;
            case 3:
                TextureManager::Draw(road, src, dest);
                break;
            case 4:
                TextureManager::Draw(bigbush_1, src, dest);
                break;
            case 5:
                TextureManager::Draw(bigbush_2, src, dest);
                break;
            case 7:
                TextureManager::Draw(sign, src, dest);
                break;
            case 8:
                TextureManager::Draw(tree_1, src, dest);
                break;
            case 9:
                TextureManager::Draw(bush1, src, dest);
                break;
            case 11:
                TextureManager::Draw(bush2, src, dest);
                break;
            case 12:
                TextureManager::Draw(bigbush_3, src, dest);
                break;
            case 13:
                TextureManager::Draw(bigbush_4, src, dest);
                break;
            case 16:
                TextureManager::Draw(tree_2, src, dest);
                break;
            }
        }
    }
}
