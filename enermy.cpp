#include "enermy.h"
#include "self.h"
#include "BattleField.h" 
#include <list>

void boss1::card1(BattleField& battlefield)
{
    //最后技能了
    for(int i=0;i<240;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;
        projectile->texture = projectile->arrow;
        projectile->textureAlt = projectile->arrow;
        projectile->textureSlowed = projectile->arrow;
        projectile->textureFrozen = projectile->arrow; 
        projectile->width = 6;
        projectile->height = 32;
        float angle = (i * M_PI / 36.0f) + (i * i * M_PI / 41472.0f); 
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 100 + (static_cast<int>(pow(i, 1.0f / 2.0f)) * 10);
        projectile->poison = 1;

        battlefield.enemy1Bullets.push_back(projectile); 
    }
}

void boss1::card2(BattleField& battlefield)
{
    //在自身圆周源源不断的产生随机方向的子弹，持续5秒
    if (!skill2)
    {
        skill2 = 1;
        skill2StartTime = SDL_GetTicks();
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - skill2StartTime < 5000 && skill2)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;

        float initialSpeed = 200 + (rand() % 100);
        float angle = static_cast<float>(rand() % 360) * M_PI / 180.0f;
        float vx = initialSpeed * cos(angle);
        float vy = initialSpeed * sin(angle);

        vx += speedX;
        float finalSpeed = sqrt(vx * vx + vy * vy);

        if (finalSpeed > 0) 
        {
            projectile->direction = SDL_FPoint{vx / finalSpeed, vy / finalSpeed};
            projectile->speed_ = finalSpeed;
        } 
        else 
        {
            projectile->direction = SDL_FPoint{0, 1};
            projectile->speed_ = 0;
        }
        if (rand() % 12 == 1)
        {
            projectile->width = 48;
            projectile->height = 48;
            projectile ->damage = 3;
            projectile->texture = projectile->large;
            projectile->textureAlt = projectile->large;
            projectile->textureFrozen = projectile->large;
            projectile->textureSlowed = projectile->large;
        }
        battlefield.enemy1Bullets.push_back(projectile);  
    }
    else if (currentTime - skill2StartTime >= 5000)
    {
        skill2 = 0;
    }
    
}

void boss1::card3(BattleField& battlefield)
{
    //在自身一周产生48个子弹
    for(int i=0;i<48;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;
        float angle = (i * M_PI / 24.0f); 
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 250;
        battlefield.enemy1Bullets.push_back(projectile); 
    }
    //在自身200px范围内随机位置生成一个enemy2
    auto enemy = new enemy2(battlefield.enemy2Template);
    enemy->position.x = position.x + width / 2.0f + (rand() % 400 - 200);
    enemy->position.y = position.y + height / 2.0f + (rand() % 200 - 200);
    enemy->health = 16.0f;
    enemy->speed = 40;
    enemy->score = 6;
    battlefield.enemies.push_back(enemy);
}

void boss1::card4(BattleField& battlefield)
{
    //向玩家的大概方向（偏差-10～10度）随机发射24个子弹，速度较快
    for(int i=0;i<16;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32;
        float baseAngle = atan2((battlefield.player.position.y + battlefield.player.height / 2.0f) - (position.y + height / 2.0f),
                                (battlefield.player.position.x + battlefield.player.width / 2.0f) - (position.x + width / 2.0f));
        float angleOffset = ((rand() % 21) - 10) * M_PI / 180.0f; 
        float angle = baseAngle + angleOffset;
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 450 + (rand() % 100);
        battlefield.enemy1Bullets.push_back(projectile); 
    }
}

