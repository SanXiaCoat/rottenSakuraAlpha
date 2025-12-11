#include "game.h"
#include "configs.h"
#include "menu.h"
#include "BattleField.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

game::game()
{
    
}

game::~game()
{
    clean();
}

// 游戏主运行函数
void game::run()
{
    while(isRunning)
    {
        Uint32 frameStart = SDL_GetTicks();
        SDL_Event event;
        handleEvents(&event);
        update(deltaTime);
        render();
        Uint32 frameTimeUsed = SDL_GetTicks() - frameStart;
        if (frameTimeUsed < frameTime)
        {
            SDL_Delay(frameTime - frameTimeUsed);
            deltaTime = frameTime / 1000.0f;
        }
        else
        {
            deltaTime = frameTimeUsed / 1000.0f;
        }
    }
}
void game::init()
{
    frameTime = 1000 / fps;
    //SDL Initialization
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    //SDL_image Initialization
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {    
        SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        isRunning = false;
    }

    // 初始化SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        isRunning = false; 
    }

    //Create window
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    //Create renderer   
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) 
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }

    //设置当前场景
    // currentScene = new BattleField();
    currentScene = new menu();
    currentScene->init();
}   

void game::clean()
{
    if (currentScene != nullptr) 
    {
        currentScene->clean();
        delete currentScene;
    }

    //SDL_Image 清理
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void game::changeScene(scene *scene)
{
    if (currentScene != nullptr) {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}

void game::handleEvents(SDL_Event* event)
{
    while (SDL_PollEvent(event)) 
        {
            if (event->type == SDL_QUIT) 
            {
                isRunning = false;
            }
            currentScene->handleEvents(event);
        }
}

void game::update(float deltaTime)
{
    currentScene->update(deltaTime);
}

void game::render()
{
    //清屏
    SDL_RenderClear(renderer);
    currentScene->render();
    //更新屏幕
    SDL_RenderPresent(renderer);
}
