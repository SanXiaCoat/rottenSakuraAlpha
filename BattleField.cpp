#include "BattleField.h"
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
#include "enemyBehaviour.h"

BattleField::BattleField(int is_Boss) : game(game::getInstance()), isBoss(is_Boss)
{

}

BattleField::~BattleField()
{
    
}

void BattleField::init()
{
    //随机数种子
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    distNeg = std::uniform_real_distribution<float>(-1.0f, 1.0f);

    startTime = SDL_GetTicks();
    srand((unsigned int)time(NULL));
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

   
    //载入图片
    player.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self1.png");
    player.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self2.png");
    player.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self3.png");
    player.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self4.png");
    player.blood = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/blood.png");
    player.selfpointTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/selfpoint.png");
    backgroundTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/BattleFieldBackground.png");
    titleTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/title.png");
    healthBarTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/healthBar.png");
    bossHealthBarTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/bossHealthBar.png");
    bossHealthBarLowTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/bossHealthBarLow.png");
    player.combatTexture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/1.png");
    player.combatTexture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/2.png");
    player.combatTexture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/3.png");
    player.combatTexture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/4.png");
    player.skill2Texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/skill2.png");

    // 初始化模板
    enemy1BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet.png");
    enemy1BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_freezed.png");
    enemy1BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_slowed.png");
    enemy1BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_alt.png");

    enemy2BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet.png");
    enemy2BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_freezed.png");
    enemy2BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_slowed.png");
    enemy2BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_alt.png");

    enemy3LaserTemplate.inactivationTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy3/inactive.png");
    enemy3LaserTemplate.activationTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy3/active.png");

    enemy4BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy4/bullet.png");
    enemy4BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy4/bullet_freezed.png");
    enemy4BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy4/bullet_slowed.png");
    enemy4BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy4/bullet_alt.png");

    boss1BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet.png");
    boss1BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_freezed.png");
    boss1BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_slowed.png");
    boss1BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_alt.png");
    boss1BulletTemplate.sakura = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/boss1Sakura.png");
    boss1BulletTemplate.sakura2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/boss1Sakura2.png");
    boss1BulletTemplate.sakura3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/boss1Sakura3.png");
    boss1BulletTemplate.arrow = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/arrow.png");
    boss1BulletTemplate.blue = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/bulletBlue.png");
    boss1BulletTemplate.large = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/boss/boss1/large.png");
    boss1BulletRevolvingTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet.png");

    enemyTemplate.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemyTemplate.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemyTemplate.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemyTemplate.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemyTemplate.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    enemy2Template.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemy2Template.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemy2Template.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemy2Template.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemy2Template.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    enemy3Template.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemy3Template.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemy3Template.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemy3Template.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemy3Template.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    enemy4Template.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemy4Template.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemy4Template.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemy4Template.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemy4Template.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    boss1Template.textures[0] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/0.png");
    boss1Template.textures[1] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/1.png");
    boss1Template.textures[2] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/2.png");
    boss1Template.textures[3] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/3.png");
    boss1Template.textures[4] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/4.png");
    boss1Template.textures[5] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/5.png");
    boss1Template.textures[6] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/6.png");
    boss1Template.textures[7] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/7.png");
    boss1Template.textures[8] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/8.png");
    boss1Template.textures[9] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/9.png");
    boss1Template.textures[10] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/10.png");
    boss1Template.textures[11] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/11.png");
    boss1Template.textures[12] = IMG_LoadTexture(game.getRenderer(), "../assets/images/boss1/12.png");

    deathEffectTemplate.textures[0] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_0.png");
    deathEffectTemplate.textures[1] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_1.png");
    deathEffectTemplate.textures[2] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_2.png");
    deathEffectTemplate.textures[3] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_3.png");
    deathEffectTemplate.textures[4] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_4.png");
    deathEffectTemplate.textures[5] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_5.png");
    deathEffectTemplate.textures[6] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_6.png");
    deathEffectTemplate.textures[7] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_7.png");
    deathEffectTemplate.textures[8] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_8.png");
    deathEffectTemplate.textures[9] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_9.png");
    deathEffectTemplate.textures[10] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_10.png");
    deathEffectTemplate.textures[11] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_11.png");
    deathEffectTemplate.textures[12] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_12.png");
    deathEffectTemplate.textures[13] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_13.png");
    deathEffectTemplate.textures[14] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_14.png"); 
    deathEffectTemplate.textures[15] = IMG_LoadTexture(game.getRenderer(), "../assets/images/death/explosion_15.png");

    selfBulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/bullet.png");

    powerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/power.png");
    scoreItemTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/scoreItem.png");

    bgTemplate1.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/battleBackground/suburbBG1.png");
    
    bgTemplate2.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/battleBackground/suburbBG2.png");

    if (statusFont != nullptr) 
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurfacePaused1 = TTF_RenderUTF8_Solid(statusFont, "PAUSED", textColor);
        SDL_Surface* textSurfacePaused2 = TTF_RenderUTF8_Solid(statusFont, "按 [ESC] 继续", textColor);
        SDL_Surface* textSurfacePaused3 = TTF_RenderUTF8_Solid(statusFont, "按 [Q] 退出]", textColor);
        SDL_Surface* textSurfaceDeath1 = TTF_RenderUTF8_Solid(statusFont, "满身疮痍 ! ", textColor);
        SDL_Surface* textSurfaceDeath2 = TTF_RenderUTF8_Solid(statusFont, "按 [Q] 退出", textColor);
        if (textSurfacePaused1 != nullptr) 
        {
            pauseTextTexture1 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused1);
            SDL_FreeSurface(textSurfacePaused1);
        }
        if (textSurfacePaused2 != nullptr) 
        {
            pauseTextTexture2 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused2);
            SDL_FreeSurface(textSurfacePaused2);
        }
        if (textSurfacePaused3 != nullptr) 
        {
            pauseTextTexture3 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused3);
            SDL_FreeSurface(textSurfacePaused3);
        }
        if (textSurfaceDeath1 != nullptr)
        {
            deathTextTexture1 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceDeath1);
            SDL_FreeSurface(textSurfaceDeath1);
        }
        if (textSurfaceDeath2 != nullptr)
        {
            deathTextTexture2 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceDeath2);
            SDL_FreeSurface(textSurfaceDeath2);
        }
    }

    //初始化自机位置
    player.position.x = (fieldW - player.width) / 2.0;
    player.position.y = fieldH - player.height;

}

void BattleField::update(float deltaTime)
{
    if (isPaused) 
    {
        return;
    }
    keyboardControl(deltaTime);
    playerBulletsUpdate(deltaTime);
    powerManage();
    spawnEnemy();
    updateEnemies1(deltaTime);
    EnemyManager::updateEnemyBullets(this, deltaTime);
    EnemyManager::updateEnemyLasers(this, deltaTime);
    updatePlayer(deltaTime);
    updatePowers(deltaTime);
    updateBattleBackground(deltaTime);
    player.skill1(enemy1Bullets);
    deathEffectsUpdate();
    ItemToPlayer();
}

