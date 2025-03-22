#ifndef _GAME_H_
#define _GAME_H_
#include <SDL.h>
#include <iostream>
class Game
{
private:
    bool running;
public:
    Game();
    ~Game();
    bool init();
    void handleEvents();
    void update();
    void render();
    void close();
    bool isRunning() {return running;}

};
#endif // _GAME_H_
