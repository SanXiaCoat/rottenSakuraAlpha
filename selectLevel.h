#pragma once
#include "scene.h"
#include "self.h"
#include "configs.h"
#include <random>

class game;

class selectLevel : public scene
{
public:
    selectLevel();
    ~selectLevel();
    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;
    

    void keyboardControl();
    void renderBackground();
    void renderSelections();

    void renderSubSelections(int selection);
    SDL_Texture* getLeftSelections(int selection);
    SDL_Texture* getRightSelections(int selection);

    

private:
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    SDL_Texture* title = nullptr;
    SDL_Texture* background = nullptr;
    SDL_Texture* section1 = nullptr;
    SDL_Texture* section2 = nullptr;
    SDL_Texture* section3 = nullptr;
    SDL_Texture* section4 = nullptr;
    SDL_Texture* section5 = nullptr;

    SDL_Texture* section1text = nullptr;
    SDL_Texture* section2text = nullptr;
    SDL_Texture* section3text = nullptr;
    SDL_Texture* section4text = nullptr;
    SDL_Texture* section5text = nullptr;



    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int selection = 1;
    bool keyDown = false;
    bool keyUp = false;
    bool keyZ = true;  
    bool keyEsc = true;
};