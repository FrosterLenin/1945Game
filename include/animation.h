#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"
#include <stdbool.h>

#define MAX_ANIMATIONS 32

typedef struct {
    Vector2 position;
    int currentFrame;
    float frameTimer;
    Rectangle firstSprite;
    int fps;
    Texture2D spriteSheet; 
    int frameWidth; 
    int frameHeight;
    bool fromSpriteSheet;
} Animation;

// // Global array of animations
// extern Animation animations[MAX_ANIMATIONS];
// extern int animationCount;

void StartAnimation(Vector2 position, Rectangle firstSprite, int fps, Texture2D spriteSheet, int frameWidth, int frameHeight, bool fromSpriteSheet);
void UpdateAndDrawAnimations();

#endif // ANIMATION_H