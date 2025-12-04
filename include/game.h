#ifndef GAME_H
#define GAME_H
#include "raylib.h"


#define MAX_TEXTURES 3

Texture2D* GetTextures();
void LoadAssets();
void UnloadAssets();

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
void ImageColorReplaceTolerance(Image image, Color target, int tolerance);

#endif