#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"

#define MAX_ENEMIES 10

void EnemyManagerInit();
void EnemyManagerUpdate();
void EnemyManagerDraw();
void EnemyManagerSpawn();

Enemy* GetEnemies(); 

#endif