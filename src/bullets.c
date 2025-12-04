#include "bullets.h"

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
            bullets[i].position.x += bullets[i].velocity.x * deltaTime;
            bullets[i].position.y += bullets[i].velocity.y * deltaTime;

            // deactivate if off screen
            if (bullets[i].position.y < 0 || bullets[i].position.y > GetScreenHeight() ||
                bullets[i].position.x < 0 || bullets[i].position.x > GetScreenWidth()) {
                bullets[i].active = false;
            }
        }
    }
}

void DrawBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            // DRAW SPRITE
        }
    }
}