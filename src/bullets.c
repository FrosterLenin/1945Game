#include "bullets.h"
#include "player.h"
#include "game.h"
Bullet bullets[MAX_BULLETS];

void InitBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = false;
    }
}

Bullet* GetFreeBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            return &bullets[i];
        }
    }
    return 0; // no free bullet available
}

void UpdateBullets() {
    float deltaTime = GetFrameTime();
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            // bullets[i].body.position.x += bullets[i].body.velocity.x * deltaTime;
            bullets[i].body.position.y += bullets[i].body.velocity.y * deltaTime;

            if (CheckCollisionCircleRec(bullets[i].body.position, bullets[i].body.width * .5f, PlayerCollider())) {
                PlayerTakeDamage(bullets[i].damage);
                bullets[i].active = false; 
            }
            // deactivate if off screen
            if (bullets[i].body.position.y < 0 || bullets[i].body.position.y > GetPlayableHeight()) 
                bullets[i].active = false;
        }
    }
}

void DrawBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            // TraceLog(LOG_INFO, "DRAW BULLET");
            DrawTexture(bullets[i].sprite, bullets[i].body.position.x, bullets[i].body.position.y, WHITE);
        }
    }
}