void BattleField::render()
{   
    //渲染窗口背景
    SDL_RenderCopy(game.getRenderer(), backgroundTexture, NULL, NULL);

    //渲染战斗背景（黑色框）
    SDL_Rect fieldRect = { 0, 0, fieldW, fieldH };
    SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(game.getRenderer(), &fieldRect);

    //渲染滚动背景
    rollingBackgroundRender();

    //渲染自机子弹
    playerBulletsRender();

    //渲染敌机1子弹
    enemy1BulletsRender();

    //渲染敌机1激光
    enemy1LasersRender();

    //渲染p点
    renderPowers();

    //渲染死亡特效
    deathEffectsRender();

    SDL_Rect playerRect = 
    {
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        static_cast<int>(player.width),
        static_cast<int>(player.height)
    };
    SDL_Rect bfRect = 
    {
        0, 0, fieldW, fieldH
    };
    if (!player.isDead)
    {
        if (player.renderSkill2Needed)
        {
            player.skill2Render();
        }

        //渲染自机
        SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);
        
        if (!player.hurting)
        {
            int currentFrame = (SDL_GetTicks() - startTime) / 500;
            if (currentFrame % 3 == 0)
            {
                player.texture = player.texture1;
            }
            else if (currentFrame % 3 == 1)
            {
                player.texture = player.texture2;
            }
            else
            {
                player.texture = player.texture3;
            }
        }
        else
        {
            if (SDL_GetTicks() - player.lastHurtTime < player.hurtDuration)
            {
                player.texture = player.texture4;
                SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
                SDL_SetTextureAlphaMod(player.blood, 255 * (1.0f - float(SDL_GetTicks() - player.lastHurtTime) / player.hurtDuration));
                SDL_RenderCopy(game.getRenderer(), player.blood, NULL, &bfRect);
            }
            else
            {
                player.hurting = false;
            }
        }
        
        
        SDL_Rect selfpoint = 
        {
            static_cast<int>(player.position.x + 16),
            static_cast<int>(player.position.y + 16),
            16,
            16
        };
        SDL_RenderCopy(game.getRenderer(), player.selfpointTexture, NULL, &selfpoint);
    }
    else
    {
        player.texture = player.texture4;
        SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(player.blood, 255);
        SDL_RenderCopy(game.getRenderer(), player.blood, NULL, &bfRect);
    }
    
    //渲染敌机
    renderEnemies1();

    //渲染右侧状态栏
    statusRender();

    //渲染近战特效贴图
    if (player.renderCombatNeeded)
    {
        player.combatRender();
    }

    //渲染bossBar
    bossBarRender();

    if (isPaused) 
    {
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        // 半透明黑色覆盖层
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 64);
        SDL_RenderFillRect(game.getRenderer(), &fieldRect);

        // 渲染暂停文字
        if (pauseTextTexture1 != nullptr && pauseTextTexture2 != nullptr && pauseTextTexture3 != nullptr) 
        {
            int textW1, textH1;
            SDL_QueryTexture(pauseTextTexture1, NULL, NULL, &textW1, &textH1);

            int textW2, textH2;
            SDL_QueryTexture(pauseTextTexture2, NULL, NULL, &textW2, &textH2);

            int textW3, textH3;
            SDL_QueryTexture(pauseTextTexture3, NULL, NULL, &textW3, &textH3);

            SDL_Rect renderRect1 = {
                (fieldW - textW1) / 2,
                (fieldH - textH1) / 2 - textH1 - 10,
                textW1,
                textH1
            };
            SDL_Rect renderRect2 = {
                (fieldW - textW2) / 2,
                (fieldH - textH2) / 2,
                textW2,
                textH2
            };
            SDL_Rect renderRect3 = {
                (fieldW - textW3) / 2,
                (fieldH - textH3) / 2 + textH3 + 10,
                textW3,
                textH3
            };
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture1, NULL, &renderRect1);
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture2, NULL, &renderRect2);
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture3, NULL, &renderRect3);
        }
    }

    if (player.isDead)
    {
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 64);
        SDL_RenderFillRect(game.getRenderer(), &fieldRect);

        // 渲染死亡文字
        if (deathTextTexture1 != nullptr && deathTextTexture2 != nullptr) 
        {
            int textW1, textH1;
            SDL_QueryTexture(deathTextTexture1, NULL, NULL, &textW1, &textH1);

            int textW2, textH2;
            SDL_QueryTexture(deathTextTexture2, NULL, NULL, &textW2, &textH2);

            SDL_Rect renderRect1 = {
                (fieldW - textW1) / 2,
                (fieldH - textH1) / 2 - 10,
                textW1,
                textH1
            };

            SDL_Rect renderRect2 = {
                (fieldW - textW2) / 2,
                (fieldH - textH2) / 2 + textH2 + 10,
                textW2,
                textH2
            };
            
            SDL_RenderCopy(game.getRenderer(), deathTextTexture1, NULL, &renderRect1);
            SDL_RenderCopy(game.getRenderer(), deathTextTexture2, NULL, &renderRect2);
        }
    
        
    }
    
}

