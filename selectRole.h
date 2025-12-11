#pragma once
#include "scene.h"
#include "self.h"
#include <random>

class game;

class selectRole : public scene
{
public:
    selectRole();
    ~selectRole();
    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;
    
    void keyboardControl();
    void renderBackground();
    void renderSelections();
    void renderUI();

private:
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    SDL_Texture* background;
    SDL_Texture* selection1;
    SDL_Texture* profile1;
    SDL_Texture* ensure;
    SDL_Texture* selectrole;
    SDL_Texture* left;
    SDL_Texture* right;


    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int selection = 1;
    bool keyDown = false;
    bool keyUp = false;
    bool keyZ = true;  
};