void boss1::card5(BattleField& battlefield)
{
    //发射螺旋形弹幕*4
    for(int i=0;i<60;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;
        float angle = (i * M_PI / 30.0f);
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 80 + 0.04*i*i;
        battlefield.enemy1Bullets.push_back(projectile);

        auto projectile_ = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile_->position.x = position.x + (width - projectile_->width) / 2.0f;
        projectile_->position.y = position.y + height / 2.0f + 32.0f;
        float angle_ = (i * M_PI / 30.0f + M_PI/2.0f);
        projectile_->direction = SDL_FPoint{cos(angle_), sin(angle_)};
        projectile_->speed_ = 80 + 0.04*i*i;
        battlefield.enemy1Bullets.push_back(projectile_);

        auto projectile__ = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile__->position.x = position.x + (width - projectile__->width) / 2.0f;
        projectile__->position.y = position.y + height / 2.0f + 32.0f;
        float angle__ = (i * M_PI / 30.0f + M_PI);
        projectile__->direction = SDL_FPoint{cos(angle__), sin(angle__)};
        projectile__->speed_ = 80 + 0.04*i*i;
        battlefield.enemy1Bullets.push_back(projectile__);

        auto projectile___ = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile___->position.x = position.x + (width - projectile___->width) / 2.0f;
        projectile___->position.y = position.y + height / 2.0f + 32.0f;
        float angle___ = (i * M_PI / 30.0f + M_PI * 1.5f);
        projectile___->direction = SDL_FPoint{cos(angle___), sin(angle___)};
        projectile___->speed_ = 80 + 0.04*i*i;
        battlefield.enemy1Bullets.push_back(projectile___);

    }
}

void boss1::card6(BattleField &battlefield)
{
    //生成一个旋转子弹
    auto revolvingBullet = new boss1_bullet_revolving(battlefield.boss1BulletRevolvingTemplate);
    int randomDirection = rand() % 4;

    float offsetX = 0.0f;
    float offsetY = 0.0f;

    switch (randomDirection)
    {
        case 0: 
            offsetX = 80.0f;
            break;
        case 1:
            offsetX = -80.0f;
            break;
        case 2: 
            offsetY = 80.0f;
            break;
        case 3: 
            offsetY = -80.0f;
            break;
    }

    revolvingBullet->position.x = position.x + width / 2.0f + offsetX;
    revolvingBullet->position.y = position.y + height / 2.0f + offsetY + 32.0f;
    revolvingBullet->width = 20;
    revolvingBullet->height = 20;
    battlefield.bossRevolveBullets.push_back(revolvingBullet);
}

void boss1::card7(BattleField &battlefield)
{
    //花
    for(int i=0;i<720;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;
        projectile->width = 48;
        projectile->height = 48;
        projectile->texture = projectile->sakura;
        projectile->textureAlt = projectile->sakura;
        projectile->textureFrozen = projectile->sakura;
        projectile->textureSlowed = projectile->sakura;
        projectile->damage = -2.0f;
        projectile->direction = SDL_FPoint{
        cos(static_cast<float>(i * M_PI / 360.0f + 0.3f * sin((i % 60) * M_PI / 30.0f) + (i / 60) * M_PI / 12.0f)),
        sin(static_cast<float>(i * M_PI / 360.0f + 0.3f * sin((i % 60) * M_PI / 30.0f) + (i / 60) * M_PI / 12.0f))
    };
        projectile->speed_ = static_cast<int>(120.0f + (i / 60) * 20.0f + 40.0f * cos((i % 60) * M_PI / 20.0f));
        battlefield.enemy1Bullets.push_back(projectile); 
    }
}

void boss1::card8(BattleField &battlefield)
{
    //漩涡
    for(int i=0;i<360;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        float spiralRadius = 0.6 * i;
        float angle = i * 0.2f; 
        projectile->position.x = position.x + width / 2.0f + spiralRadius * cos(angle);
        projectile->position.y = position.y + width / 2.0f + spiralRadius * sin(angle) + 32.0f;
        projectile->direction = SDL_FPoint{cos(static_cast<float>(angle + M_PI_2)), sin(static_cast<float>(angle + M_PI_2))}; // 切线方向
        projectile->speed_ = 100 + 0.2 * i;
        battlefield.enemy1Bullets.push_back(projectile);
    }
}

void boss1::card9(BattleField &battlefield)
{
    //向玩家的大概方向（偏差-15～15度）随机发射32个子弹，速度较快
    for(int i=0;i<32;i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        projectile->position.x = position.x + (width - projectile->width) / 2.0f + 32.0f;
        projectile->position.y = position.y + height / 2.0f;
        float baseAngle = atan2((battlefield.player.position.y + battlefield.player.height / 2.0f) - (position.y + height / 2.0f),
                                (battlefield.player.position.x + battlefield.player.width / 2.0f) - (position.x + width / 2.0f));
        float angleOffset = ((rand() % 31) - 15) * M_PI / 180.0f; 
        float angle = baseAngle + angleOffset;
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 500 + (rand() % 100);
        battlefield.enemy1Bullets.push_back(projectile); 
    }
}

