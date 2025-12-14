#include "enemyBehaviour.h"

void EnemyManager::updateEnemies(BattleField* battleField, float deltaTime)
{
    auto currentTime = SDL_GetTicks();
    for(auto it = battleField->enemies.begin(); it != battleField->enemies.end(); )
    {
        std::visit([&it, &currentTime, &player = battleField->player, deltaTime, battleField](auto&& enemy) 
        {
            using T = std::decay_t<decltype(enemy)>;
            if constexpr (std::is_same_v<T, enemy1*> || std::is_same_v<T, enemy2*> || std::is_same_v<T, enemy4*>)
            {
                enemy->position.y += enemy->speed * deltaTime;
            }
            if constexpr (std::is_same_v<T, enemy3*>)
            {
                if (!enemy->isShooting)
                    enemy->position.y += enemy->speed * deltaTime;
            }
            if constexpr (std::is_same_v<T, boss1*>)
            {
                if(enemy->phase_left == 3)
                {
                    if(enemy->health > enemy->healthMax * 0.75f)
                    {
                        if (currentTime - enemy->lastSpellCardTime > static_cast<Uint32>(2000 * (enemy->c10o + 1)) && enemy->c10[enemy->c10o])
                        {
                            enemy->card10(*battleField, enemy->c10o * 10);
                            enemy->c10[enemy->c10o - 1] = false;
                            enemy->c10o++;
                        }
                        if (enemy->c10o == 23)
                        {
                            for (int j = 0; j < 24; j++)
                            {
                                enemy->c10[j] = true;
                            }
                            enemy->c10o = 0;
                            enemy->lastSpellCardTime = currentTime;
                        }

                    }
                    if(enemy->health <= enemy->healthMax * 0.75f && !enemy->bonus1)
                    {
                        enemy->bonus1 = true;  
                        battleField->bossGeneratePower(enemy);
                        enemy->convertBulletsToScores(*battleField, 50.0f);
                    }
                    if(enemy->health > enemy->healthMax * 0.5f && enemy->health < enemy->healthMax * 0.75f && currentTime - enemy->lastSpellCardTime > 5000)
                    {
                        enemy->card2(*battleField);
                        enemy->card2(*battleField);
                        
                        if (currentTime - enemy->lastSpellCardTime > 12000)
                        {
                            enemy->card3(*battleField);
                            enemy->lastSpellCardTime = currentTime;
                        }
                    }
                    if(enemy->health <= enemy->healthMax * 0.5f && !enemy->bonus2)
                    {
                        enemy->bonus2 = true;  
                        battleField->bossGeneratePower(enemy);
                        enemy->convertBulletsToScores(*battleField, 50.0f);
                        //清除所有非boss敌机
                        for (auto it = battleField->enemies.begin(); it != battleField->enemies.end(); )
                        {
                            bool shouldErase = std::visit([&battleField](auto&& otherEnemy) {
                                using U = std::decay_t<decltype(otherEnemy)>;
                                if constexpr (std::is_same_v<U, enemy1*> ||
                                              std::is_same_v<U, enemy2*> ||
                                              std::is_same_v<U, enemy3*> ||
                                              std::is_same_v<U, enemy4*> )
                                {
                                    delete otherEnemy;
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }, *it);
                            if (shouldErase)
                            {
                                it = battleField->enemies.erase(it);
                            }
                            else
                            {
                                ++it;
                            }
                        }
                    }
                    if(enemy->health > enemy->healthMax * 0.25f && enemy->health < enemy->healthMax * 0.5f)
                    {
                        if (currentTime - enemy->lastSpellCard12Time > 6000)
                        {
                            enemy->card12(*battleField);
                            enemy->card13Used1 = false;
                            enemy->card13Used2 = false;
                            enemy->lastSpellCard12Time = currentTime;
                        }
                        else if (currentTime - enemy->lastSpellCard12Time > 1000 && !enemy->card13Used1)
                        {
                            enemy->card13(*battleField);
                            enemy->card13Used1 = true;
                        }
                        else if (currentTime - enemy->lastSpellCard12Time > 2000 && !enemy->card13Used2)
                        {
                            enemy->card13(*battleField);
                            enemy->card13Used2 = true;
                        }    
                    }

                    if(enemy->health <= enemy->healthMax * 0.25f && !enemy->bonus3)
                    {
                        enemy->bonus3 = true;  
                        battleField->bossGeneratePower(enemy);
                        enemy->convertBulletsToScores(*battleField, 100.0f);
                    }
                    if(enemy->health <= enemy->healthMax * 0.25f)
                    {
                        enemy->defence = 0.1f;
                        enemy->card2(*battleField);
                        enemy->moveHorizont(deltaTime, 250.0f);
                    }
                    if (enemy->health <= 0)
                    {
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        enemy->phase_left = 2;
                        enemy->health = enemy->healthMax / 2.0f;
                        enemy->defence = 0.2f;
                        battleField->player.lives += 1.0f;
                        //清空场上子弹
                        enemy->convertBulletsToScores(*battleField, 100.0f);
                    }
                }
                if (enemy->phase_left == 2)
                {
                    if (enemy->health > 0.25f * enemy->healthMax && enemy->health <= 0.5f * enemy->healthMax)
                    {
                        enemy->moveHorizont(deltaTime, (1 - (enemy->health - 0.25f * enemy->healthMax) / (0.25f * enemy->healthMax)) * 700.0f + 50.0f);
                    }
                    if (enemy->health > 0.25f * enemy->healthMax && enemy->health <= 0.5f * enemy->healthMax && currentTime - enemy->lastSpellCardTime > (enemy->health - 0.25f * enemy->healthMax) / (0.25f * enemy->healthMax) * 2000.0f + 400.0f)
                    {
                        enemy->card4(*battleField);
                        enemy->lastSpellCardTime = currentTime;
                    }
                    if (enemy->health <= 0.25f * enemy->healthMax && !enemy->bonus4)
                    {
                        enemy->bonus4 = true;  
                        battleField->bossGeneratePower(enemy);
                        enemy->convertBulletsToScores(*battleField, 100.0f);
                    }
                    if (enemy->health <= 0.25f * enemy->healthMax && fabs(enemy->position.x - fieldW / 2.0f + enemy->width / 2.0f) > 5.0f)
                    {
                        enemy->moveHorizont(deltaTime, 100.0f);
                    }
                    if (enemy->health <= 0.25f * enemy->healthMax && currentTime - enemy->lastSpellCardTime > 1900)
                    {
                        enemy->defence = 5.0f;
                        enemy->card9(*battleField);
                        enemy->lastSpellCardTime = currentTime;
                    }
                    if (enemy->health <= 0.25f * enemy->healthMax && currentTime - enemy->lastSpellCard5Time > 8000)
                    {
                        enemy->defence = -1.0f;
                        enemy->card5(*battleField);
                        enemy->lastSpellCard5Time = currentTime;
                    }
                    if (enemy->health <= 0)
                    {
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        enemy->phase_left = 1;
                        enemy->health = enemy->healthMax * 0.33f;
                        
                        enemy->ballCount = 33;
                        battleField->player.lives += 1.0f;
                        battleField->player.defence += 0.5f;
                        battleField->player.recoverSpeed += 2.0f;
                        enemy->convertBulletsToScores(*battleField, 100.0f);
                    }
                }
                if (enemy->phase_left == 1)
                {
                    
                    enemy->defence = 0.1f;
                    if(currentTime - enemy->lastSpellCardTime > 7000)
                    {
                        enemy->card7(*battleField);
                        enemy->lastSpellCardTime = currentTime;
                        enemy->lastSpellCard8Time = currentTime;
                    }
                    if (currentTime - enemy->lastSpellCard8Time > 3000)
                    {
                        enemy->card8(*battleField);
                        enemy->lastSpellCard8Time = currentTime;
                    }
                    if (currentTime - enemy->lastSpellCard1Time > 5000)
                    {
                        enemy->card1(*battleField);
                        enemy->lastSpellCard1Time = currentTime;
                    }
                    enemy->bulletRevolve(deltaTime, *battleField);
                    float healthPercentage = enemy->health / enemy->healthMax;
                    int currentInterval = static_cast<int>(healthPercentage / 0.01f);
                    if (currentInterval < enemy->ballCount)
                    {
                        enemy->card6(*battleField);
                        enemy->card1(*battleField);
                        enemy->ballCount = currentInterval;
                    }
                    if (enemy->health <= 0)
                    {
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        battleField->bossGeneratePower(enemy);
                        enemy->phase_left = 0;
                        battleField->bossDead = 1;
                        enemy->convertBulletsToScores(*battleField, 200.0f);
                    }
                }

                
            }
            
            if ((enemy->position.y > fieldH) ||
                (enemy->position.y < 0 - enemy->height) ||
                (enemy->position.x < 0 - enemy->width) ||
                (enemy->position.x > fieldW) )
            {
                delete enemy;
                it = battleField->enemies.erase(it);
            }
            else
            {
                using T = std::decay_t<decltype(enemy)>;
                if constexpr (std::is_same_v<T, enemy1*> || std::is_same_v<T, enemy2*> || std::is_same_v<T, enemy4*>)
                {
                    if (currentTime - enemy->lastShootTime > enemy->FireCooldown && !player.isDead)
                    {
                        battleField->enemyShot(enemy);
                        enemy->lastShootTime = currentTime;
                    }
                }
                if constexpr (std::is_same_v<T, enemy3*>) 
                {
                    if (currentTime - enemy->lastShootTime > enemy->FireCooldown && !player.isDead) 
                    {
                        enemy->isShooting = true;
                        battleField->enemyLaserShot(enemy);
                        enemy->lastShootTime = currentTime;
                    }
                    if (enemy->isShooting && currentTime - enemy->lastShootTime >= (battleField->enemy3LaserTemplate.alarmTime + battleField->enemy3LaserTemplate.duration)) 
                    {
                        enemy->isShooting = false;
                    }
                }
                if (enemy->health <= 0)
                {
                    battleField->enemy1Death(enemy);
                    it = battleField->enemies.erase(it);
                }
                else
                {
                    ++it;
                }
            }
       
        }, *it);
    }
}

void EnemyManager::enemyShot(BattleField *battleField, std::variant<enemy1 *, enemy2 *, enemy3 *, enemy4 *, boss1 *> enemy)
{
    std::visit([battleField](auto&& e) {
        using T = std::decay_t<decltype(e)>;
        if constexpr (std::is_same_v<T, enemy1*>) 
        {
            auto projectile = new enemy1_bullet(battleField->enemy1BulletTemplate);
            projectile->position.x = e->position.x + (e->width - projectile->width) / 2.0f;
            projectile->position.y = e->position.y + e->height;
            projectile->direction = battleField->getDirection(e);
            battleField->enemy1Bullets.push_back(projectile);
        } 
        else if constexpr (std::is_same_v<T, enemy2*>) 
        {
            for(int i = 0; i < 24; i++)
            {
                auto projectile = new enemy2_bullet(battleField->enemy2BulletTemplate);
                projectile->position.x = e->position.x + (e->width - projectile->width) / 2.0f;
                projectile->position.y = e->position.y + e->height / 2.0f;
                projectile->direction = SDL_FPoint{cos(static_cast<float>(i * M_PI / 12.0f)), sin(static_cast<float>(i * M_PI / 12.0f))};
                battleField->enemy1Bullets.push_back(projectile);
            }
        }
        else if constexpr (std::is_same_v<T, enemy4*>) 
        {
            //生成6个子弹，呈锥形分布
            for(int i = 0; i < 6; i++)
            {
                auto projectile = new enemy4_bullet(battleField->enemy4BulletTemplate);
                projectile->position.x = e->position.x + (e->width - projectile->width) / 2.0f;
                projectile->position.y = e->position.y + e->height;
                float angle = (-15.0f + i * 6.0f) * M_PI / 180.0f; // -15度到15度
                SDL_FPoint directionToPlayer = battleField->getDirection(e);
                float rotatedX = directionToPlayer.x * cos(angle) - directionToPlayer.y * sin(angle);
                float rotatedY = directionToPlayer.x * sin(angle) + directionToPlayer.y * cos(angle);
                projectile->direction = SDL_FPoint{rotatedX, rotatedY};
                battleField->enemy1Bullets.push_back(projectile);
            }
        }
        else if constexpr (std::is_same_v<T, boss1*>)
        {
            
        }
    }, enemy);
}

void EnemyManager::updateEnemyBullets(BattleField* battleField, float deltaTime)
{
    for(auto it = battleField->enemy1Bullets.begin(); it != battleField->enemy1Bullets.end(); )
    {
        bool shouldErase = std::visit([battleField, deltaTime](auto&& bullet) {
            bullet->position.x += bullet->speed * bullet->direction.x * deltaTime;
            bullet->position.y += bullet->speed * bullet->direction.y * deltaTime;
            
            if ((bullet->position.y > fieldH) ||
                (bullet->position.y < 0 - bullet->height) ||
                (bullet->position.x < 0 - bullet->width) ||
                (bullet->position.x > fieldW) )
            {
                delete bullet;
                return true;
            }
            
            SDL_Rect bulletRect = 
                {
                    static_cast<int>(bullet->position.x),
                    static_cast<int>(bullet->position.y),
                    bullet->width,
                    bullet->height
                };
            SDL_Rect selfpointBox = 
                {
                    static_cast<int>(battleField->player.position.x + 16),
                    static_cast<int>(battleField->player.position.y + 16),
                    16,
                    16
                };
            int boxCenterX = selfpointBox.x + selfpointBox.w / 2;
            int boxCenterY = selfpointBox.y + selfpointBox.h / 2;
            int bulletCenterX = bulletRect.x + bulletRect.w / 2;
            int bulletCenterY = bulletRect.y + bulletRect.h / 2;
            int distanceX = boxCenterX - bulletCenterX;
            int distanceY = boxCenterY - bulletCenterY;
            int distance = sqrt(distanceX * distanceX + distanceY * distanceY);
            if (distance < (selfpointBox.w + bulletRect.w) / 2 - 6 && !battleField->player.isDead)
            {
                if (bullet->poison)
                {
                    battleField->player.poisonTime = bullet->poisonDuration;
                }
                if (bullet->damage > battleField->player.defence * 1.1f)
                {
                    battleField->player.lives -= (bullet->damage - battleField->player.defence);
                }
                else
                {
                    battleField->player.lives -= bullet->damage * 0.1f;
                }
                battleField->player.power -= (bullet->damage * (battleField->player.power / battleField->player.powerMax) * 5.0f);
                if (bullet->damage > 0)
                {
                    battleField->player.hurting = true;
                    battleField->player.lastHurtTime = SDL_GetTicks();
                }
                delete bullet;
                return true;
            }
            return false;
        }, *it);

        if (shouldErase)
        {
            it = battleField->enemy1Bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (battleField->bossDead)
    {
        for (auto it = battleField->bossRevolveBullets.begin(); it != battleField->bossRevolveBullets.end(); )
        {
            //如果不存在boss1,则子弹按照angle的切线与speed飞行
            bool shouldErase = std::visit([deltaTime](auto&& bullet) 
            {
                bullet->position.x += bullet->speed * cos(bullet->angle + M_PI / 2) * deltaTime;
                bullet->position.y += bullet->speed * sin(bullet->angle + M_PI / 2) * deltaTime;
    
                if ((bullet->position.y > fieldH) ||
                    (bullet->position.y < 0 - bullet->height) ||
                    (bullet->position.x < 0 - bullet->width) ||
                    (bullet->position.x > fieldW) )
                {
                    delete bullet;
                    return true;
                }
                return false;
            }, *it);

            if (shouldErase)
            {
                it = battleField->bossRevolveBullets.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}

void EnemyManager::updateEnemyLasers(BattleField* battleField, float deltaTime)
{
    for (auto it = battleField->enemyLasers.begin(); it != battleField->enemyLasers.end(); )
    {
        auto laser = *it;
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = currentTime - laser->startTime;

        // 检查是否激活（3秒后）
        if (elapsed >= battleField->enemy3LaserTemplate.alarmTime && !laser->isActive)
        {
            laser->isActive = true;
        }

        // 检查是否结束
        if (elapsed >= laser->duration + battleField->enemy3LaserTemplate.alarmTime)
        {
            delete laser;
            it = battleField->enemyLasers.erase(it);
        }
        else
        {
            if (laser->isActive)
            {
                SDL_FPoint playerCenter = {
                    battleField->player.position.x + battleField->player.width / 2.0f,
                    battleField->player.position.y + battleField->player.height / 2.0f
                };

                float A = laser->endPosition.y - laser->startPosition.y;
                float B = laser->startPosition.x - laser->endPosition.x;
                float C = laser->endPosition.x * laser->startPosition.y - laser->startPosition.x * laser->endPosition.y;
                float distance = abs(A * playerCenter.x + B * playerCenter.y + C) / sqrt(A * A + B * B);

                // 距离小于激光宽度的一半，造成伤害
                if (distance < laser->width / 2.0f && !battleField->player.isDead)
                {
                    battleField->player.lives -= laser->damage * deltaTime;
                    battleField->player.power -= (laser->damage * (battleField->player.power / battleField->player.powerMax) * 0.1f);
                }
            }
            ++it;
        }
    }
}
