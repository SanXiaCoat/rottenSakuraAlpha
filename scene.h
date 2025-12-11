#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class scene
{
public:
    scene() = default;
    virtual ~scene() = default;
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handleEvents(SDL_Event* event) = 0;
};