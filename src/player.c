#include "player.h"
#include "raylib.h"
#include "bullets.h"
#include "game.h"
#include <math.h>
#include "enemy.h"
#include "enemy_manager.h"

Player player;
static float frameTimer = 0;

void PlayerInit() {
    player.sprite = &GetTextures()[0];
    player.frame = 0;

    float positionX = GetScreenWidth() * .5f;
    float positionY = GetScreenHeight() * .5f;
    
    player.body.position = (Vector2){positionX, positionY};
    player.body.velocity = (Vector2){ 0, 0 };
    player.body.width = 65;
    player.body.height = 65;
    player.pivot = (Vector2){positionX + ((int)round(player.body.width * .5f)), positionY + ((int)round(player.body.height *.5f))};
    player.life = 3;
    player.energy = MAX_ENERGY;
    player.bulletDamage = 20;
    player.shootInterval = 2;
    player.shootTimer = .0f;
}

int GetPlayerLife(){
    return player.life;
}
int GetPlayerEnergy(){
    return player.energy;
}

void PlayerUpdate() {
    frameTimer += GetFrameTime();

    // Example movement
    player.body.velocity.x = (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT)) * 100;
    player.body.velocity.y = (IsKeyDown(KEY_DOWN)  - IsKeyDown(KEY_UP)) * 100;

    // Apply velocity
    float newX = player.body.velocity.x * GetFrameTime();
    player.body.position.x += newX;
    player.pivot.x += newX;
    float newY = player.body.velocity.y * GetFrameTime();
    player.body.position.y += newY;
    player.pivot.y += newY;

    PlayerShoot();

    KeepPlayerInsideScreen();
    
    // Update sprite frame
    int framesPerSecond = 6;
    player.frame = (int)(GetTime() * framesPerSecond) % 3;
    
}

void PlayerDraw() {
    int offsetY = GetSpriteSheetOffset() + (32 * 12) + 12;
    int offsetX = GetSpriteSheetOffset() + (player.frame * 65) + player.frame; // 4 + 65 + 1
    Rectangle spriteFramePosition = { offsetX, offsetY, 65, 65 };
    Vector2 currentPosition = (Vector2) {player.body.position.x, player.body.position.y};
    DrawTextureRec(*player.sprite, spriteFramePosition, currentPosition, WHITE);
}

Rectangle PlayerCollider() {
    return (Rectangle){
        player.body.position.x,
        player.body.position.y,
        player.body.width,
        player.body.height
    };
}

void KeepPlayerInsideScreen() {
    Rectangle collider = PlayerCollider();

    float left = collider.x;
    float right = collider.x + collider.width;
    float top = collider.y;
    float bottom = collider.y + collider.height;

    // Left wall
    if (left < 0)
        player.body.position.x = 0;

    // Right wall
    if (right > GetScreenWidth())
        player.body.position.x = GetScreenWidth() - collider.width;

    // Top wall
    if (top < 0)
        player.body.position.y = 0;

    // Bottom wall
    if (bottom > GetPlayableHeight())
        player.body.position.y = GetPlayableHeight() - collider.height;
}

void PlayerTakeDamage(int damage){
    player.energy -= damage;
    if(player.energy <= 0){
        player.energy = MAX_ENERGY;
        player.life--;
    }
}

void PlayerShoot(){
    player.shootTimer += GetFrameTime();
    if(IsKeyDown(KEY_SPACE) && player.shootTimer >= player.shootInterval){
        player.shootTimer = .0f;
        Bullet *bullet = GetFreeBullet();
        Rectangle collider = PlayerCollider();
        Vector2 bulletPosition = (Vector2){player.pivot.x, player.pivot.y};
        if (bullet) {
            bullet->owner = ENTITY_PLAYER;
            bullet->active = true;
            bullet->body.position = bulletPosition;
            bullet->body.velocity = (Vector2){0, -150};
            bullet->sprite = GetTextures()[4];
            bullet->body.height = 7;
            bullet->body.width = 7;
            bullet->damage = player.bulletDamage;
        }
    }
}

void PlayerUnload() {
    UnloadTexture(*player.sprite);
}