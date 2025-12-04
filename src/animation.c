#include "animation.h"

Animation animations[MAX_ANIMATIONS];
int animationCount = 0;

void StartAnimation(Vector2 position, Rectangle firstSprite, int fps, Texture2D spriteSheet, int frameWidth, int frameHeight) {
    if (animationCount < MAX_ANIMATIONS) {
        animations[animationCount].position = position;
        animations[animationCount].currentFrame = 0;
        animations[animationCount].frameTimer = .0f;
        animations[animationCount].firstSprite = firstSprite;
        animations[animationCount].fps = fps;
        animations[animationCount].spriteSheet = spriteSheet;
        animations[animationCount].frameWidth = frameWidth;
        animations[animationCount].frameHeight = frameHeight;
        animationCount++;
    }
}

void UpdateAndDrawAnimations() {
    for (int i = 0; i < animationCount; ) {
        Animation *currentAnimation = &animations[i];

        currentAnimation->frameTimer += GetFrameTime();
        if (currentAnimation->frameTimer >= 1.0f / currentAnimation->fps) {
            currentAnimation->currentFrame++;
            currentAnimation->frameTimer = .0f;
        }

        // Draw current frame
        if (currentAnimation->currentFrame < 6) {
            Rectangle src = (Rectangle){
                currentAnimation->firstSprite.x + ((currentAnimation->frameWidth * currentAnimation->currentFrame) + currentAnimation->currentFrame),
                currentAnimation->firstSprite.y,
                currentAnimation->frameWidth,
                currentAnimation->frameHeight
            };
            DrawTextureRec(currentAnimation->spriteSheet, src, currentAnimation->position, WHITE);
            i++; // next animation
        } 
        else {
            // Remove finished animation (swap with last)
            animations[i] = animations[animationCount - 1];
            animationCount--;
        }
    }
}