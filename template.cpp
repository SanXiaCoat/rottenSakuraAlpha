#include "menu.h"
#include "selectLevel.h"
#include "game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <list>
#include <random>
#include <iomanip>
#include <sstream> 
#include "selectRole.h"



selectLevel::selectLevel() : game(game::getInstance())
{
    
}

selectLevel::~selectLevel()
{
    
}

void selectLevel::init()
{
    //随机数种子
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    srand((unsigned int)time(NULL));
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

    //载入图片
    title = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/title.png");
    background = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menubg.png");
    
    
}

void selectLevel::clean()
{
    if (title != nullptr)
    {
        SDL_DestroyTexture(title);
    }

    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
    }

}

void selectLevel::update(float deltaTime)
{
    keyboardControl();
}

void selectLevel::render()
{
    renderBackground();
    renderSelections();
}



void selectLevel::handleEvents(SDL_Event* event)
{
    if (event->key.keysym.scancode == SDL_SCANCODE_Z)
    {
        if (selection == 6)
        {
            game::getInstance().quit();
        }
    }
}

void selectLevel::keyboardControl()
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 

    //判断是否按下上键选择菜单项
    if (keyboardState[SDL_SCANCODE_UP] && !keyUp)
    {
        if (selection > 1)
        {
            selection--;
        }
        keyUp = true;
    }

    if (!keyboardState[SDL_SCANCODE_UP])
    {
        keyUp = false;
    }

    if (keyboardState[SDL_SCANCODE_DOWN] && !keyDown)
    {
        if (selection < 11)
        {
            selection++;
        }
        keyDown = true;
    }

    if (!keyboardState[SDL_SCANCODE_DOWN])
    {
        keyDown = false;
    }

    if (keyboardState[SDL_SCANCODE_Z] && !keyZ)
    {
        if (selection == 1)
        {
            
        }

        if (selection == 2)
        {

        }

        if (selection == 3)
        {
            
        }

        if (selection == 4)
        {
            
        }

        if (selection == 5)
        {
            
        }

        if (selection == 6)
        {

        }

        keyZ = true;
    }

    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;
    }
    
}

void selectLevel::renderBackground()
{
    SDL_RenderCopy(game::getInstance().getRenderer(), background, NULL, NULL);
    SDL_Rect titleRect = { titleX, titleY, titleW, titleH };
    SDL_RenderCopy(game::getInstance().getRenderer(), title, NULL, &titleRect);
}

void selectLevel::renderSelections()
{
    
}
