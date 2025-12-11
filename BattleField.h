#pragma once
#include <list>
#include "scene.h"
#include "self.h"
#include "enermy.h"
#include "item.h"
#include <random>

class game;

struct background
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    float offset = 0;
    int width = fieldBGw;
    int height = fieldBGh / 2;
    int speed = 20;
};

class BattleField : public scene
{
    friend struct boss1;
    friend class EnemyManager;
public:
    BattleField(int is_boss);
    ~BattleField(); 

    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;

    void keyboardControl(float deltaTime);
    void selfShoot();
    void playerBulletsUpdate(float deltaTime);
    void playerBulletsRender();
    void generateEnemy();
    void spawnEnemy();
    void updateEnemies1(float deltaTime);
    void renderEnemies1();
    void enemyShot(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy);
    void enemyLaserShot(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy);
    template<typename EnemyType>
    SDL_FPoint getDirection(EnemyType *enemy)
    {
        auto dx = (player.position.x + player.width / 2.0f) - (enemy->position.x + enemy->width / 2.0f);
        auto dy = (player.position.y + player.height / 2.0f) - (enemy->position.y + enemy->height / 2.0f);
        auto distance = sqrt(dx * dx + dy * dy);
        dx /= distance;
        dy /= distance;
        return SDL_FPoint{dx, dy};
    }
    void enemy1BulletsRender();
    void enemy1LasersRender();
    void enemy1Death(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy);
    void updatePlayer(float deltaTime);
    void generatePower(std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy);
    void updatePowers(float deltaTime);
    void renderPowers();
    void statusRender();
    void bossBarRender();
    void rollingBackgroundRender();
    void updateBattleBackground(float deltaTime);
    void powerManage();
    void bossGeneratePower(boss1* enemy);
    void deathEffectsUpdate();
    void deathEffectsRender();

    Uint32 startTime;
    Uint32 collect_signStartTime = 0;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* titleTexture = nullptr;
    SDL_Texture* healthBarTexture = nullptr;
    SDL_Texture* bossHealthBarTexture = nullptr;
    SDL_Texture* bossHealthBarLowTexture = nullptr;
    bool z_sign = 1;
    bool spaceSign = 0;
    bool c_sign = 0;
    bool x_sign = 0;
    bool v_sign = 0;
    bool s_sign = 0;
    
    bool collectSign = 0;
    bool isPaused = false;
    int collectScale = 0;
    int collectScaleOld = 0;
    bool hasBoss = 0;
    bool bossDead = 0;
    SDL_Texture* pauseTextTexture1 = nullptr;
    SDL_Texture* pauseTextTexture2 = nullptr;
    SDL_Texture* pauseTextTexture3 = nullptr;
    SDL_Texture* deathTextTexture1 = nullptr;
    SDL_Texture* deathTextTexture2 = nullptr;

private:
    //随机数种子
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;
    std::uniform_real_distribution<float> distNeg;
    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int exp = 0;

    //模版与容器
    self_bullet selfBulletTemplate;
    std::list<self_bullet*> playerBullets;

    enemy1 enemyTemplate;
    enemy2 enemy2Template;
    enemy3 enemy3Template;
    enemy4 enemy4Template;
    boss1 boss1Template;

    std::list<std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*>> enemies;

    enemy1_bullet enemy1BulletTemplate;
    enemy2_bullet enemy2BulletTemplate;
    enemy3_laser enemy3LaserTemplate;
    enemy4_bullet enemy4BulletTemplate;
    boss1_bullet boss1BulletTemplate;
    boss1_bullet_revolving boss1BulletRevolvingTemplate;
    death_effect deathEffectTemplate;

    std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> enemy1Bullets;
    std::list<enemy3_laser*> enemyLasers;
    std::list<std::variant<boss1_bullet_revolving*>> bossRevolveBullets;
    std::list<death_effect*> deathEffects;

    power powerTemplate;
    std::list<power*> powers;

    background bgTemplate1;
    background bgTemplate2;
    std::list<background*> battleBackgrounds;

    bool isBoss = 0;
};







