#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "raylib.h"
#include "animation.h"
#include "enemy_manager.h"
#include <stdio.h>

static Music bgMusic;
static Texture2D* textures;
static Image* images;
static Color backgroundColor;
const int SpriteSheetMargin = 3;
const int SpriteSheetBorder = 1;
const int UiBarHeight = 80;
const int EnergyBarWidth = 127;
const int ScreenWidth = 640;
const int ScreenHeight = 480;

const int* GetSpriteSheetMargin(){
    return &SpriteSheetMargin;
}
const int* GetSpriteSheetBorder(){
    return &SpriteSheetBorder;
}
int GetSpriteSheetOffset(){
    return SpriteSheetBorder + SpriteSheetMargin;
}
Texture2D* GetTextures() {
    return textures;
}
int GetUIHeight() {
    return UiBarHeight;  
}
int GetPlayableHeight() {
    return GetScreenHeight() - GetUIHeight();
}


void LoadAssets() {
    bgMusic = LoadMusicStream("assets/audio/background.mp3");
    bgMusic.looping = true;
    SetMusicVolume(bgMusic, .5f);
    images = malloc(sizeof(Image) * MAX_TEXTURES);
    images[0] = LoadImage("assets/1945_atlas.bmp");
    images[1] = ImageCopy(images[0]);
    images[2] = ImageCopy(images[0]);
    
    int bgPos = SpriteSheetMargin + SpriteSheetMargin + SpriteSheetBorder;
    backgroundColor = GetImageColor(images[0], bgPos, bgPos);
    ImageColorReplace(&images[1], backgroundColor, GRAY);
    // Color spriteSheetBlack = GetImageColor(images[0], 1, 1);
    ImageColorReplace(&images[2], BLACK, GRAY);
    textures = (Texture2D*)(malloc(sizeof(Texture2D) * MAX_TEXTURES));

    textures[0] = LoadTextureFromImage(images[0]);
    textures[1] = LoadTextureFromImage(images[1]);
    textures[2] = LoadTextureFromImage(images[2]);
}
void GameInit() {
    InitWindow(ScreenWidth, ScreenHeight, "1945");
    InitAudioDevice();

    LoadAssets();
    PlayMusicStream(bgMusic);

    PlayerInit();
    EnemyManagerInit();
}
void GameUpdate() {
    UpdateMusicStream(bgMusic);
    PlayerUpdate();
    EnemyManagerUpdate();
}
void GameDraw() {
    BeginDrawing();
    ClearBackground(backgroundColor);

    EnemyManagerDraw(); 
    DrawUI(); // after enenmies so they pass trought the UI
    PlayerDraw();
    UpdateAndDrawAnimations();
    
    EndDrawing();
}


void GameUnload() {
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    UnloadAssets();
    PlayerUnload();
}
void UnloadAssets() {
    for (int i = 0; i < MAX_TEXTURES; i++)
        UnloadTexture(textures[i]);
    for (int i = 0; i < MAX_TEXTURES; i++)
        UnloadImage(images[i]);
    free(images);
    free(textures);
}
void DrawUI(){
    // BOX
    Color UIBackgroundColor = GRAY; 
    DrawRectangle(0, GetScreenHeight() - UiBarHeight, GetScreenWidth(), UiBarHeight, UIBackgroundColor);

    // LOGO
    int offsetY = GetSpriteSheetOffset() + (32 * 12) + 12;
    int offsetX = GetSpriteSheetOffset() + (32 * 21) + 21;
    Rectangle spriteFramePosition = (Rectangle){ offsetX, offsetY, 126, 65 };
    Vector2 position = (Vector2) {GetScreenWidth() - 130, GetScreenHeight() - 72};
    DrawTextureRec(textures[2], spriteFramePosition, position, WHITE);

    // PLAYER LIFE POINTS
    offsetY = GetSpriteSheetOffset() + (32 * 8) + 8;
    offsetX = GetSpriteSheetOffset() + (32 * 6) + 6;
    spriteFramePosition = (Rectangle){ offsetX, offsetY, 32, 32 };
    
    int currentPlayerLife = GetPlayerLife();
    for(int i = 0; i < currentPlayerLife; i++){ 
        
        Rectangle spriteFramePosition = (Rectangle){ offsetX, offsetY, 32, 32 };
        Vector2 position = (Vector2) {11 + (i * 32), GetScreenHeight() - 75};
        DrawTextureRec(textures[1], spriteFramePosition, position, WHITE);
    }

    // PLAYER ENERGY BAR
    offsetY = GetSpriteSheetOffset() + (32 * 6) + 6;
    offsetX = GetSpriteSheetOffset() + (32 * 11) + 11;
    spriteFramePosition = (Rectangle){ offsetX, offsetY, 198, 32 };
    position = (Vector2){10 , GetScreenHeight() - 35};
    DrawTextureRec(textures[2], spriteFramePosition, position, WHITE);

    int barWidth = (GetPlayerEnergy() * EnergyBarWidth) / MAX_ENERGY;

    DrawRectangle(position.x + 7, position.y + 11, barWidth, 10, GREEN);
}