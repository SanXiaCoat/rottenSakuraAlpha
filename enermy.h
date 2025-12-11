#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "configs.h"

struct enemy1
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 40;
    int defence = 0;
    Uint32 FireCooldown = 1500;
    Uint32 lastShootTime = 0;
    float health = 3.0f;
    int score = 1;
};

struct enemy2
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 20;
    int defence = 0;
    Uint32 FireCooldown = 400;
    Uint32 lastShootTime = 0;
    float health = 12.0f;
    int score = 3;
};

struct enemy3
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 20;
    int defence = 0;
    Uint32 FireCooldown = 10000;
    Uint32 lastShootTime = 0;
    float health = 20.0f;
    int score = 2;
    bool isShooting = false;         // 是否正在发射
};

struct enemy4
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 50;
    int defence = 0;
    Uint32 FireCooldown = 3000;
    Uint32 lastShootTime = 0;
    float health = 6.0f;
    int score = 2;
};

struct enemy1_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = 10;
    int height = 10;
    int speed = 160;
    int speed_ = 160;
    float damage = 0.5f;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
    int explosion = 0;
    int poison = 0;
    Uint32 poisonDuration = 1000;
};

struct enemy2_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = 12;
    int height = 12;
    int speed = 200;
    int speed_ = 200;
    float damage = 1.0f;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
    int explosion = 0;
    int poison = 0;
    Uint32 poisonDuration = 1000;
};

struct enemy3_laser
{
    SDL_Texture* inactivationTexture = nullptr;   
    SDL_Texture* activationTexture = nullptr;    
    SDL_FPoint startPosition;         
    SDL_FPoint endPosition;       
    int width = 8;                  
    float damage = 8.0f;                     
    Uint32 startTime;               
    Uint32 alarmTime = 1500;           
    Uint32 duration = 2000;          
    bool isActive = false;                  
};

struct enemy4_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = 16;
    int height = 16;
    int speed = 320;
    int speed_ = 320;
    float damage = 0.8;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
    int explosion = 0;
    int poison = 0;
    Uint32 poisonDuration = 1000;
};

class BattleField;

struct boss1
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textures[16] = {};
    int width = 180;
    int height = 270;
    SDL_FPoint position = {fieldW / 2.0f - width / 2.0f , fieldH / 4.0f - height / 2.0f};
    int speed = 0;
    int speedX = 30;
    const float initialSpeedX = 10.0f; 
    const float acceleration = 2000.0f; 
    float defence = 0;
    Uint32 lastSpellCardTime = 0;
    Uint32 lastSpellCard1Time = 0;
    Uint32 lastSpellCard5Time = 0;
    Uint32 lastSpellCard8Time = 0;
    Uint32 lastSpellCard12Time = 0;
    Uint32 lastMoveTime = 0;    
    float health = 2000.0f;
    float healthMax = 2000.0f;
    int phase_left = 3;
    int score = 100;
    bool skill2 = false; 
    Uint32 skill2StartTime = 0;
    bool bonus1 = false;
    bool bonus2 = false;
    bool bonus3 = false;
    bool bonus4 = false;
    bool bonus5 = false;
    bool card13Used1 = false;
    bool card13Used2 = false;
    int ballCount = 0;

    bool c10[24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int c10o = 0;


    void card1(BattleField& battlefield);
    void card2(BattleField& battlefield);
    void card3(BattleField& battlefield);
    void card4(BattleField& battlefield);
    void card5(BattleField& battlefield);
    void card6(BattleField& battlefield);
    void card7(BattleField& battlefield);
    void card8(BattleField& battlefield);
    void card9(BattleField& battlefield);
    void card10(BattleField& battlefield, int offset);
    void card11(BattleField& battlefield);
    void card12(BattleField& battlefield);
    void card13(BattleField& battlefield);

    void moveHorizont(float deltaTime,float maxSpeedX);
    void bulletRevolve(float deltaTime, BattleField& battlefield);
};

struct boss1_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_Texture* sakura = nullptr;
    SDL_Texture* sakura2 = nullptr;
    SDL_Texture* sakura3 = nullptr;
    SDL_Texture* arrow = nullptr;
    SDL_Texture* blue = nullptr;
    SDL_Texture* large = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = 12;
    int height = 12;
    int speed = 300;
    int speed_ = 300;
    float damage = 1;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
    int explosion = 0;
    int poison = 0;
    Uint32 poisonDuration = 200;
};

struct boss1_bullet_revolving
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint revolvingPosition = {0.0f, 0.0f};
    float angle = 0.0f;
    int width = 12;
    int height = 12;
    int speed = 400;
    int damage = 2;
};

struct death_effect
{
    SDL_Texture* texture = nullptr;
    //定义材质数组
    SDL_Texture* textures[16] = {};
    SDL_FPoint position = {0.0f, 0.0f};
    int width = 64;
    int height = 64;
    Uint32 startTime = 0;
    float speed = 50.0f;
};