void BattleField::clean()
{
    //清理子弹容器
    for (auto &projectile  : playerBullets)
    {
        if (projectile != nullptr)
        {
            delete projectile;
        }
    }
    playerBullets.clear();

    //清理敌机1容器
    for (auto &enemy : enemies)
    {
        std::visit([](auto&& enemy) {
            if (enemy != nullptr)
            {
                delete enemy;
            }
        }, enemy);
    }
    enemies.clear();

    //清理敌机1子弹容器
    for (auto &bullet : enemy1Bullets)
    {
        std::visit([](auto&& bullet) {
            if (bullet != nullptr)
            {
                delete bullet;
            } 
        },bullet);
    }
    enemy1Bullets.clear();

    //清理激光容器
    for (auto &laser : enemyLasers)
    {
        if (laser != nullptr)
        {
            delete laser;
        }
    }
    enemyLasers.clear();

    //清理p点容器
    for (auto &power : powers)
    {
        if (power != nullptr)
        {
            delete power;
        }
    }
    powers.clear();

    //清理背景容器
    for (auto &bg : battleBackgrounds)
    {
        if (bg != nullptr)
        {
            delete bg;
        }
    }

    //清理自机

    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }

    if (player.texture1 != nullptr)
    {
        SDL_DestroyTexture(player.texture1);
    }

    if (player.texture2 != nullptr)
    {
        SDL_DestroyTexture(player.texture2);
    }

    if (player.texture3 != nullptr)
    {
        SDL_DestroyTexture(player.texture3);
    }

    if (player.texture4 != nullptr)
    {
        SDL_DestroyTexture(player.texture4);
    }


    //清理模板
    if (selfBulletTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(selfBulletTemplate.texture);
    }

    if (enemyTemplate.texture1 != nullptr || enemyTemplate.texture2 != nullptr || enemyTemplate.texture3 != nullptr || enemyTemplate.texture4 != nullptr || enemyTemplate.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemyTemplate.texture1);
        SDL_DestroyTexture(enemyTemplate.texture2);
        SDL_DestroyTexture(enemyTemplate.texture3);
        SDL_DestroyTexture(enemyTemplate.texture4);
        SDL_DestroyTexture(enemyTemplate.texture5);
    }

    if (enemy2Template.texture1 != nullptr || enemy2Template.texture2 != nullptr || enemy2Template.texture3 != nullptr || enemy2Template.texture4 != nullptr || enemy2Template.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemy2Template.texture1);
        SDL_DestroyTexture(enemy2Template.texture2);
        SDL_DestroyTexture(enemy2Template.texture3);
        SDL_DestroyTexture(enemy2Template.texture4);
        SDL_DestroyTexture(enemy2Template.texture5);
    }

    if (enemy3Template.texture1 != nullptr || enemy3Template.texture2 != nullptr || enemy3Template.texture3 != nullptr || enemy3Template.texture4 != nullptr || enemy3Template.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemy3Template.texture1);
        SDL_DestroyTexture(enemy3Template.texture2);
        SDL_DestroyTexture(enemy3Template.texture3);
        SDL_DestroyTexture(enemy3Template.texture4);
        SDL_DestroyTexture(enemy3Template.texture5);
    }

    if (enemy4Template.texture1 != nullptr || enemy4Template.texture2 != nullptr || enemy4Template.texture3 != nullptr || enemy4Template.texture4 != nullptr || enemy4Template.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemy4Template.texture1);
        SDL_DestroyTexture(enemy4Template.texture2);
        SDL_DestroyTexture(enemy4Template.texture3);
        SDL_DestroyTexture(enemy4Template.texture4);
        SDL_DestroyTexture(enemy4Template.texture5);
    }

    if (boss1Template.textures != nullptr)
    {
        for (int i = 0; i < 13; ++i)
        {
            if (boss1Template.textures[i] != nullptr)
            {
                SDL_DestroyTexture(boss1Template.textures[i]);
            }
        }
    }

    if (player.combatTexture1 != nullptr || player.combatTexture2 != nullptr || player.combatTexture3 != nullptr || player.combatTexture4 != nullptr)
    {
        SDL_DestroyTexture(player.combatTexture1);
        SDL_DestroyTexture(player.combatTexture2);
        SDL_DestroyTexture(player.combatTexture3);
        SDL_DestroyTexture(player.combatTexture4);
    }

    if (player.skill2Texture != nullptr)
    {
        SDL_DestroyTexture(player.skill2Texture);
    }

    if (enemy1BulletTemplate.texture != nullptr || enemy1BulletTemplate.textureFrozen != nullptr || enemy1BulletTemplate.textureSlowed != nullptr || enemy1BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy1BulletTemplate.texture);
        SDL_DestroyTexture(enemy1BulletTemplate.textureFrozen);
        SDL_DestroyTexture(enemy1BulletTemplate.textureSlowed);
        SDL_DestroyTexture(enemy1BulletTemplate.textureAlt);
    }

    if (enemy2BulletTemplate.texture != nullptr || enemy2BulletTemplate.textureFrozen != nullptr || enemy2BulletTemplate.textureSlowed != nullptr || enemy2BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy2BulletTemplate.texture);
        SDL_DestroyTexture(enemy2BulletTemplate.textureFrozen);
        SDL_DestroyTexture(enemy2BulletTemplate.textureSlowed);
        SDL_DestroyTexture(enemy2BulletTemplate.textureAlt);
    }

    if (enemy3LaserTemplate.activationTexture != nullptr || enemy3LaserTemplate.inactivationTexture!= nullptr)
    {
        SDL_DestroyTexture(enemy3LaserTemplate.activationTexture);
        SDL_DestroyTexture(enemy3LaserTemplate.inactivationTexture);
    }

    if (enemy4BulletTemplate.texture != nullptr || enemy4BulletTemplate.textureFrozen != nullptr || enemy4BulletTemplate.textureSlowed != nullptr || enemy4BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy4BulletTemplate.texture);
        SDL_DestroyTexture(enemy4BulletTemplate.textureFrozen);
        SDL_DestroyTexture(enemy4BulletTemplate.textureSlowed);
        SDL_DestroyTexture(enemy4BulletTemplate.textureAlt);
    }   

    if (boss1BulletTemplate.texture != nullptr || boss1BulletTemplate.textureFrozen != nullptr || boss1BulletTemplate.textureSlowed != nullptr || boss1BulletTemplate.textureAlt != nullptr || boss1BulletTemplate.sakura != nullptr || boss1BulletTemplate.sakura2 != nullptr || boss1BulletTemplate.sakura3 != nullptr || boss1BulletTemplate.arrow != nullptr || boss1BulletTemplate.blue != nullptr || boss1BulletTemplate.large != nullptr)
    {
        SDL_DestroyTexture(boss1BulletTemplate.texture);
        SDL_DestroyTexture(boss1BulletTemplate.textureFrozen);
        SDL_DestroyTexture(boss1BulletTemplate.textureSlowed);
        SDL_DestroyTexture(boss1BulletTemplate.textureAlt);
        SDL_DestroyTexture(boss1BulletTemplate.sakura);
        SDL_DestroyTexture(boss1BulletTemplate.sakura2);
        SDL_DestroyTexture(boss1BulletTemplate.sakura3);
        SDL_DestroyTexture(boss1BulletTemplate.arrow);
        SDL_DestroyTexture(boss1BulletTemplate.blue);
        SDL_DestroyTexture(boss1BulletTemplate.large);
    }

    if (boss1BulletRevolvingTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(boss1BulletRevolvingTemplate.texture);
    }

    if (deathEffectTemplate.textures != nullptr)
    {
        for (int i = 0; i < 16; ++i)
        {
            if (deathEffectTemplate.textures[i] != nullptr)
            {
                SDL_DestroyTexture(deathEffectTemplate.textures[i]);
            }
        }
    }

    if (backgroundTexture != nullptr)
    {
        SDL_DestroyTexture(backgroundTexture);
    }

    if (powerTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(powerTemplate.texture);
    }

    if (scoreItemTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(scoreItemTemplate.texture);
    }

    if (bgTemplate1.texture != nullptr)
    {
        SDL_DestroyTexture(bgTemplate1.texture);
    }

    if (bgTemplate2.texture != nullptr)
    {
        SDL_DestroyTexture(bgTemplate2.texture);
    }

    //清理标题
    if (titleTexture != nullptr)
    {
        SDL_DestroyTexture(titleTexture);
    }

    //清理字体
    if (statusFont != nullptr)
    {
        TTF_CloseFont(statusFont);
    }

    //清理血条
    if (healthBarTexture != nullptr) 
    {
        SDL_DestroyTexture(healthBarTexture);
    }
    if (bossHealthBarTexture != nullptr) 
    {
        SDL_DestroyTexture(bossHealthBarTexture);
    }   
    if (bossHealthBarLowTexture != nullptr) 
    {
        SDL_DestroyTexture(bossHealthBarLowTexture);
    }   
    
    
    if (pauseTextTexture1 != nullptr) 
    {
        SDL_DestroyTexture(pauseTextTexture1);
        pauseTextTexture1 = nullptr;
    }

    if (pauseTextTexture2 != nullptr)
    {
        SDL_DestroyTexture(pauseTextTexture2);
        pauseTextTexture2 = nullptr;
    }

    if (pauseTextTexture3 != nullptr)
    {
        SDL_DestroyTexture(pauseTextTexture3);
        pauseTextTexture3 = nullptr;
    }

    if (deathTextTexture1 != nullptr)
    {
        SDL_DestroyTexture(deathTextTexture1);
        deathTextTexture1 = nullptr;
    }

    if (deathTextTexture2 != nullptr)
    {
        SDL_DestroyTexture(deathTextTexture2);
        deathTextTexture2 = nullptr;
    }

}

