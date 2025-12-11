#pragma once
#include <SDL.h>
#include "scene.h"

class game
{
public:
    static game& getInstance()
    {
        static game instance;
        return instance;
    };
    ~game();
    void run();
    void init();
    void clean();
    void changeScene(scene* scene);

    void handleEvents(SDL_Event *event);
    void update(float deltaTime);
    void render();
    bool running() { return isRunning; }  
    void quit() { isRunning = false; }                      
    SDL_Window* getWindow() { return window; }
    SDL_Renderer* getRenderer() { return renderer; }

    struct options
    {
        bool isWASDControl = 0;  
    };

private:
    game();
    //删除拷贝构造函数和赋值运算符，防止拷贝
    game(const game&) = delete;
    game& operator = (const game&) = delete;
    bool isRunning = 1;
    scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Uint32 frameTime;
    float deltaTime;
};


