#pragma once
#include "BattleField.h"

class EnemyManager 
{
public:
    static void updateEnemies(BattleField* battleField, float deltaTime);
    static void enemyShot(BattleField* battleField, std::variant<enemy1*, enemy2*, enemy3*, enemy4*, boss1*> enemy);
    static void updateEnemyBullets(BattleField* battleField, float deltaTime);
    static void updateEnemyLasers(BattleField* battleField, float deltaTime);
};
