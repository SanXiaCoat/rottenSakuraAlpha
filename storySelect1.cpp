#include "selectLevel.h"
#include "storySelect1.h"
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



storySelect1::storySelect1() : game(game::getInstance())
{
    
}

storySelect1::~storySelect1()
{
    
}

void storySelect1::init()
{
    //随机数种子
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    srand((unsigned int)time(NULL));
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

    //载入图片
    background = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menubg.png");

    if (statusFont != nullptr) 
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurfaceTitle = TTF_RenderUTF8_Solid(statusFont, "选择进度", textColor);
        SDL_Surface* section1textSurface = TTF_RenderUTF8_Solid(statusFont, "S-1", textColor);   

        if (textSurfaceTitle != nullptr) 
        {
            title = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceTitle);
            SDL_FreeSurface(textSurfaceTitle);
        }
        if (section1textSurface != nullptr) 
        {
            section1text = SDL_CreateTextureFromSurface(game.getRenderer(), section1textSurface);
            SDL_FreeSurface(section1textSurface);
        }
    }

    section1 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/levelIcons/s1.png");
    
}

void storySelect1::clean()
{
    if (statusFont != nullptr)
    {
        TTF_CloseFont(statusFont);
    }

    if (title != nullptr)
    {
        SDL_DestroyTexture(title);
    }

    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
    }

    if (section1 != nullptr)
    {
        SDL_DestroyTexture(section1);
    }

    if (section1text != nullptr)
    {
        SDL_DestroyTexture(section1text);
    }

}

void storySelect1::handleEvents(SDL_Event *event)
{
}

void storySelect1::update(float deltaTime)
{
    keyboardControl();
}

void storySelect1::render()
{
    renderBackground();
    renderSelections();
}



void storySelect1::keyboardControl()
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
        if (selection < 4)
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
        keyZ = true;
    }

    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;
    }

    //esc
    if (keyboardState[SDL_SCANCODE_ESCAPE])
    {
        game::getInstance().changeScene(new selectLevel());
    }
    
}

void storySelect1::renderBackground()
{
    SDL_RenderCopy(game::getInstance().getRenderer(), background, NULL, NULL);
    int titleW_, titleH_;
    SDL_QueryTexture(title, NULL, NULL, &titleW_, &titleH_);
    SDL_Rect titleRect = 
    { 
        (WINDOW_WIDTH - titleW_) / 2, 
        50, 
        titleW_, 
        titleH_ 
    };
    SDL_RenderCopy(game::getInstance().getRenderer(), title, NULL, &titleRect);
}

void storySelect1::renderSelections()
{
    int s1W, s1H;
    SDL_QueryTexture(section1text, NULL, NULL, &s1W, &s1H); 
    SDL_Rect s1Rect = 
    { 
        levelIconSize / 2, 
        (WINDOW_HEIGHT - levelIconSize) / 2 - 30, 
        levelIconSize, 
        levelIconSize 
    };
    SDL_Rect s1TextRect =
    {
        levelIconSize / 2 + (levelIconSize - s1W) / 2,
        (WINDOW_HEIGHT - s1H) / 2 - 30,
        s1W,
        s1H
    };
    SDL_RenderCopy(game::getInstance().getRenderer(), section1, NULL, &s1Rect);
    SDL_RenderCopy(game::getInstance().getRenderer(), section1text, NULL, &s1TextRect);
}
