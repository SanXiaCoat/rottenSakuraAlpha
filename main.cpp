#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstring>
#include "game.h"



int main(int,char**)
{
    game &Game = game::getInstance();
    Game.init();
    Game.run();
    return 0;
}