void BattleField::handleEvents(SDL_Event* event)
{
    if(isBoss && !hasBoss)
    {
        auto boss = new boss1(boss1Template);
        boss->lastSpellCardTime = SDL_GetTicks();
        enemies.push_back(boss);
        hasBoss = true;
    }
    
    if (event->type == SDL_KEYDOWN) 
    {
        if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE && player.isDead == false) {
            isPaused = !isPaused; 
        }
        if (isPaused) 
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_Q)
            {
                game::getInstance().changeScene(new menu());
            }
        }
        if (player.isDead)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_Q)
            {
                game::getInstance().changeScene(new menu());
            }
        }
    }

    

}

void BattleField::keyboardControl(float deltaTime)
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 
    if (!player.isDead)
    {
        player.speedH = 0;
        player.speedV = 0;
    
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            player.speedH = keyboardState[SDL_SCANCODE_LSHIFT] ? -player.sneakSpeed : -player.speed;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            player.speedH = keyboardState[SDL_SCANCODE_LSHIFT] ? player.sneakSpeed : player.speed;
        }
        if (keyboardState[SDL_SCANCODE_UP])
        {
            player.speedV = keyboardState[SDL_SCANCODE_LSHIFT] ? -player.sneakSpeed : -player.speed;
        }
        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            player.speedV = keyboardState[SDL_SCANCODE_LSHIFT] ? player.sneakSpeed : player.speed;
        }

        // 自机移动
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.x -= deltaTime * player.sneakSpeed;
            else
                player.position.x -= deltaTime * player.speed;
            if (player.position.x < 0) 
                player.position.x = 0;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.x += deltaTime * player.sneakSpeed;
            else
                player.position.x += deltaTime * player.speed;
            if (player.position.x > fieldW - player.width) 
                player.position.x = fieldW - player.width;
        }
        if (keyboardState[SDL_SCANCODE_UP])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.y -= deltaTime * player.sneakSpeed;
            else
                player.position.y -= deltaTime * player.speed;
            if (player.position.y < 0) 
                player.position.y = 0;
        }
        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.y += deltaTime * player.sneakSpeed;
            else
                player.position.y += deltaTime * player.speed;
            if (player.position.y > fieldH - player.height) 
                player.position.y = fieldH - player.height;
        }

        if (keyboardState[SDL_SCANCODE_LSHIFT] && !player.shift_sign)
        {
            player.shift_sign = true;
        }
        if (!keyboardState[SDL_SCANCODE_LSHIFT])
        {
            player.shift_sign = false; 
        }

        if(keyboardState[SDL_SCANCODE_S] && !s_sign)
        {
            player.autoFire = !player.autoFire;
            s_sign = true;
        }
        if (!keyboardState[SDL_SCANCODE_S])
        {
            s_sign = false; 
        }



        
        //自机射击
        if (!player.autoFire)
        {
            if(keyboardState[SDL_SCANCODE_Z])
            {
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - player.lastShootTime > player.FireCooldown / sqrt(1 + player.power * 0.2f))
                {
                    selfShoot();
                    player.lastShootTime = currentTime;
                }
            }

            //不射击恢复体力
            if (!keyboardState[SDL_SCANCODE_Z])
            {
                player.power += deltaTime * player.recoverSpeed;
            }
        }
        else
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - player.lastShootTime > player.FireCooldown / sqrt(1 + player.power * 0.2f))
            {
                selfShoot();
                player.lastShootTime = currentTime;
            }
        }

        if (keyboardState[SDL_SCANCODE_SPACE] && !spaceSign)
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - player.lastMeleeTime > player.meleeCooldown / sqrt(1 + player.power))
            {
                player.combat(enemies); 
                player.renderCombatNeeded = true; 
                player.lastMeleeTime = currentTime; 
                player.space_signStartTime = currentTime; 
            }
            spaceSign = true;
        }

        if (!keyboardState[SDL_SCANCODE_SPACE])
        {
            spaceSign = false;
        }
        
        //主动技能
        if (keyboardState[SDL_SCANCODE_X] && !x_sign)
        {
            if (player.power >= 3.0f)
            {
                player.skill2(enemy1Bullets, enemies);
                player.x_signStartTime = SDL_GetTicks();
                player.renderSkill2Needed = true;
                player.power -= 3.0f;
            }
            x_sign = true;
        }

        if (!keyboardState[SDL_SCANCODE_X])
        {
            x_sign = false;
        }

        //终决技
        if (keyboardState[SDL_SCANCODE_C] && !c_sign)
        {
            if (player.power >= 10.0f)
            {
                player.skill3(enemy1Bullets, playerBullets);
                if (player.lives <= 19.0f)
                    player.lives += 1.0f;
                player.power -= 10.0f;
            }
            c_sign = true;
        }

        if (!keyboardState[SDL_SCANCODE_C])
        {
            c_sign = false;
        }

    }
}

