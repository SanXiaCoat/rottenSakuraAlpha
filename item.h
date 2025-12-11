#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "configs.h"

struct power
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0, 0};
    int width = powerSize;
    int height = powerSize;
    int speed = powerSpeed;
    float value = 0;
    int sizeTrue = 0;
    int acceleration = 2;
    int accelerationY = 2;
};