#ifndef PLAYER_H
#define PLAYER_H

#include "rigidbody.h"
#define MAX_ENERGY 100

typedef struct {
    Texture2D* sprite;
    int frame;
    RigidBody body;
    Vector2 pivot;
    int life;
    int energy;
    int bulletDamage;
    float shootTimer;
    float shootInterval;
} Player;

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerUnload();

int GetPlayerLife();
int GetPlayerEnergy();

void KeepPlayerInsideScreen();
Rectangle PlayerCollider();
void PlayerTakeDamage(int damage);
void PlayerShoot();

#endif