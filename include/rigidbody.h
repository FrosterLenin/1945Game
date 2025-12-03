#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
} RigidBody;

#endif
