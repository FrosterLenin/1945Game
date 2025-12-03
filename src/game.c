#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "raylib.h"
#include "enemy_manager.h"

static Textures tex;
static Image altasImage;
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
    altasImage = LoadImage("assets/1945_atlas.png");      // Load as image (CPU)
    ImageFormat(&altasImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    int bgPos = SpriteSheetMargin + SpriteSheetMargin + SpriteSheetBorder;
    backgroundColor = GetImageColor(altasImage, bgPos, bgPos);  // Read pixel color
    tex.count = 1;
    tex.textures = malloc(sizeof(Texture2D) * tex.count);

    tex.textures[0] = LoadTextureFromImage(altasImage);
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
    Rectangle spriteFramePosition = (Rectangle){ offsetX, offsetY, 126, 65 };
    Vector2 position = (Vector2) {GetScreenWidth() - 130, GetScreenHeight() - 72};
    DrawTextureRec(atlas, spriteFramePosition, position, WHITE);

    // PLAYER LIFE POINTS
    int currentPlayerLife = GetPlayerLife();
    for(int i = 0; i < currentPlayerLife; i++){
        int offsetY = GetSpriteSheetOffset() + (32 * 8) + 8;
        int offsetX = GetSpriteSheetOffset() + (32 * 6) + 6;
        Rectangle spriteFramePosition = (Rectangle){ offsetX, offsetY, 32, 32 };
        Vector2 position = (Vector2) {11 + (i * 32), GetScreenHeight() - 75};
        Image cropped = ImageFromImage(altasImage, spriteFramePosition);
        Color colorToReplace = GetImageColor(cropped, 0, 0);

        ImageColorReplace(&cropped, colorToReplace, (Color){0,0,0,0});
        Texture2D textureWithTrasparency = LoadTextureFromImage(cropped);
        UnloadImage(cropped);
        DrawTexture(textureWithTrasparency, position.x, position.y, WHITE);
        UnloadTexture(textureWithTrasparency);
    }

    // PLAYER ENERGY BAR
    offsetY = GetSpriteSheetOffset() + (32 * 6) + 6;
    offsetX = GetSpriteSheetOffset() + (32 * 11) + 11;
    spriteFramePosition = (Rectangle){ offsetX, offsetY, 198, 32 };
    position = (Vector2){10 , GetScreenHeight() - 35};
    DrawTextureRec(atlas, spriteFramePosition, position, WHITE);
    
}