void boss1::card10(BattleField &battlefield, int offset)
{
    // 从中心发射的螺旋系统，增加时间间隔
    for(int layer = 0; layer < 3; layer++) {
        for(int i = 0; i < 24; i++) {
            // 生成六重对称的弹幕
            for(int symmetry = 0; symmetry < 6; symmetry++) {
                auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
                
                float offsetRadius = static_cast<float>(layer * 5.0f);
                float angleOffset = static_cast<float>(symmetry * M_PI / 3.0f);
                projectile->position.x = position.x + width / 2.0f + offsetRadius * cos(angleOffset);
                projectile->position.y = position.y + height / 2.0f + offsetRadius * sin(angleOffset) + 32.0f;
                
                // 螺旋角度系统，增加间隔
                float baseAngle = static_cast<float>(i * M_PI / 12.0f);
                float symmetryAngle = static_cast<float>(symmetry * M_PI / 3.0f);
                float spiralOffset = static_cast<float>(layer * M_PI / 6.0f);
                float angle = baseAngle + symmetryAngle + spiralOffset + static_cast<float>(offset * M_PI / 180.0f);
                
                projectile->width = 16 + layer * 2;
                projectile->height = 16 + layer * 2;
                projectile->speed_ = 80.0f + layer * 30.0f + static_cast<float>(i * 2.0f);
                projectile->direction = SDL_FPoint{cos(angle), sin(angle)};

                if (symmetry % 2 == 0)
                {
                    projectile->texture = projectile->blue;
                    projectile->textureAlt = projectile->blue;
                    projectile->textureFrozen = projectile->blue;
                    projectile->textureSlowed = projectile->blue;
                }
                
                battlefield.enemy1Bullets.push_back(projectile);
            }
        }
    }
    
    for(int petal = 0; petal < 6; petal++) {
        for(int i = 0; i < 12; i++) {
            auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
            
            float offsetRadius = 10.0f;
            float angleOffset = static_cast<float>(petal * M_PI / 3.0f);
            projectile->position.x = position.x + width / 2.0f + offsetRadius * cos(angleOffset);
            projectile->position.y = position.y + height / 2.0f + offsetRadius * sin(angleOffset) + 32.0f;
            
            float petalAngle = static_cast<float>(petal * M_PI / 3.0f);
            float spreadAngle = static_cast<float>(i * M_PI / 24.0f - M_PI / 48.0f);
            float angle = petalAngle + spreadAngle + static_cast<float>(offset * M_PI / 180.0f);
            
            projectile->width = 14;
            projectile->height = 14;

            float speedVariation = static_cast<float>(i * 5.0f);
            projectile->speed_ = 60.0f + speedVariation;
            projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
            
            battlefield.enemy1Bullets.push_back(projectile);
        }
    }
    
    for(int ring = 0; ring < 2; ring++) {
        for(int i = 0; i < 18; i++) {
            auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
            float offsetRadius = static_cast<float>(ring * 8.0f);
            float angleOffset = static_cast<float>(i * M_PI / 9.0f);
            projectile->position.x = position.x + width / 2.0f + offsetRadius * cos(angleOffset);
            projectile->position.y = position.y + height / 2.0f + offsetRadius * sin(angleOffset) + 32.0f;

            float baseAngle = static_cast<float>(i * M_PI / 9.0f);
            float ringOffset = static_cast<float>(ring * M_PI / 18.0f);
            float angle = baseAngle + ringOffset + static_cast<float>(offset * M_PI / 180.0f);
            
            projectile->width = 12;
            projectile->height = 12;
            
            projectile->speed_ = 50.0f + ring * 20.0f + static_cast<float>(i * 3.0f);
            
            projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
            
            battlefield.enemy1Bullets.push_back(projectile);
        }
    }
}

void boss1::card11(BattleField &battlefield)
{
    //极尽极端超级绚丽复杂的分12组区域的弹幕代码
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 36; j++)
        {
            auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
            float angle = (i * M_PI / 6.0f) + (j * j * M_PI / 240.0f);
            float radius = 20.0f + j * 5.0f;
            projectile->position.x = position.x + width / 2.0f + 0.1 * radius * cos(angle);
            projectile->position.y = position.y + height / 2.0f + 0.1 * radius * sin(angle) + 32.0f;
            projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
            projectile->speed_ = 10 + j * 10;
            battlefield.enemy1Bullets.push_back(projectile);
        }
    }

}