void BattleField::selfShoot()
{
    auto projectile1 = new self_bullet(selfBulletTemplate);
    projectile1->position.x = player.position.x + (player.width - projectile1->width) / 2.0f;
    projectile1->position.y = player.position.y - projectile1->height;
    projectile1->speed -= player.speedV;
    if (!player.shift_sign)
            projectile1->speedX = - projectile1->speed * 0.05f - distNeg(gen) * 50.0f;
    projectile1->speedX += player.speedH;
    playerBullets.push_back(projectile1);  

    if (player.power >= 5.0f)
    {
        auto projectile2 = new self_bullet(selfBulletTemplate);
        projectile2->position.x = player.position.x + (player.width - projectile2->width) / 2.0f - 12;
        projectile2->position.y = player.position.y - projectile2->height;
        projectile2->speed -= player.speedV;
        if (!player.shift_sign)
            projectile2->speedX = - projectile2->speed * 0.05f + distNeg(gen) * 100.0f;
        projectile2->speedX += player.speedH;
        projectile2->damage /= 4.0f;
        if (player.power >= 10.0f)
        {
            projectile2->damage *= 2.0f;
        }
        if (player.power >= 25.0f)
        {
            projectile2->damage *= 2.0f;
        }
        playerBullets.push_back(projectile2);

        auto projectile3 = new self_bullet(selfBulletTemplate);
        projectile3->position.x = player.position.x + (player.width - projectile3->width) / 2.0f + 12;
        projectile3->position.y = player.position.y - projectile3->height;
        projectile3->speed -= player.speedV;
        if (!player.shift_sign)
            projectile3->speedX = projectile3->speed * 0.05f + distNeg(gen) * 100.0f;
        projectile3->speedX += player.speedH;
        projectile3->damage /= 4.0f;
        if (player.power >= 10.0f)
        {
            projectile3->damage *= 2.0f;
        }
        if (player.power >= 25.0f)
        {
            projectile3->damage *= 2.0f;
        }
        playerBullets.push_back(projectile3);
    }
    if (player.power >= 25.0f)
    {
        auto projectile4 = new self_bullet(selfBulletTemplate);
        projectile4->position.x = player.position.x + (player.width - projectile4->width) / 2.0f - 24;
        projectile4->position.y = player.position.y - projectile4->height;
        projectile4->damage /= 4.0f;
        if (!player.shift_sign)
            projectile4->speedX = -1 * projectile4->speed * 0.1f + distNeg(gen) * 150.0f;;
        projectile4->speed -= player.speedV;
        projectile4->speedX += player.speedH;
        if (player.power >= 50.0f)
        {
            projectile4->damage *= 2.0f;
        }
        playerBullets.push_back(projectile4);

        auto projectile5 = new self_bullet(selfBulletTemplate);
        projectile5->position.x = player.position.x + (player.width - projectile5->width) / 2.0f + 24;
        projectile5->position.y = player.position.y - projectile5->height;
        projectile5->damage /= 4.0f;
        if (!player.shift_sign)
            projectile5->speedX = projectile5->speed * 0.1f + distNeg(gen) * 150.0f;;
        projectile5->speed -= player.speedV;
        projectile5->speedX += player.speedH;
        if (player.power >= 50.0f)
        {
            projectile5->damage *= 2.0f;
        }
        playerBullets.push_back(projectile5);
    }
}

void BattleField::playerBulletsUpdate(float deltaTime)
{
    for(auto it = playerBullets.begin(); it != playerBullets.end(); )
    {
        auto bullet = *it;
        bullet->position.y -= bullet->speed * deltaTime;
        bullet->position.x += bullet->speedX * deltaTime;
        //子弹超出屏幕范围，删除子弹
        if ((bullet->position.y < 0 - bullet->height) ||
            (bullet->position.y > fieldH) ||
            (bullet->position.x < 0 - bullet->width) ||
            (bullet->position.x > fieldW) )
        {
            delete bullet;
            it = playerBullets.erase(it);
        }
        else
        {
            bool hit = false;
            SDL_Rect bulletRect = 
                {
                    static_cast<int>(bullet->position.x),
                    static_cast<int>(bullet->position.y),
                    bullet->width,
                    bullet->height
                };
            for (auto enemy : enemies)
            {
                if (std::visit([&bulletRect](auto&& enemy)
                {
                    SDL_Rect enemyRect = 
                    {
                        static_cast<int>(enemy->position.x),
                        static_cast<int>(enemy->position.y),
                        enemy->width,
                        enemy->height
                    };
                    return SDL_HasIntersection(&bulletRect, &enemyRect);
                }, enemy))
                {
                    std::visit([&bullet](auto&& enemy)
                    {
                        if (bullet->damage > enemy->defence * 1.1f)
                        {
                            enemy->health -= bullet->damage - enemy->defence;
                        }
                        else
                        {
                            enemy->health -= bullet->damage * 0.1f;
                        }
                    }, enemy);
                    delete bullet;
                    it = playerBullets.erase(it);
                    hit = true;
                    break; 
                }
            }
            if (!hit)
            {
                ++it;
            }
        }
    }
}

void BattleField::playerBulletsRender()
{
    for(auto projectile : playerBullets)
    {
        SDL_Rect bulletRect = 
        {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width,
            projectile->height
        };
        float angle = atan2(projectile->speedX, projectile->speed) * 180.0f / M_PI;
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(projectile->texture, 127);
        SDL_RenderCopyEx(game.getRenderer(), projectile->texture, NULL, &bulletRect, angle, NULL, SDL_FLIP_NONE);
    }
}

void BattleField::generateEnemy()
{
    if(!isBoss)
    {
        if (dist(gen) < 0.75f)
            {
                enemy1* Enemy1 = new enemy1(enemyTemplate);
                Enemy1->position.x = dist(gen) * (fieldW - Enemy1->width);
                Enemy1->position.y = -Enemy1->height; 
                enemies.push_back(Enemy1);
            }
            if (dist(gen) < 0.2f)
            {
                enemy4* Enemy4 = new enemy4(enemy4Template);
                Enemy4->position.x = dist(gen) * (fieldW - Enemy4->width);
                Enemy4->position.y = -Enemy4->height; 
                enemies.push_back(Enemy4);
            }
            if (dist(gen) < 0.03f)
            {
                enemy2* Enemy2 = new enemy2(enemy2Template);
                Enemy2->position.x = dist(gen) * (fieldW - Enemy2->width);
                Enemy2->position.y = -Enemy2->height; 
                enemies.push_back(Enemy2);
            }
            if (dist(gen) < 0.02f)
            {
                enemy3* Enemy3 = new enemy3(enemy3Template);
                Enemy3->position.x = dist(gen) * (fieldW - Enemy3->width);
                Enemy3->position.y = -Enemy3->height; 
                enemies.push_back(Enemy3);
            }
    }
    
}

void BattleField::spawnEnemy()
{
    if (dist(gen) < 0.002f && player.power < 5.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.003f && player.power >= 5.0f && player.power < 10.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.005f && player.power >= 10.0f && player.power < 25.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.015f && player.power >= 25.0f && player.power < 50.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.02f && player.power >= 50.0f)
    {
        generateEnemy();
    }
}

void BattleField::updateEnemies1(float deltaTime)
{
    EnemyManager::updateEnemies(this, deltaTime);
}

