#include "storySelect1.h"
#include "s1.h"
#include "game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <list>
#include <random>
#include <iomanip>
#include <sstream> 

s1::s1() : game(game::getInstance())
{
    
}

s1::~s1()
{
    
}

void s1::init()
{
    //随机数种子
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    srand((unsigned int)time(NULL));
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

    //载入图片
    town = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menubg.png");
    farmland = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter1.png");
    town_night = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter2.png");
    town_light = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter3.png");
    wild = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter4.png");
    mountain = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter5.png");
    CyanBean = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/self/CyanBean.png");
    
    
}

void s1::clean()
{
    SDL_DestroyTexture(town);
    SDL_DestroyTexture(farmland);
    SDL_DestroyTexture(town_night);
    SDL_DestroyTexture(town_light);
    SDL_DestroyTexture(wild);
    SDL_DestroyTexture(mountain);
    SDL_DestroyTexture(CyanBean);
}

void s1::update(float deltaTime)
{
    keyboardControl();
}

void s1::render()
{
    renderBackground();
    renderIllustrations();
    renderStories();
}



void s1::handleEvents(SDL_Event* event)
{
}

void s1::keyboardControl()
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 

    //判断是否按下上键播放剧情
    if (keyboardState[SDL_SCANCODE_UP] && !keyUp)
    {
        if (steps > 1)
        {
            steps--;
        }
        keyUp = true;
    }

    if (!keyboardState[SDL_SCANCODE_UP])
    {
        keyUp = false;
    }

    if (keyboardState[SDL_SCANCODE_DOWN] && !keyDown)
    {
        if (steps < 28)
        {
            steps++;
        }
        keyDown = true;
    }

    if (!keyboardState[SDL_SCANCODE_DOWN])
    {
        keyDown = false;
    }

    if (keyboardState[SDL_SCANCODE_Z] && !keyZ)
    {   
        keyZ = true;
    }

    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;
    }
    
}

void s1::renderBackground()
{
    
}

void s1::renderIllustrations()
{
}

void s1::renderStories()
{
}

