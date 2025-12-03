#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "game.h"

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "1945");
    const char* appDirectory = GetApplicationDirectory();
    ChangeDirectory(appDirectory);

    SetTargetFPS(60);
    GameInit();

    while (!WindowShouldClose()) {
        GameUpdate();
        GameDraw();
    }

    GameUnload();
    CloseWindow();
    return 0;
}