void BattleField::renderEnemies1()
{
    for(auto enemy : enemies)
    {
        std::visit([this](auto&& enemy)
        {
            using T = std::decay_t<decltype(enemy)>;
            if constexpr (std::is_same_v<T, enemy1*> ||
                          std::is_same_v<T, enemy2*> ||
                          std::is_same_v<T, enemy3*> ||
                          std::is_same_v<T, enemy4*> )
            {
                SDL_Rect enemyRect = 
                {
                    static_cast<int>(enemy->position.x),
                    static_cast<int>(enemy->position.y),
                    enemy->width,
                    enemy->height
                };
                int currentFrame = (SDL_GetTicks() - startTime) / 100;
                if (currentFrame % 5 == 0)
                {
                    SDL_RenderCopy(game.getRenderer(), enemy->texture1, NULL, &enemyRect);
                }
                else if (currentFrame % 5 == 1)
                {
                    SDL_RenderCopy(game.getRenderer(), enemy->texture2, NULL, &enemyRect);
                }
                else if (currentFrame % 5 == 2)
                {
                    SDL_RenderCopy(game.getRenderer(), enemy->texture3, NULL, &enemyRect);
                }
                else if (currentFrame % 5 == 3)
                {
                    SDL_RenderCopy(game.getRenderer(), enemy->texture4, NULL, &enemyRect);
                }
                else if (currentFrame % 5 == 4)
                {
                    SDL_RenderCopy(game.getRenderer(), enemy->texture5, NULL, &enemyRect);
                }
            }
            else if constexpr (std::is_same_v<T, boss1*>)
            {
                SDL_Rect enemyRect = 
                {
                    static_cast<int>(enemy->position.x),
                    static_cast<int>(enemy->position.y),
                    enemy->width,
                    enemy->height
                };
                int currentFrame = (SDL_GetTicks() - startTime) / 150;
                switch (currentFrame % 13)
                {
                    case 0:
                        enemy->texture = boss1Template.textures[0];
                        break;
                    case 1:
                        enemy->texture = boss1Template.textures[1];
                        break;
                    case 2:
                        enemy->texture = boss1Template.textures[2];
                        break;
                    case 3:
                        enemy->texture = boss1Template.textures[3];
                        break;
                    case 4:
                        enemy->texture = boss1Template.textures[4];
                        break;
                    case 5:
                        enemy->texture = boss1Template.textures[5];
                        break;
                    case 6:
                        enemy->texture = boss1Template.textures[6];
                        break;
                    case 7:
                        enemy->texture = boss1Template.textures[7];
                        break;
                    case 8:
                        enemy->texture = boss1Template.textures[8];
                        break;
                    case 9:
                        enemy->texture = boss1Template.textures[9];
                        break;
                    case 10:
                        enemy->texture = boss1Template.textures[10];
                        break;
                    case 11:
                        enemy->texture = boss1Template.textures[11];
                        break;
                    case 12:
                        enemy->texture = boss1Template.textures[12];
                        break;
                }
                SDL_RenderCopy(game.getRenderer(), enemy->texture, NULL, &enemyRect);
            }

    }, enemy);
    }
}

void BattleField::enemyShot(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy)
{
    EnemyManager::enemyShot(this, enemy);
} 

void BattleField::enemyLaserShot(std::variant<enemy1 *, enemy2 *, enemy3 *, enemy4*, boss1*> enemy)
{
    std::visit([this](auto&& enemy) {
        using T = std::decay_t<decltype(enemy)>;
        if constexpr (std::is_same_v<T, enemy3*>) 
        {
            auto laser = new enemy3_laser(enemy3LaserTemplate);
            laser->isActive = false;
            laser->startPosition.x = enemy->position.x + (enemy->width - laser->width) / 2.0f;
            laser->startPosition.y = enemy->position.y + enemy->height / 2.0f;
            laser->endPosition.x = player.position.x + player.width / 2.0f + getDirection(enemy).x * sqrt(fieldW*fieldW + fieldH*fieldH);
            laser->endPosition.y = player.position.y + player.height / 2.0f + getDirection(enemy).y * sqrt(fieldW*fieldW + fieldH*fieldH);
            laser->startTime = SDL_GetTicks();
            enemyLasers.push_back(laser);
        }
    }, enemy);
}

void BattleField::enemy1BulletsRender()
{
    for(auto projectile : enemy1Bullets)
    {
        std::visit([this](auto&& bullet) {
            SDL_Rect bulletRect = 
            {
                static_cast<int>(bullet->position.x),
                static_cast<int>(bullet->position.y),
                bullet->width,
                bullet->height
            };
            float angle = atan2(bullet->direction.y, bullet->direction.x) * 180.0f / M_PI - 90.0f;
            SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(bullet->texture, 255);
            SDL_RenderCopyEx(game.getRenderer(), bullet->texture, NULL, &bulletRect, angle, NULL, SDL_FLIP_NONE);
        }, projectile);
    }
    for(auto projectile : bossRevolveBullets)
    {
        std::visit([this](auto&& bullet) {
            SDL_Rect bulletRect = 
            {
                static_cast<int>(bullet->position.x),
                static_cast<int>(bullet->position.y),
                bullet->width,
                bullet->height
            };
            SDL_RenderCopyEx(game.getRenderer(), bullet->texture, NULL, &bulletRect, bullet->angle, NULL, SDL_FLIP_NONE);
        }, projectile);
    }
}

void BattleField::enemy1LasersRender()
{
    for (auto laser : enemyLasers)
    {
        float dx = laser->endPosition.x - laser->startPosition.x;
        float dy = laser->endPosition.y - laser->startPosition.y;
        float length = sqrt(dx * dx + dy * dy);
        
        float angle = atan2(-dx, dy) * 180.0f / M_PI;
        
        SDL_Rect laserRect = 
        {
            static_cast<int>(laser->startPosition.x),
            static_cast<int>(laser->startPosition.y),
            static_cast<int>(laser->width),  
            static_cast<int>(length)  
        };
        

        SDL_Point center = {laser->width / 2, 0}; 
        
        if (laser->isActive)
        {
            SDL_RenderCopyEx(game.getRenderer(), laser->activationTexture, NULL, &laserRect, angle, &center, SDL_FLIP_NONE);
        }
        else
        {
            SDL_RenderCopyEx(game.getRenderer(), laser->inactivationTexture, NULL, &laserRect, angle, &center, SDL_FLIP_NONE);
        }
    }
}

void BattleField::enemy1Death(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy)
{
    std::visit([this](auto&& enemy) {
        generatePower(enemy);
        exp += enemy->score;
        auto deathEffectInstance = new death_effect(deathEffectTemplate);
        deathEffectInstance->position.x = enemy->position.x;
        deathEffectInstance->position.y = enemy->position.y;
        deathEffectInstance->width = enemy->width;
        deathEffectInstance->height = enemy->height;
        deathEffectInstance->startTime = SDL_GetTicks();
        deathEffects.push_back(deathEffectInstance);
        delete enemy;
    }, enemy);
}

void BattleField::updatePlayer(float deltaTime)
{
    if (player.isDead)
        return;
    if (player.lives <= 0)
    {            
        player.isDead = true;
    }
    if (player.lives > player.livesMax)
    {
        player.lives = player.livesMax;
    }
    if (player.poisonTime > 0)
    {
        player.poisonTime -= deltaTime;
        player.lives -= 0.01f;
    }
}

