#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
float screenWidth = 1280, screenHeight = 720;
Rectangle canvas = {0, 0, screenWidth * 0.8f, screenHeight};
float controlsWidth = screenWidth - canvas.width, controlsHeight = 20;
float controlsOffset = 40;
float zoom = 1.0f;
Vector2 offset = {0, 0};
int main(void)
{
    InitWindow(screenWidth, screenHeight, "Fractaler");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
}