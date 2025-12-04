#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"
#include "rigidbody.h"
#include <stdbool.h>

#define MAX_BULLETS 64

typedef struct {
    bool active;
    RigidBody body;
    Texture2D sprite;
    int damage;
} Bullet;

void InitBullets();
Bullet* GetFreeBullet();
void UpdateBullets();
void DrawBullets();

#endif // BULLETS_H