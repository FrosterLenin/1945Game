#ifndef PLAYER_H
#define PLAYER_H

#include "rigidbody.h"

typedef struct {
    Texture2D* sprite;
    int frame;
    RigidBody body;
    Vector2 pivot;
    int life;
    int energy;
} Player;

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerUnload();

int GetPlayerLife();
void KeepPlayerInsideScreen();
Rectangle PlayerCollider();

#endif