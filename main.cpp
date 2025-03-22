#include "Game.h"

int main(int argc, char* args[])
{
    Game WizG;
    WizG.init();
    while(WizG.isRunning())
    {
        WizG.handleEvents();
        WizG.update();
        WizG.render();
    }
    WizG.close();
    return 0;
}
