#include "enemy.h"
#include "game.h"
#include "player.h"
#include "bullets.h"
#include "animation.h"
#include <math.h>

static float enemyFrameTimer = 0;

void EnemyInit(Enemy* enemy) {
    enemy->sprite = &GetTextures()[0];
    enemy->frame = 0;

    // Spawn top of screen
    int positionX = GetRandomValue(100, GetScreenWidth() - 100);
    int positionY = -50;
    enemy->body.position = (Vector2){ positionX, positionY };
    enemy->body.velocity = (Vector2){ 0, 40 }; // falling

    enemy->body.width = 32;
    enemy->body.height = 32;
    enemy->pivot = (Vector2){
        (int)round(enemy->body.position.x),
        (int)round(enemy->body.position.y + (enemy->body.height * .5f))
    };
    enemy->active = true;
    enemy->explosionDamage = 34;
    enemy->bulletDamage = 10;
    enemy->shootInterval = 2;
    enemy->shootTimer = .0f;
}

void EnemyUpdate(Enemy* enemy, float deltaTime) {
    enemyFrameTimer += GetFrameTime();

    enemy->body.position.y += enemy->body.velocity.y * deltaTime;
    enemy->pivot.y += enemy->body.velocity.y * deltaTime;
    int framesPerSecond = 6;
    enemy->frame = (int)(GetTime() * framesPerSecond) % 3;

    if(CheckCollisionRecs(PlayerCollider(), EnemyCollider(enemy))){
        EnemyDestroy(enemy);
        PlayerTakeDamage(enemy->explosionDamage);
    }

    EnemyShoot(enemy);


    // Despawn when off-screen
    if (enemy->body.position.y - enemy->pivot.y > GetPlayableHeight()) {
       enemy->active = false;
    }
}

void EnemyDraw(Enemy* enemy) {
    int offsetY = GetSpriteSheetOffset() + (32 * 6) + 6;
    int offsetX = GetSpriteSheetOffset() + ((enemy->frame + 5) * 32) + enemy->frame + 5;

    Rectangle spriteFramePosition = { offsetX, offsetY, 32, -32 };

    Vector2 currentPosition = (Vector2) {enemy->body.position.x, enemy->body.position.y};
    DrawTextureRec(*enemy->sprite, spriteFramePosition, currentPosition, WHITE);
}

Rectangle EnemyCollider(Enemy* enemy) {
    return (Rectangle){
        enemy->body.position.x,
        enemy->body.position.y,
        enemy->body.width,
        enemy->body.height
    };
}

void EnemyUnload(Enemy* enemy) {
    UnloadTexture(*enemy->sprite);
}

void EnemyDestroy(Enemy* enemy){
    enemy->active = false;
    int offsetY = GetSpriteSheetOffset() + (32 * 5) + 5;
    int offsetX = GetSpriteSheetOffset() + (32 * 2) + 2;
    Vector2 explosionPosition = (Vector2){enemy->pivot.x, enemy->pivot.y};
    StartAnimation(enemy->body.position, (Rectangle){0, 0, 32, 32}, 6, GetTextures()[3], 32, 32, false);
}

void EnemyShoot(Enemy *enemy) {
    enemy->shootTimer += GetFrameTime();
    if (enemy->shootTimer >= enemy->shootInterval) {
        enemy->shootTimer = .0f;
        Bullet *bullet = GetFreeBullet();
        Vector2 bulletPosition = (Vector2){enemy->pivot.x, enemy->body.position.y + enemy->body.height};
        if (bullet) {
            bullet->active = true;
            bullet->body.position = bulletPosition;
            bullet->body.velocity = (Vector2){0, 150};
            bullet->sprite = GetTextures()[4];
            bullet->body.height = 7;
            bullet->body.width = 7;
            bullet->damage = enemy->bulletDamage;
        }
    }
}
