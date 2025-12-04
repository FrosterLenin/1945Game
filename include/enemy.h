#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include "rigidbody.h"
#include "raylib.h"

typedef struct Enemy {
    Texture2D* sprite; 
    int frame;
    Vector2 pivot;
    RigidBody body;
    bool active;
    int explosionDamage;
    float shootTimer;
    float shootInterval;
} Enemy;

extern Enemy enemy;

void EnemyInit(Enemy* enemy);
void EnemyUpdate(Enemy* enemy, float deltaTime);
void EnemyDraw(Enemy* enemy);
Rectangle EnemyCollider(Enemy* enemy);
void EnemyUnload(Enemy* enemy);

void EnemyDestroy(Enemy* enemy);
void EnemyShoot(Enemy *enemy);

#endif