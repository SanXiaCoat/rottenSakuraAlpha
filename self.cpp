#include "self.h"
#include "enermy.h"
#include "game.h"
#include <cmath>
#include <random>


// 计算两点间距离
float getMeleeDistance(const SDL_FPoint& a, const SDL_FPoint& b) 
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Player::combat(std::list<std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*>>& enemies) 
{
    // 计算玩家中心位置
    SDL_FPoint playerCenter = 
    {
        position.x + width / 2.0f,
        position.y + height / 2.0f
    };
   
    for (auto it = enemies.begin(); it != enemies.end();) 
    {
        std::visit([this, &playerCenter](auto&& enemy) {
            SDL_FPoint enemyCenter = 
            {
                enemy->position.x + enemy->width / 2.0f,
                enemy->position.y + enemy->height / 2.0f
            };

            if (getMeleeDistance(playerCenter, enemyCenter) <= meleeRadius * (1 + power / powerMax) && playerCenter.y + 24.0f >= enemyCenter.y) 
            {
                enemy->health -= meleeDamage * (1 + 2 * power / powerMax);
            }
        }, *it);
        ++it;
    }
}

void Player::skill1(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>>& enemyBullets)
{
    SDL_FPoint playerCenter = 
    {
        position.x + width / 2.0f,
        position.y + height / 2.0f
    };

    for (auto& bullet : enemyBullets) 
    {
        std::visit([this, &playerCenter](auto&& bullet) {
            if (bullet->hasBeenSlowedBySkill2)
            {
                return;
            }

            SDL_FPoint bulletCenter = 
            {
                bullet->position.x + bullet->width / 2.0f,
                bullet->position.y + bullet->height / 2.0f
            };

            float distance = getMeleeDistance(playerCenter, bulletCenter);

            if (distance <= meleeRadius * 1.5f && bullet->hasBeenSlowed == false) 
            {
                if (power < powerMax * 0.5f)
                    bullet->speed = static_cast<int>(bullet->speed * (1.0f - power / powerMax));
                else
                    bullet->speed = static_cast<int>(bullet->speed * 0.5f);

                bullet->hasBeenSlowed = true;
                bullet->texture = bullet->textureSlowed;
            }
            else
            {
                bullet->speed = bullet->speed_;
                bullet->texture = bullet->textureAlt;
                bullet->hasBeenSlowed = false;
            }
        }, bullet);
    }
}

void Player::skill2(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> &enemyBullets, std::list<std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*>>& enemies)
{
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 1);
    SDL_FPoint playerCenter = 
    {
        position.x + width / 2.0f,
        position.y + height / 2.0f
    };
    for(auto it = enemyBullets.begin(); it != enemyBullets.end(); )
    {
        bool shouldErase = std::visit([&dis, &gen](auto&& bullet) {
            if (dis(gen) == 0)
            {
                delete bullet;
                return true;
            }
            else
            {
                if (bullet->hasBeenSlowedBySkill2 == false)
                {
                    bullet->speed /= 4;
                    bullet->texture = bullet->textureFrozen;
                }            
                bullet->hasBeenSlowedBySkill2 = true;
                return false;
            }
        }, *it);

        if (shouldErase)
        {
            it = enemyBullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for(auto enemy : enemies)
    {
        std::visit([this, &playerCenter](auto&& enemy) {
            SDL_FPoint enemyCenter = 
            {
                enemy->position.x + enemy->width / 2.0f,
                enemy->position.y + enemy->height / 2.0f
            };
            if (getMeleeDistance(playerCenter, enemyCenter) <= meleeRadius * 4 )
            {
                enemy->health -= 100 * (1 + power / powerMax) * meleeDamage / 1.5f;
            }
        }, enemy);
    }
}

void Player::skill2Render()
{
    SDL_FPoint playerCenter = 
    {
        position.x + width / 2.0f,
        position.y + height / 2.0f
    };
    SDL_Rect skill2Rect = {
        static_cast<int>(playerCenter.x - meleeRadius * 4), 
        static_cast<int>(playerCenter.y - meleeRadius * 4), 
        static_cast<int>(meleeRadius * 8),
        static_cast<int>(meleeRadius * 8)
    };
    SDL_Renderer* renderer = game::getInstance().getRenderer();
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsed = currentTime - x_signStartTime;
    if (elapsed < 200) 
    {
        SDL_RenderCopy(renderer, skill2Texture, NULL, &skill2Rect);
    }
    else
    {
        renderSkill2Needed = false;
    }
    
}

void Player::skill3(std::list<std::variant<enemy1_bullet*, enemy2_bullet*, enemy4_bullet*, boss1_bullet*>> &enemyBullets,std::list<self_bullet *> &selfBullets) 
{
    //将所有地方弹幕转化为自机弹幕并继承伤害和速度绝对值但是速度相反
    for(auto it = enemyBullets.begin(); it != enemyBullets.end(); )
    {
        self_bullet* newBullet = new self_bullet();
        std::visit([this, &newBullet](auto&& bullet) {
            newBullet->position = bullet->position;
            newBullet->speed = bullet->speed * bullet->direction.y *2.0f;
            newBullet->speedX = -bullet->speed * bullet->direction.x *2.0f;
            newBullet->damage = bullet->damage * (1 + power / powerMax);
            newBullet->width = bullet->width * 1.5f;
            newBullet->height = bullet->height * 1.5f;
            newBullet->texture = bullet->texture;
            delete bullet;
        },*it);
        selfBullets.push_back(newBullet);
        it = enemyBullets.erase(it);
    }   
}

void Player::combatRender() {
    SDL_FPoint playerCenter = {
        position.x + width / 2.0f,
        position.y + height / 2.0f
    };
    SDL_Rect combatRect = { 
        static_cast<int>(playerCenter.x - meleeRadius), 
        static_cast<int>(playerCenter.y - meleeRadius), 
        static_cast<int>(meleeRadius * 2),
        static_cast<int>(meleeRadius) 
    };
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsed = currentTime - space_signStartTime;
    SDL_Renderer* renderer = game::getInstance().getRenderer();

    if (elapsed < 50) 
    {
        SDL_RenderCopy(renderer, combatTexture1, NULL, &combatRect);
    } else if (elapsed < 100) 
    {
        SDL_RenderCopy(renderer, combatTexture2, NULL, &combatRect);
    } else if (elapsed < 150) 
    {
        SDL_RenderCopy(renderer, combatTexture3, NULL, &combatRect);
    } else if (elapsed < 200) 
    { 
        SDL_RenderCopy(renderer, combatTexture4, NULL, &combatRect);
    } else 
    {
        renderCombatNeeded = false;  
    }
}