#include "player.h"
#include "raylib.h"
#include "game.h"
#include <math.h>
#include "enemy.h"
#include "enemy_manager.h"

Player player;
static float frameTimer = 0;

void PlayerInit() {
    player.sprite = &GetTextures()->textures[0];
    player.frame = 0;

    float positionX = GetScreenWidth() * .5f;
    float positionY = GetScreenHeight() * .75f;
    
    player.body.position = (Vector2){positionX, positionY};
    player.body.velocity = (Vector2){ 0, 0 };
    player.body.width = 65;
    player.body.height = 65;
    player.pivot = (Vector2){(int)round(player.body.width * .5f), (int)round(player.body.height *.5f)};
    player.life = 3;
    player.energy = 100;
}

int GetPlayerLife(){
    return player.life;
}

void PlayerUpdate() {
    frameTimer += GetFrameTime();

    // Example movement
    player.body.velocity.x = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT)) * 100;
    player.body.velocity.y = (IsKeyDown(KEY_DOWN)  - IsKeyDown(KEY_UP)) * 100;

    // Apply velocity
    player.body.position.x += player.body.velocity.x * GetFrameTime();
    player.body.position.y += player.body.velocity.y * GetFrameTime();

    KeepPlayerInsideScreen();
    
    // Update sprite frame
    int framesPerSecond = 6;
    player.frame = (int)(GetTime() * framesPerSecond) % 3;

    //TODO COLLISSION
    Enemy* enemies = GetEnemies();
    for(int i = 0; i < MAX_ENEMIES; i++){
        if (!enemies[i].active) continue;
        if(CheckCollisionRecs(PlayerCollider(), EnemyCollider(&enemies[i]))){
            player.energy-= enemies[i].explosionDamage;
            if(player.life <= 0)
                player.life--;
        }
    }
    
}

void PlayerDraw() {
    int offsetY = GetSpriteSheetOffset() + (32 * 12) + 12;
    int offsetX = GetSpriteSheetOffset() + (player.frame * 65) + player.frame; // 4 + 65 + 1
    Rectangle spriteFramePosition = { offsetX, offsetY, 65, 65 };
    Vector2 currentPosition = (Vector2) {player.body.position.x - player.pivot.x, player.body.position.y - player.pivot.y};
    DrawTextureRec(*player.sprite, spriteFramePosition, currentPosition, WHITE);
}

Rectangle PlayerCollider() {
    Vector2 topLeftOfTheSprite = {
        player.body.position.x - player.pivot.x,
        player.body.position.y - player.pivot.y
    };

    return (Rectangle){
        topLeftOfTheSprite.x,
        topLeftOfTheSprite.y,
        player.body.width,
        player.body.height
    };
}

void KeepPlayerInsideScreen() {
    Rectangle collider = PlayerCollider();

    float left = collider.x;
    float right = collider.x - collider.width;
    float top = collider.y;
    float bottom = collider.y - collider.height;

    // Left wall
    if (left < 0)
        player.body.position.x = player.pivot.x;

    // Right wall
    if (right > GetScreenWidth())
        player.body.position.x = GetScreenWidth() - player.pivot.x;

    // Top wall
    if (collider.y < 0)
        player.body.position.y = player.pivot.y;

    // Bottom wall
    if (collider.y + collider.height > GetPlayableHeight())
        player.body.position.y = GetPlayableHeight() - player.pivot.y;
}

void PlayerUnload() {
    UnloadTexture(*player.sprite);
}