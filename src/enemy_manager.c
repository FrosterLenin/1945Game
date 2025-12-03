#include "enemy_manager.h"
#include "raylib.h"
#include "game.h"
#include "player.h"
#include <stdbool.h>

Enemy enemies[MAX_ENEMIES];
static float spawnTimer = 0;
static float spawnInterval = 2.0f;


Enemy* GetEnemies() {
    return enemies;
}

void EnemyManagerInit() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
    }
}

void EnemyManagerSpawn() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            EnemyInit(&enemies[i]);
            return; // spawn ONE enemy
        }
    }
}

void EnemyManagerUpdate() {
    float deltaTime = GetFrameTime();
    spawnTimer += deltaTime;

    // Spawn a new enemy
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0;
        EnemyManagerSpawn();
    }

    // Update enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;

        EnemyUpdate(&enemies[i], deltaTime);
        if(CheckCollisionRecs(PlayerCollider(), EnemyCollider(&enemies[i])))
            enemies[i].active = false;
    }
}

void EnemyManagerDraw() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;
        EnemyDraw(&enemies[i]);
    }
}