void boss1::card12(BattleField &battlefield)
{
    //周围一周生成12个子弹
    for (int i = 0; i < 12; i++)
    {
        auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
        float angle = i * M_PI / 6.0f;
        projectile->position.x = position.x + (width - projectile->width) / 2.0f;
        projectile->position.y = position.y + height / 2.0f + 32.0f;
        projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
        projectile->speed_ = 100;
        projectile->width = 32;
        projectile->height = 32;
        projectile->explosion = 3;
        projectile->damage = 4;
        battlefield.enemy1Bullets.push_back(projectile);
    }
}

void boss1::card13(BattleField &battlefield)
{
    //与c12配合使用，分裂
    std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> newBullets;
    for (auto it = battlefield.enemy1Bullets.begin(); it != battlefield.enemy1Bullets.end();)
    {
        std::visit([&battlefield, &it, &newBullets](auto&& bullet) {
            if (bullet->explosion == 3)
            {
                for (int i = 0; i < 12; i++)
                {
                    auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
                    projectile->position.x = bullet->position.x + (bullet->width - projectile->width) / 2.0f;
                    projectile->position.y = bullet->position.y + (bullet->height - projectile->height) / 2.0f;
                    float angle = i * M_PI / 6.0f;
                    projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
                    projectile->speed_ = 300;
                    projectile->explosion = 2;
                    projectile->width = 16;
                    projectile->height = 16;
                    projectile->damage = 1;
                    newBullets.push_back(projectile);
                }
                delete bullet;
                it = battlefield.enemy1Bullets.erase(it);
            }
            else if (bullet->explosion == 2)
            {
                for (int i = 0; i < 8; i++)
                {
                    auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
                    projectile->position.x = bullet->position.x + (bullet->width - projectile->width) / 2.0f;
                    projectile->position.y = bullet->position.y + (bullet->height - projectile->height) / 2.0f;
                    float angle = i * M_PI / 4.0f;
                    projectile->direction = SDL_FPoint{cos(angle), sin(angle)};
                    projectile->speed_ = 100;
                    projectile->explosion = 1;
                    projectile->damage = 0.4;
                    projectile->textureAlt = projectile->sakura2;
                    projectile->textureFrozen = projectile->sakura2;    
                    projectile->textureSlowed = projectile->sakura2;
                    newBullets.push_back(projectile);
                }
                delete bullet;
                it = battlefield.enemy1Bullets.erase(it);
            }
            else if (bullet->explosion == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    auto projectile = new boss1_bullet(battlefield.boss1BulletTemplate);
                    projectile->position.x = bullet->position.x + (bullet->width - projectile->width) / 2.0f;
                    projectile->position.y = bullet->position.y + (bullet->height - projectile->height) / 2.0f;
                    float angle = M_PI/2 + (i - 2) * M_PI/6;
                    projectile->direction = SDL_FPoint{cos(angle) * 0.8f , sin(angle) * 1.5f};
                    projectile->speed_ = 150;
                    projectile->explosion = 0;
                    projectile->damage = 0.0;
                    projectile->width = 10;
                    projectile->height = 10;
                    projectile->textureAlt = projectile->sakura3;
                    projectile->textureFrozen = projectile->sakura3;    
                    projectile->textureSlowed = projectile->sakura3;
                    newBullets.push_back(projectile);
                }
                delete bullet;
                it = battlefield.enemy1Bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }, *it);
    }
    
    // 将新子弹合并到主列表中
    battlefield.enemy1Bullets.splice(battlefield.enemy1Bullets.end(), newBullets);
}

void boss1::moveHorizont(float deltaTime,float maxSpeedX)
{
    if (speedX > 0) 
    {
        speedX += acceleration * deltaTime;
        if (speedX > maxSpeedX) 
            speedX = maxSpeedX;
    } 
    else 
    {
        speedX -= acceleration * deltaTime;
        if (speedX < -maxSpeedX) 
            speedX = -maxSpeedX;
    }
    position.x += speedX * deltaTime;
    if (position.x < 0)
    {
        position.x = 0;
        speedX = initialSpeedX;
    }
    else if (position.x + width > fieldW)
    {
        position.x = fieldW - width;
        speedX = -initialSpeedX; 
    }
}

