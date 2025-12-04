#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_BULLETS 64

typedef struct {
    Vector2 position;
    Vector2 velocity;
    bool active;
} Bullet;

void InitBullets();
Bullet* GetFreeBullet();
void UpdateBullets();
void DrawBullets();


#endif // BULLETS_H