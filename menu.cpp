#include "menu.h"
#include "game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <list>
#include <random>
#include <iomanip>
#include <sstream> 
#include "BattleField.h"
#include "selectRole.h"
#include "selectLevel.h"



menu::menu() : game(game::getInstance())
{
    
}

menu::~menu()
{
    
}

void menu::init()
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
    menu1 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuStory.png");
    menu1_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuStorySelected.png");
    menu2 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuTrain.png");
    menu2_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuTrainSelected.png");
    menu3 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuUpgrade.png");
    menu3_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuUpgradeSelected.png");
    menu4 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuMusic.png");
    menu4_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuMusicSelected.png");
    menu5 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuOptions.png");
    menu5_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuOptionsSelected.png");
    menu6 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuQuit.png");
    menu6_ = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menu/menuQuitSelected.png");
    
}

void menu::clean()
{
    if (title != nullptr)
    {
        SDL_DestroyTexture(title);
    }

    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
    }

    if (menu1 != nullptr)
    {
        SDL_DestroyTexture(menu1);
    }

    if (menu1_ != nullptr)
    {
        SDL_DestroyTexture(menu1_);
    }

    if (menu2 != nullptr)
    {
        SDL_DestroyTexture(menu2);
    }

    if (menu2_ != nullptr)
    {
        SDL_DestroyTexture(menu2_);
    }

    if (menu3 != nullptr)
    {
        SDL_DestroyTexture(menu3);
    }

    if (menu3_ != nullptr)
    {
        SDL_DestroyTexture(menu3_);
    }

    if (menu4 != nullptr)
    {
        SDL_DestroyTexture(menu4);
    }

    if (menu4_ != nullptr)
    {
        SDL_DestroyTexture(menu4_);
    }

    if (menu5 != nullptr)
    {
        SDL_DestroyTexture(menu5);
    }

    if (menu5_ != nullptr)
    {
        SDL_DestroyTexture(menu5_);
    }

    if (menu6 != nullptr)
    {
        SDL_DestroyTexture(menu6);
    }

    if (menu6_ != nullptr)
    {
        SDL_DestroyTexture(menu6_);
    }
}

void menu::update(float deltaTime)
{
    keyboardControl();
}

void menu::render()
{
    renderTitle_Background();
    renderSelections();
}

void menu::handleEvents(SDL_Event* event)
{
    if (event->key.keysym.scancode == SDL_SCANCODE_Z)
    {
        if (selection == 6)
        {
            game::getInstance().quit();
        }
    }
}

void menu::keyboardControl()
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 

    //判断是否按下上键选择菜单项
    if (keyboardState[SDL_SCANCODE_UP] && !keyUp)
    {
        if (selection > 1)
        {
            selection--;
        }
        else
        {
            selection = 6;
        }
        keyUp = true;
    }

    if (!keyboardState[SDL_SCANCODE_UP])
    {
        keyUp = false;
    }

    if (keyboardState[SDL_SCANCODE_DOWN] && !keyDown)
    {
        if (selection < 6)
        {
            selection++;
        }
        else
        {
            selection = 1;
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
            //切换至selectLevel场景
            game::getInstance().changeScene(new selectLevel());

        }

        if (selection == 2)
        {
            //切换至battlefield场景
            keyZ = true;  
            game::getInstance().changeScene(new selectRole());
        }

        if (selection == 3)
        {
            
        }

        if (selection == 4)
        {
            
        }

        if (selection == 5)
        {
            game::getInstance().changeScene(new BattleField(1));
        }

        if (selection == 6)
        {
            //退出游戏
            game::getInstance().quit();
        }

        keyZ = true;
    }

    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;
    }
    
}

void menu::renderTitle_Background()
{
    SDL_RenderCopy(game::getInstance().getRenderer(), background, NULL, NULL);
    SDL_Rect titleRect = { titleX, titleY, titleW, titleH };
    SDL_RenderCopy(game::getInstance().getRenderer(), title, NULL, &titleRect);
}

void menu::renderSelections()
{
    SDL_Rect selection1Rect = { menuX, menuY, menuW, menuH };
    SDL_Rect selection2Rect = { menuX, menuY + menuH, menuW, menuH };
    SDL_Rect selection3Rect = { menuX, menuY + menuH * 2, menuW, menuH };
    SDL_Rect selection4Rect = { menuX, menuY + menuH * 3, menuW, menuH };
    SDL_Rect selection5Rect = { menuX, menuY + menuH * 4, menuW, menuH };
    SDL_Rect selection6Rect = { menuX, menuY + menuH * 5, menuW, menuH };

    SDL_Rect selection1Rect_ = { menuX - menuInflate, menuY - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    SDL_Rect selection2Rect_ = { menuX - menuInflate, menuY + menuH - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    SDL_Rect selection3Rect_ = { menuX - menuInflate, menuY + menuH * 2 - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    SDL_Rect selection4Rect_ = { menuX - menuInflate, menuY + menuH * 3 - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    SDL_Rect selection5Rect_ = { menuX - menuInflate, menuY + menuH * 4 - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    SDL_Rect selection6Rect_ = { menuX - menuInflate, menuY + menuH * 5 - menuInflateY, menuW + menuInflate * 2, menuH + menuInflateY * 2 };
    

    if (selection != 1)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu1, NULL, &selection1Rect);
    }
    if (selection != 2)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu2, NULL, &selection2Rect);
    }
    if (selection != 3)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu3, NULL, &selection3Rect);
    }
    if (selection != 4)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu4, NULL, &selection4Rect);
    }
    if (selection != 5)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu5, NULL, &selection5Rect);
    }
    if (selection != 6)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu6, NULL, &selection6Rect);
    }

    if (selection == 1)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu1_, NULL, &selection1Rect_);
    }
    if (selection == 2)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu2_, NULL, &selection2Rect_);
    }
    if (selection == 3)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu3_, NULL, &selection3Rect_);
    }
    if (selection == 4)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu4_, NULL, &selection4Rect_);
    }
    if (selection == 5)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu5_, NULL, &selection5Rect_);
    }
    if (selection == 6)
    {
        SDL_RenderCopy(game::getInstance().getRenderer(), menu6_, NULL, &selection6Rect_);
    }


}
