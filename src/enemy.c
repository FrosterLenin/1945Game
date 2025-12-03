#include "enemy.h"
#include "game.h"
#include <math.h>

static float enemyFrameTimer = 0;

void EnemyInit(Enemy* enemy) {
    enemy->sprite = &GetTextures()->textures[0];
    enemy->frame = 0;

    // Spawn top of screen
    int positionX = GetRandomValue(100, GetScreenWidth() - 100);
    int positionY = -50;
    enemy->body.position = (Vector2){ positionX, positionY };
    enemy->body.velocity = (Vector2){ 0, 60 }; // falling

    enemy->body.width = 32;
    enemy->body.height = 32;
    enemy->pivot = (Vector2){
        (int)round(enemy->body.width * 0.5f),
        (int)round(enemy->body.height * 0.5f)
    };
    enemy->active = true;
    enemy->explosionDamage = 50;
}

void EnemyUpdate(Enemy* enemy, float deltaTime) {
    enemyFrameTimer += GetFrameTime();

    enemy->body.position.y += enemy->body.velocity.y * deltaTime;
    int framesPerSecond = 6;
    enemy->frame = (int)(GetTime() * framesPerSecond) % 3;

    // Despawn when off-screen
    if (enemy->body.position.y - enemy->pivot.y > GetPlayableHeight()) {
       enemy->active = false;
    }
}

void EnemyDraw(Enemy* enemy) {
    int offsetY = GetSpriteSheetOffset() + (32 * 6) + 6;
    int offsetX = GetSpriteSheetOffset() + ((enemy->frame + 5) * 32) + enemy->frame + 5;

    Rectangle spriteFramePosition = { offsetX, offsetY, 32, -32 };

    Vector2 currentPosition = (Vector2) {enemy->body.position.x - enemy->pivot.x, enemy->body.position.y - enemy->pivot.y};
    DrawTextureRec(*enemy->sprite, spriteFramePosition, currentPosition, WHITE);
}

Rectangle EnemyCollider(Enemy* enemy) {
    Vector2 topLeftOfTheSprite = {
        enemy->body.position.x - enemy->pivot.x,
        enemy->body.position.y - enemy->pivot.y
    };

    return (Rectangle){
        topLeftOfTheSprite.x,
        topLeftOfTheSprite.y,
        enemy->body.width,
        enemy->body.height
    };
}

void EnemyUnload(Enemy* enemy) {
    UnloadTexture(*enemy->sprite);
}