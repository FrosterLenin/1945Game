#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "raylib.h"
#include "enemy_manager.h"

static Textures tex;  // singleton
static Color backgroundColor;
const int SpriteSheetMargin = 3;
const int SpriteSheetBorder = 1;
const int UiBarHeight = 80;


const int* GetSpriteSheetMargin(){
    return &SpriteSheetMargin;
}
const int* GetSpriteSheetBorder(){
    return &SpriteSheetBorder;
}
int GetSpriteSheetOffset(){
    return SpriteSheetBorder + SpriteSheetMargin;
}
Textures* GetTextures() {
    return &tex;
}
int GetUIHeight() {
    return UiBarHeight;  
}
int GetPlayableHeight() {
    return GetScreenHeight() - GetUIHeight();
}


void LoadTextures() {
    Image image = LoadImage("assets/1945_atlas.bmp");      // Load as image (CPU)
    int bgPos = SpriteSheetMargin + SpriteSheetMargin + SpriteSheetBorder;
    backgroundColor = GetImageColor(image, bgPos, bgPos);  // Read pixel color
    tex.count = 1;
    tex.textures = malloc(sizeof(Texture2D) * tex.count);

    tex.textures[0] = LoadTextureFromImage(image);
}
void GameInit() {
    LoadTextures();
    PlayerInit();
    EnemyManagerInit();
}
void GameUpdate() {
    PlayerUpdate();
    EnemyManagerUpdate();
}
void GameDraw() {
    BeginDrawing();
    ClearBackground(backgroundColor);

    EnemyManagerDraw(); 
    DrawUI(); // after enenmies so they pass trought the UI
    PlayerDraw();

    EndDrawing();
}


void GameUnload() {
    UnloadTextures();
    PlayerUnload();
}
void UnloadTextures() {
    for (int i = 0; i < tex.count; i++)
        UnloadTexture(tex.textures[i]);

    free(tex.textures);
}
void DrawUI(){
    // BOX
    DrawRectangle(0, GetScreenHeight() - UiBarHeight, GetScreenWidth(), UiBarHeight, GRAY);

    Texture2D atlas = tex.textures[0];
    // LOGO
    int offsetY = GetSpriteSheetOffset() + (32 * 12) + 12;
    int offsetX = GetSpriteSheetOffset() + (32 * 21) + 21;
    Rectangle spriteFramePosition = { offsetX, offsetY, 126, 65 };
    Vector2 position = (Vector2) {GetScreenWidth() - 130, GetScreenHeight() - 72};
    DrawTextureRec(atlas, spriteFramePosition, position, WHITE);

    // PLAYER LIFE POINTS
    int currentPlayerLife = GetPlayerLife();
    for(int i = 0; i < currentPlayerLife; i++){
        int offsetY = GetSpriteSheetOffset() + (32 * 8) + 8;
        int offsetX = GetSpriteSheetOffset() + (32 * 6) + 6;
        Rectangle spriteFramePosition = { offsetX, offsetY, 32, 32 };
        Vector2 position = (Vector2) {10 +( i * 32), GetScreenHeight() - 60};
        DrawTextureRec(atlas, spriteFramePosition, position, WHITE);
    }
    
}