void boss1::bulletRevolve(float deltaTime, BattleField &battlefield)
{
    for (auto bullet : battlefield.bossRevolveBullets)
    {
        std::visit([this, deltaTime](auto&& revolvingBullet) {
            revolvingBullet->revolvingPosition.x = this->position.x + this->width / 2.0f - 10.0f;
            revolvingBullet->revolvingPosition.y = this->position.y + this->height / 2.0f - 10.0f + 32.0f;

            const float radius = 160.0f; 
            float angularSpeed = revolvingBullet->speed / radius;
            revolvingBullet->angle += angularSpeed * deltaTime;

            revolvingBullet->position.x = revolvingBullet->revolvingPosition.x + radius * cos(revolvingBullet->angle);
            revolvingBullet->position.y = revolvingBullet->revolvingPosition.y + radius * sin(revolvingBullet->angle);
        }, bullet);
    }
        //如果battlefield.playerbullets与子弹碰撞，删除playerbullet
    for (auto playerIt = battlefield.playerBullets.begin(); playerIt != battlefield.playerBullets.end();)
    {
        auto playerBullet = *playerIt;
        bool playerBulletHit = false;

        SDL_Rect playerBulletRect = {
            static_cast<int>(playerBullet->position.x),
            static_cast<int>(playerBullet->position.y),
            playerBullet->width,
            playerBullet->height
        };

        for (const auto& revolveVariant : battlefield.bossRevolveBullets)
        {
            std::visit([&playerBulletRect, &playerBulletHit](auto&& revolvingBullet) {
                SDL_Rect revolveBulletRect = {
                    static_cast<int>(revolvingBullet->position.x),
                    static_cast<int>(revolvingBullet->position.y),
                    revolvingBullet->width,
                    revolvingBullet->height
                };

                if (SDL_HasIntersection(&playerBulletRect, &revolveBulletRect))
                {
                    playerBulletHit = true;
                }
            }, revolveVariant);

            if (playerBulletHit) {
                break;
            }
        }

        if (playerBulletHit)
        {
            delete playerBullet;
            playerIt = battlefield.playerBullets.erase(playerIt);
        }
        else
        {
            ++playerIt;
        }
    }
    SDL_Rect playerRect = 
    {
        static_cast<int>(battlefield.player.position.x),
        static_cast<int>(battlefield.player.position.y),
        battlefield.player.width,
        battlefield.player.height
    };

    for (auto it = battlefield.bossRevolveBullets.begin(); it != battlefield.bossRevolveBullets.end();)
    {
        bool hit = false;
        std::visit([&playerRect, &battlefield, &hit](auto&& revolvingBullet) {
            SDL_Rect revolveBulletRect = {
                static_cast<int>(revolvingBullet->position.x),
                static_cast<int>(revolvingBullet->position.y),
                revolvingBullet->width,
                revolvingBullet->height
            };

            if (SDL_HasIntersection(&playerRect, &revolveBulletRect) && !battlefield.player.isDead)
            {
                if (revolvingBullet->damage >= battlefield.player.defence * 1.1f)
                {
                    battlefield.player.lives -= (revolvingBullet->damage - battlefield.player.defence);
                }
                else
                {
                    battlefield.player.lives -= revolvingBullet->damage * 0.1f;
                }
                battlefield.player.power -= (revolvingBullet->damage * (battlefield.player.power / battlefield.player.powerMax) * 5.0f);
                
                hit = true;
            }
        }, *it);

        if (hit)
        {
            std::visit([](auto&& revolvingBullet) {
                delete revolvingBullet;
            }, *it);
            it = battlefield.bossRevolveBullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void boss1::convertBulletsToScores(BattleField &battlefield,float scoreValue)
{
    //所有敌机子弹转化为score,先统计子弹数量
    int bulletCount = battlefield.enemy1Bullets.size();
    for (auto it = battlefield.enemy1Bullets.begin(); it != battlefield.enemy1Bullets.end();)
    {
        std::visit([&battlefield, &bulletCount, &scoreValue](auto&& bullet) {
            auto score = new scoreItem(battlefield.scoreItemTemplate);
            score->position.x = bullet->position.x + (bullet->width - score->width) / 2.0f;
            score->position.y = bullet->position.y + (bullet->height - score->height) / 2.0f;
            score->absorbed = true;
            score->value = scoreValue / static_cast<float>(bulletCount);
            battlefield.scoreItems.push_back(score);
            delete bullet;
        }, *it);
        it = battlefield.enemy1Bullets.erase(it);
    }
    
}
