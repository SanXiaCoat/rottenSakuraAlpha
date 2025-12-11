#pragma once
#include "scene.h"
#include "self.h"
#include <random>

class game;

class menu : public scene
{
public:
    menu();
    ~menu();
    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;
    void keyboardControl();
    void renderTitle_Background();
    void renderSelections();

private:
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    SDL_Texture* title;
    SDL_Texture* background;
    SDL_Texture* menu1;
    SDL_Texture* menu1_;
    SDL_Texture* menu2;
    SDL_Texture* menu2_;
    SDL_Texture* menu3;
    SDL_Texture* menu3_;
    SDL_Texture* menu4;
    SDL_Texture* menu4_;
    SDL_Texture* menu5;
    SDL_Texture* menu5_;
    SDL_Texture* menu6;
    SDL_Texture* menu6_;

    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int selection = 1;
    bool keyDown = false;
    bool keyUp = false;
    bool keyZ = false;  
};