void BattleField::generatePower(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy)
{
    std::visit([this](auto&& enemy) {
        power* Power = new power(powerTemplate);
        using T = std::decay_t<decltype(enemy)>;
        if constexpr (std::is_same_v<T, enemy1*>)
        {
            Power->value = dist(gen) / 2.0f + 0.1f;
        }
        else if constexpr (std::is_same_v<T, enemy2*>)
        {
            Power->value = dist(gen) / 1.6f + 0.12f;
        }
        else if constexpr (std::is_same_v<T, enemy3*>)
        {
            Power->value = dist(gen) / 1.3f + 0.15f;
        }
        else if constexpr (std::is_same_v<T, enemy4*>)
        {
            Power->value = dist(gen) / 1.8f + 0.12f;
        }
        Power->direction.x = static_cast<int>(dist(gen) * 200.0f) /10 * 10;
        Power->direction.y = static_cast<int>(dist(gen) * 100.0f) /10 * 10 + 50;
        if(dist(gen) > 0.5f)
            Power->direction.x = -Power->direction.x;
        Power->sizeTrue = Power->width * (0.5f + sqrtf(Power->value) * 0.5f);
        Power->position.x = enemy->position.x + (enemy->width - Power->sizeTrue) / 2.0f;
        Power->position.y = enemy->position.y + (enemy->height - Power->sizeTrue) / 2.0f;
        powers.push_back(Power);
    },enemy);
}

