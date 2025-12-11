#include "selectRole.h"
#include "game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <list>
#include <random>
#include <iomanip>
#include <sstream> 
#include "menu.h"
#include "BattleField.h"



selectRole::selectRole() : game(game::getInstance())
{
    
}

selectRole::~selectRole()
{
    
}

void selectRole::init()
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
    selection1 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/illustrations/player1.png");
    ensure = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/gui/ensure.png");
    selectrole = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/gui/selectRole.png");
    left = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/gui/left.png");
    right = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/gui/right.png");
    profile1 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/profiles/profile1.png");
    
    
}

void selectRole::clean()
{

    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
    }

    if (selection1 != nullptr)
    {
        SDL_DestroyTexture(selection1);
    }

    if (ensure != nullptr)
    {
        SDL_DestroyTexture(ensure);
    }

    if (selectrole != nullptr)
    {
        SDL_DestroyTexture(selectrole);
    }

    if (left != nullptr)
    {
        SDL_DestroyTexture(left);
    }

    if (right != nullptr)
    {
        SDL_DestroyTexture(right);
    }

    if (profile1 != nullptr)
    {
        SDL_DestroyTexture(profile1);
    }
    
}

void selectRole::update(float deltaTime)
{
    keyboardControl();
}

void selectRole::render()
{
    renderBackground();
    renderSelections();
    renderUI();
}

void selectRole::handleEvents(SDL_Event* event)
{
    if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        game::getInstance().changeScene(new menu());
    }
}

void selectRole::keyboardControl()
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 

    if ((keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_LEFT]) && !keyUp)
    {
        keyUp = true;
    }
    if (!keyboardState[SDL_SCANCODE_UP] && !keyboardState[SDL_SCANCODE_LEFT])
    {
        keyUp = false;
    }

    if ((keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_RIGHT]) && !keyDown)
    {
        keyDown = true;
    }
    if (!keyboardState[SDL_SCANCODE_DOWN] && !keyboardState[SDL_SCANCODE_RIGHT])
    {
        keyDown = false;
    }
    if(keyboardState[SDL_SCANCODE_Z] && !keyZ)
    {
        keyZ = true;
        game::getInstance().changeScene(new BattleField(0));
    }
    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;   
    }
    
}

void selectRole::renderBackground()
{
    SDL_RenderCopy(game::getInstance().getRenderer(), background, NULL, NULL);
}

void selectRole::renderSelections()
{
    SDL_Rect illustrationRect = { (WINDOW_WIDTH - ILLUSTRATION_WIDTH) / 2 - 200, (WINDOW_HEIGHT - ILLUSTRATION_HEIGHT) / 2, ILLUSTRATION_WIDTH, ILLUSTRATION_HEIGHT };
    SDL_RenderCopy(game::getInstance().getRenderer(), selection1, NULL, &illustrationRect);
    SDL_Rect profileRect = { (WINDOW_WIDTH - ILLUSTRATION_WIDTH) / 2 + ILLUSTRATION_WIDTH - 256, (WINDOW_HEIGHT - PROFILE_HEIGHT) / 2, PROFILE_WIDTH, PROFILE_HEIGHT };
    SDL_RenderCopy(game::getInstance().getRenderer(), profile1, NULL, &profileRect);
}

void selectRole::renderUI()
{
    SDL_Rect ensureRect = { (WINDOW_WIDTH - menuW) / 2, ILLUSTRATION_HEIGHT + 32, menuW, menuH };
    SDL_RenderCopy(game::getInstance().getRenderer(), ensure, NULL, &ensureRect);

    SDL_Rect selectroleRect = { (WINDOW_WIDTH - menuW) / 2, 16, menuW, menuH };
    SDL_RenderCopy(game::getInstance().getRenderer(), selectrole, NULL, &selectroleRect);

    SDL_Rect leftRect = { 64, (WINDOW_HEIGHT - 64) / 2, 64, 64 };
    SDL_RenderCopy(game::getInstance().getRenderer(), left, NULL, &leftRect);

    SDL_Rect rightRect = { WINDOW_WIDTH - 64 - 64, (WINDOW_HEIGHT - 64) / 2, 64, 64 };
    SDL_RenderCopy(game::getInstance().getRenderer(), right, NULL, &rightRect);
}
