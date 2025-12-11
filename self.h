#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "configs.h"
#include "enermy.h"
#include <list>

struct self_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = 12;
    int height = 16;
    int speed = 1500;
    int speedX = 0;
    float damage = 0.6f;
};

struct Player
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* blood = nullptr;
    SDL_Texture* combatTexture1 = nullptr;
    SDL_Texture* combatTexture2 = nullptr;
    SDL_Texture* combatTexture3 = nullptr;
    SDL_Texture* combatTexture4 = nullptr;
    SDL_Texture* selfpointTexture = nullptr;
    SDL_Texture* skill2Texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f}; 
    int width = selfSize;
    int height = selfSize;
    float speed = 450;
    float sneakSpeed = 120;
    Uint32 FireCooldown = 250;
    Uint32 lastShootTime = 0;
    Uint32 z_signStartTime = 0;
    Uint32 shift_signStartTime = 0;
    Uint32 space_signStartTime = 0;
    Uint32 x_signStartTime = 0;
    Uint32 lastHurtTime = 0;
    Uint32 hurtDuration = 300;
    Uint32 poisonTime = 0;
    Uint32 fireTime = 0;
    Uint32 frozenTime = 0;
    float speedH = 0.0f;
    float speedV = 0.0f;   
    bool sneak = 0;
    bool shift_sign = 0;
    bool renderSkill2Needed = 0;
    bool renderCombatNeeded = 0;
    bool hurting = 0;
    bool autoFire = 0;
    float lives = 10.0f;
    float livesMax = 10.0f;
    bool isDead = false;
    float power = 200.0f;
    float powerMax = 200.0f;
    float level = 0.0f;
    float levelMax = 100.0f;
    float recoverSpeed = 0.08f;
    float defence = 0.0f;

    void skill1(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> &enemyBullets);//被动技能
    void skill2(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> &enemyBullets,std::list<std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*>>& enemies);//主动技能
    void skill2Render();
    void skill3(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> &enemyBullets,std::list<self_bullet *> &selfBullets);//决战技能

    Uint32 meleeCooldown = 500;  // 近战冷却时间(ms)
    Uint32 lastMeleeTime = 0;    // 上次近战时间
    float meleeRadius = 64.0f;   // 近战攻击半径
    float meleeDamage = 4.0f;    // 近战伤害值

    void combat(std::list<std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*>>& enemies);
    void combatRender();
};

