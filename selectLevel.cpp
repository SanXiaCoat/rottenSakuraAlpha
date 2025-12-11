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
#include "storySelect1.h"

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
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

    //载入图片
    background = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/menubg.png");
    section1 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter1.png");
    section2 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter2.png");
    section3 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter3.png");
    section4 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter4.png");
    section5 = IMG_LoadTexture(game::getInstance().getRenderer(), "../assets/images/chapter/chapter5.png");
    
    if (statusFont != nullptr) 
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurfaceTitle = TTF_RenderUTF8_Solid(statusFont, "选择故事", textColor);
        SDL_Surface* textSurfaceLevel1 = TTF_RenderUTF8_Solid(statusFont, "魇途初启", textColor);
        SDL_Surface* textSurfaceLevel2 = TTF_RenderUTF8_Solid(statusFont, "山峦之下", textColor);
        SDL_Surface* textSurfaceLevel3 = TTF_RenderUTF8_Solid(statusFont, "暗流窥伺", textColor);
        SDL_Surface* textSurfaceLevel4 = TTF_RenderUTF8_Solid(statusFont, "远郊近宫", textColor);
        SDL_Surface* textSurfaceLevel5 = TTF_RenderUTF8_Solid(statusFont, "孽城终破", textColor);
        
        if (textSurfaceTitle != nullptr) 
        {
            title = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceTitle);
            SDL_FreeSurface(textSurfaceTitle);
        }
        if (textSurfaceLevel1 != nullptr) 
        {
            section1text = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceLevel1);
            SDL_FreeSurface(textSurfaceLevel1);
        }
        if (textSurfaceLevel2 != nullptr) 
        {
            section2text = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceLevel2);
            SDL_FreeSurface(textSurfaceLevel2);
        }
        if (textSurfaceLevel3 != nullptr)
        {
            section3text = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceLevel3);
            SDL_FreeSurface(textSurfaceLevel3);
        }
        if (textSurfaceLevel4 != nullptr)
        {
            section4text = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceLevel4);
            SDL_FreeSurface(textSurfaceLevel4);
        }
        if (textSurfaceLevel5 != nullptr)
        {
            section5text = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceLevel5);
            SDL_FreeSurface(textSurfaceLevel5);
        }
    }
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

    if (statusFont != nullptr)
    {
        TTF_CloseFont(statusFont);
    }

    if (section1text != nullptr)
    {
        SDL_DestroyTexture(section1text);
    }

    if (section2text != nullptr)
    {
        SDL_DestroyTexture(section2text);
    }

    if (section3text != nullptr)
    {
        SDL_DestroyTexture(section3text);
    }

    if (section4text != nullptr)
    {
        SDL_DestroyTexture(section4text);
    }

    if (section5text != nullptr)
    {
        SDL_DestroyTexture(section5text);
    }

    if (section1 != nullptr)
    {
        SDL_DestroyTexture(section1);
    }

    if (section2 != nullptr)
    {
        SDL_DestroyTexture(section2);
    }

    if (section3 != nullptr)
    {
        SDL_DestroyTexture(section3);
    }

    if (section4 != nullptr)
    {
        SDL_DestroyTexture(section4);
    }

    if (section5 != nullptr)
    {
        SDL_DestroyTexture(section5);
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
        if (selection < chapterMax)
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
            game::getInstance().changeScene(new storySelect1());          
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
        keyZ = true;
    }

    if (!keyboardState[SDL_SCANCODE_Z])
    {
        keyZ = false;
    }

    //esc
    if (keyboardState[SDL_SCANCODE_ESCAPE] && !keyEsc)
    {
        game::getInstance().changeScene(new menu());
    }

    if (!keyboardState[SDL_SCANCODE_ESCAPE])
    {
        keyEsc = false;
    }
    
}

void selectLevel::renderBackground()
{
    SDL_RenderCopy(game::getInstance().getRenderer(), background, NULL, NULL);
}