void BattleField::updatePowers(float deltaTime)
{
    SDL_Rect playerRect = 
    {
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        static_cast<int>(player.width),
        static_cast<int>(player.height)
    };
    for(auto it = powers.begin(); it != powers.end(); )
    {
        auto power = *it;
        if (power->direction.x < 0)
        {
            power->direction.x += power->acceleration;
        }
        else if (power->direction.x > 0)
        {
            power->direction.x -= power->acceleration;
        }
        power->position.x += power->direction.x * deltaTime;
        power->position.y += power->direction.y * deltaTime;

        //当按shift时p点向自机靠近
        Uint32 currentTime = SDL_GetTicks();
        auto keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_LSHIFT])
        {
            player.sneak = 1;
            player.shift_signStartTime = currentTime;
        }
        //2秒后sneak归0
        if (player.sneak == 1 && currentTime - player.shift_signStartTime > 1000)
        {
            player.sneak = 0;
        }

        if (player.sneak == 1)
        {
            //p点和自机距离小于200px时，p点向自机靠近
            if (sqrt(pow(power->position.x - player.position.x, 2) + pow(power->position.y - player.position.y, 2)) < 150)
            {
                auto dx = (player.position.x + player.width / 2.0f) - (power->position.x + power->sizeTrue / 2.0f);
                auto dy = (player.position.y + player.height / 2.0f) - (power->position.y + power->sizeTrue / 2.0f);
                auto distance = sqrt(dx * dx + dy * dy);
                dx /= distance;
                dy /= distance;
                power->position.x += dx * power->acceleration * deltaTime * 130;
                power->position.y += dy * power->accelerationY * deltaTime * 130;
            }
        }

        //每当score每次超过30的整数倍时，p点向自机靠近,持续2秒
        collectScale = static_cast<int>(exp / 50);
        if (collectScale != collectScaleOld)
        {
            collectSign = 1;
            collect_signStartTime = currentTime;
            collectScaleOld = collectScale;
        }
        //2秒后collectSign归0
        if (collectSign == 1 && currentTime - collect_signStartTime > 2000)
        {
            collectSign = 0;
        }
        
        if (collectSign == 1)
        {
            auto dx = (player.position.x + player.width / 2.0f) - (power->position.x + power->sizeTrue / 2.0f);
            auto dy = (player.position.y + player.height / 2.0f) - (power->position.y + power->sizeTrue / 2.0f);
            auto distance = sqrt(dx * dx + dy * dy);
            dx /= distance;
            dy /= distance;
            power->position.x += dx * power->acceleration * deltaTime * 500;
            power->position.y += dy * power->accelerationY * deltaTime * 500;
        }


        SDL_Rect powerRect = 
        {
            static_cast<int>(power->position.x),
            static_cast<int>(power->position.y),
            power->sizeTrue,
            power->sizeTrue
        };
        if ((power->position.y > fieldH) ||
            (power->position.y < 0 - power->sizeTrue) ||
            (power->position.x < 0 - power->sizeTrue) ||
            (power->position.x > fieldW) )
        {
            delete power;
            it = powers.erase(it);
        }
        else if (SDL_HasIntersection(&playerRect, &powerRect))
        {
            player.power += power->value;
            delete power;
            it = powers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //对scoreItems进行同样操作
    for(auto it = scoreItems.begin(); it != scoreItems.end(); )
    {
        auto scoreItem = *it;
        scoreItem->position.x += scoreItem->direction.x * deltaTime;
        scoreItem->position.y += scoreItem->direction.y * deltaTime;

        scoreItem->sizeTrue = sqrt(scoreItem->value) + 16;

        SDL_Rect scoreItemRect = 
        {
            static_cast<int>(scoreItem->position.x),
            static_cast<int>(scoreItem->position.y),
            scoreItem->sizeTrue,
            scoreItem->sizeTrue
        };
        if ((scoreItem->position.y > fieldH) ||
            (scoreItem->position.y < 0 - scoreItem->sizeTrue) ||
            (scoreItem->position.x < 0 - scoreItem->sizeTrue) ||
            (scoreItem->position.x > fieldW) )
        {
            delete scoreItem;
            it = scoreItems.erase(it);
        }
        else if (SDL_HasIntersection(&playerRect, &scoreItemRect))
        {
            exp += scoreItem->value;
            delete scoreItem;
            it = scoreItems.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void BattleField::renderPowers()
{
    for(auto power : powers)
    {
        SDL_Rect powerRect = 
        {
            static_cast<int>(power->position.x),
            static_cast<int>(power->position.y),
            power->sizeTrue,
            power->sizeTrue
        };
        SDL_RenderCopy(game.getRenderer(), power->texture, NULL, &powerRect);
    }

    for(auto scoreItem : scoreItems)
    {
        SDL_Rect scoreItemRect = 
        {
            static_cast<int>(scoreItem->position.x),
            static_cast<int>(scoreItem->position.y),
            scoreItem->sizeTrue,
            scoreItem->sizeTrue
        };
        SDL_RenderCopy(game.getRenderer(), scoreItem->texture, NULL, &scoreItemRect);
    }
}

void BattleField::statusRender()
{
    //残机（生命值)
    std::ostringstream lifeTextRaw;
    lifeTextRaw << "生命: ";
    std::string lifeText = lifeTextRaw.str();
    SDL_Surface* lifeSurface = TTF_RenderUTF8_Solid(statusFont, lifeText.c_str(), {255, 255, 255, 255});

    SDL_Texture* lifeTexture = SDL_CreateTextureFromSurface(game.getRenderer(), lifeSurface);
    SDL_Rect lifeRect = { fieldW + 32, 32, lifeSurface->w, lifeSurface->h };
    SDL_RenderCopy(game.getRenderer(), lifeTexture, NULL, &lifeRect);
    SDL_FreeSurface(lifeSurface);
    SDL_DestroyTexture(lifeTexture);

    SDL_Rect healthBar = { fieldW + 96, 36, healthBarW, healthBarH };
    SDL_RenderCopy(game.getRenderer(), healthBarTexture, NULL, &healthBar);
    if (player.lives < 20.0f)
    {
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
        SDL_Rect healthRect = { 
                            fieldW + 96 + static_cast<int>(healthBarW * (player.lives / player.livesMax)) + 1, 
                            37, 
                            healthBarW - static_cast<int>(healthBarW * (player.lives / player.livesMax)) - 2, 
                            healthBarH - 2
                            };
        SDL_RenderFillRect(game.getRenderer(), &healthRect);
    }

    //渲染灵力
    std::ostringstream powerTextRaw;
    powerTextRaw << "体力: " << std::fixed << std::setprecision(2) << player.power;
    std::string powerText = powerTextRaw.str();
    SDL_Surface* powerSurface = TTF_RenderUTF8_Solid(statusFont, powerText.c_str(), {255, 255, 255, 255});

    SDL_Texture* powerTexture = SDL_CreateTextureFromSurface(game.getRenderer(), powerSurface);
    SDL_Rect powerRect = { fieldW + 32, 64, powerSurface->w, powerSurface->h };
    SDL_RenderCopy(game.getRenderer(), powerTexture, NULL, &powerRect);
    SDL_FreeSurface(powerSurface);
    SDL_DestroyTexture(powerTexture);

    //渲染经验
    std::ostringstream expTextRaw;
    expTextRaw << "经验: " << exp;
    std::string expText = expTextRaw.str();
    SDL_Surface* expSurface = TTF_RenderUTF8_Solid(statusFont, expText.c_str(), {255, 255, 255, 255});

    SDL_Texture* expTexture = SDL_CreateTextureFromSurface(game.getRenderer(), expSurface);
    SDL_Rect expRect = { fieldW + 32, 96, expSurface->w, expSurface->h };
    SDL_RenderCopy(game.getRenderer(), expTexture, NULL, &expRect);
    SDL_FreeSurface(expSurface);
    SDL_DestroyTexture(expTexture);
    
    //渲染标题
    SDL_Rect titleRect = { fieldW + 160, 450, static_cast<int>(titleW / 1.5), static_cast<int>(titleH / 1.5) };
    SDL_RenderCopy(game.getRenderer(), titleTexture, NULL, &titleRect);
}

void BattleField::bossBarRender()
{
    //如果存在boss1
    for(auto& enemy : enemies) 
    {
        std::visit([this](auto&& enemy) {
            using T = std::decay_t<decltype(enemy)>;
            if constexpr (std::is_same_v<T, boss1*>)
            {
                SDL_Rect bossBar = { 12, 16, bossBarW, bossBarH };
                if (enemy->health / enemy->healthMax <= 0.33f)
                {
                    SDL_RenderCopy(game.getRenderer(), bossHealthBarLowTexture, NULL, &bossBar);
                }
                else
                    SDL_RenderCopy(game.getRenderer(), bossHealthBarTexture, NULL, &bossBar);

                SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
                SDL_Rect healthRect = 
                { 
                                        12 + 2 + static_cast<int>((bossBarW - 4) * (enemy->health / enemy->healthMax)), 
                                        17, 
                                        bossBarW - 4 - static_cast<int>((bossBarW - 4) * (enemy->health / enemy->healthMax)), 
                                        bossBarH - 2
                                    };
                SDL_RenderFillRect(game.getRenderer(), &healthRect);
            }
        }, enemy);  
    }
}

void BattleField::updateBattleBackground(float deltaTime)
{
    // 如果背景容器为空，初始化两个背景
    if (battleBackgrounds.empty())
    {
        background* bg1 = new background(bgTemplate1);
        background* bg2 = new background(bgTemplate2);
        
        bg1->position.x = 0;
        bg1->position.y = 0;
        
        bg2->position.x = 0;
        bg2->position.y = -bg1->height;  // 第二个背景在第一个背景上方
        
        battleBackgrounds.push_back(bg1);
        battleBackgrounds.push_back(bg2);
    }
    
    // 更新背景位置
    for (auto bg : battleBackgrounds)
    {
        bg->position.y += bg->speed * deltaTime;
        
        // 如果背景完全移出屏幕，将其重置到另一个背景的上方
        if (bg->position.y > fieldH)
        {
            for (auto otherBg : battleBackgrounds)
            {
                if (otherBg != bg)
                {
                    bg->position.y = otherBg->position.y - bg->height;
                    break;
                }
            }
        }
    }
}

void BattleField::powerManage()
{
    if (player.power > 100.0f)
    {
        player.power = 100.0f;
    }

    if (player.power < 0.0f)
    {
        player.power = 0.0f;
    }
}

void BattleField::bossGeneratePower(boss1* enemy)
{
    power* Power = new power(powerTemplate);   
    Power->value = dist(gen) / 0.25f + 10.0f;
    Power->direction.x = static_cast<int>(dist(gen) * 200.0f) /10 * 10;
    Power->direction.y = static_cast<int>(dist(gen) * 100.0f) /10 * 10 + 50;
    if(dist(gen) > 0.5f)
        Power->direction.x = -Power->direction.x;
    Power->sizeTrue = Power->width * (sqrtf(Power->value) * 0.3f);
    Power->position.x = enemy->position.x + (enemy->width - Power->sizeTrue) / 2.0f;
    Power->position.y = enemy->position.y + (enemy->height - Power->sizeTrue) / 2.0f;
    powers.push_back(Power);
}

void BattleField::deathEffectsUpdate()
{
    for (auto it = deathEffects.begin(); it != deathEffects.end(); )
    {
        auto effect = *it;
        int frameIndex = static_cast<int>((SDL_GetTicks() - effect->startTime) / effect->speed);
        
        if (frameIndex >= 0 && frameIndex < 16)
        {
            effect->texture = effect->textures[frameIndex];
        }
        
        if ((SDL_GetTicks() - effect->startTime) / effect->speed >= 16)
        {
            delete effect;
            it = deathEffects.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void BattleField::deathEffectsRender()
{
    for (auto& effect : deathEffects)
    {
        if (effect && effect->texture)
        {
            SDL_Rect effectRect = 
            {
                static_cast<int>(effect->position.x),
                static_cast<int>(effect->position.y),
                effect->width,
                effect->height
            };
            SDL_RenderCopy(game.getRenderer(), effect->texture, NULL, &effectRect);
        }
    }
}

void BattleField::ItemToPlayer()
{
    //对于scoreItem,如果absorbed为true，则奔向自机
    for (auto& item : scoreItems)
    {
        if (item->absorbed)
        {
            auto dx = (player.position.x + player.width / 2.0f) - (item->position.x + item->sizeTrue / 2.0f);
            auto dy = (player.position.y + player.height / 2.0f) - (item->position.y + item->sizeTrue / 2.0f);
            auto distance = sqrt(dx * dx + dy * dy);
            dx /= distance;
            dy /= distance;
            item->direction = {1200.0f * dx, 1200.0f * dy};
        }
    }
}

void BattleField::rollingBackgroundRender()
{
    for (auto bg : battleBackgrounds)
    {
        SDL_Rect bgRect = { static_cast<int>(bg->position.x), static_cast<int>(bg->position.y), bg->width, bg->height };
        SDL_RenderCopy(game.getRenderer(), bg->texture, NULL, &bgRect);
    }
}
