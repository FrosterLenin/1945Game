#ifndef GAME_H
#define GAME_H
#include "raylib.h"

typedef struct {
    Texture2D* textures;
    int count;
} Textures;

Textures* GetTextures();
void LoadTextures();
void UnloadTextures();

const int* GetSpriteSheetMargin();
const int* GetSpriteSheetBorder();
int GetSpriteSheetOffset();

void GameInit();
void GameUpdate();
void GameDraw();
void GameUnload();

void DrawUI();
int GetUIHeight();
int GetPlayableHeight();

#endif