void selectLevel::renderSelections()
{
    //渲染title
    int titleTextW, titleTextH;
    SDL_QueryTexture(title, NULL, NULL, &titleTextW, &titleTextH);
    SDL_Rect titleRect = 
    { 
        (WINDOW_WIDTH - titleTextW) / 2, 
        50, 
        titleTextW, 
        titleTextH 
    };
    SDL_RenderCopy(game::getInstance().getRenderer(), title, NULL, &titleRect);

    //渲染章节封面于窗口正中间
    SDL_Rect chapterSelectedRect = 
    { 
        (WINDOW_WIDTH - chapterSizeSelected) / 2, 
        (WINDOW_HEIGHT - chapterSizeSelected) / 2 - 50, 
        chapterSizeSelected, 
        chapterSizeSelected 
    };
    int cstextW, cstextH;
    SDL_QueryTexture(section1text, NULL, NULL, &cstextW, &cstextH);
    SDL_Rect chapterSelectedTextRect =
    {
        (WINDOW_WIDTH - cstextW * 2) / 2, 
        (WINDOW_HEIGHT + chapterSizeSelected) / 2, 
        cstextW * 2,
        cstextH * 2
    };
    switch (selection)
    {
        case 1:
            SDL_RenderCopy(game::getInstance().getRenderer(), section1, NULL, &chapterSelectedRect);
            SDL_RenderCopy(game::getInstance().getRenderer(), section1text, NULL, &chapterSelectedTextRect);
            break;
        case 2: 
            SDL_RenderCopy(game::getInstance().getRenderer(), section2, NULL, &chapterSelectedRect);
            SDL_RenderCopy(game::getInstance().getRenderer(), section2text, NULL, &chapterSelectedTextRect);
            break;
        case 3:
            SDL_RenderCopy(game::getInstance().getRenderer(), section3, NULL, &chapterSelectedRect);
            SDL_RenderCopy(game::getInstance().getRenderer(), section3text, NULL, &chapterSelectedTextRect);
            break;
        case 4:
            SDL_RenderCopy(game::getInstance().getRenderer(), section4, NULL, &chapterSelectedRect);
            SDL_RenderCopy(game::getInstance().getRenderer(), section4text, NULL, &chapterSelectedTextRect);
            break;
        case 5:
            SDL_RenderCopy(game::getInstance().getRenderer(), section5, NULL, &chapterSelectedRect);
            SDL_RenderCopy(game::getInstance().getRenderer(), section5text, NULL, &chapterSelectedTextRect);
            break;
        default:
            break;
    }

    //渲染没被选中的章节图标于左右两侧
    renderSubSelections(selection);


}

void selectLevel::renderSubSelections(int selection)
{
    SDL_Rect chapterSubRectLeft = 
    { 
        (WINDOW_WIDTH - chapterSizeSelected) / 2 - chapterSize - 30, 
        (WINDOW_HEIGHT - chapterSize) / 2 - 50, 
        chapterSize, 
        chapterSize
    };
    SDL_Rect chapterSubRectRight =
    {
        (WINDOW_WIDTH + chapterSizeSelected) / 2 + 30, 
        (WINDOW_HEIGHT - chapterSize) / 2 - 50, 
        chapterSize, 
        chapterSize
    };

    SDL_SetTextureAlphaMod(getLeftSelections(selection), 200);
    SDL_RenderCopy(game::getInstance().getRenderer(), getLeftSelections(selection), NULL, &chapterSubRectLeft);

    SDL_SetTextureAlphaMod(getRightSelections(selection), 200);
    SDL_RenderCopy(game::getInstance().getRenderer(), getRightSelections(selection), NULL, &chapterSubRectRight);
    SDL_SetTextureAlphaMod(getLeftSelections(selection), 255); 
    SDL_SetTextureAlphaMod(getRightSelections(selection), 255);
}

SDL_Texture *selectLevel::getLeftSelections(int selection)
{
    switch (selection)
    {
        case 1:
            return nullptr;
        case 2:
            return section1;
        case 3:
            return section2;
        case 4:
            return section3;
        case 5:
            return section4;
        default:
            return nullptr;
    }
}

SDL_Texture *selectLevel::getRightSelections(int selection)
{
    switch (selection)
    {
        case 1:
            return section2;
        case 2:
            return section3;
        case 3:
            return section4;
        case 4:
            return section5;
        case 5:
            return nullptr;
        default:
            return nullptr;
    }
}
