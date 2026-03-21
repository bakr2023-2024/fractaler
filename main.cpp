#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "fractaler.hpp"
float screenWidth = 1280, screenHeight = 720;
Rectangle canvas = {0, 0, screenWidth * 0.8f, screenHeight};

float controlsWidth = screenWidth - canvas.width, controlsHeight = 20;
float controlsOffset = 40;
double minX = -2.5, minY = -1.5, maxX = 1.5, maxY = 1.5;
void drawFractal(const Fractaler &fractaler, int *pixels)
{
#pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < (int)canvas.height; y++)
    {
        for (int x = 0; x < (int)canvas.width; x++)
        {
            double mapX = minX + ((double)x / canvas.width) * (maxX - minX);
            double mapY = maxY - ((double)y / canvas.height) * (maxY - minY);
            pixels[y * (int)canvas.width + x] = fractaler.plot(Complex{mapX, mapY});
        }
    }
}
void zoom(bool in = true)
{
    Vector2 mouse = GetMousePosition();
    if (mouse.x < canvas.width)
    {
        double factor = in ? 0.25 : 1.0;
        double mouseX = minX + (mouse.x / canvas.width) * (maxX - minX);
        double mouseY = maxY - (mouse.y / canvas.height) * (maxY - minY);
        double rangeX = (maxX - minX) * factor;
        double rangeY = (maxY - minY) * factor;
        minX = mouseX - rangeX;
        maxX = mouseX + rangeX;
        minY = mouseY - rangeY;
        maxY = mouseY + rangeY;
    }
}
void reset()
{
    minX = -2.5;
    maxX = 1.5;
    minY = -1.5;
    maxY = 1.5;
}
int main(void)
{
    bool needsUpdate = false;
    bool editAlgsMode = false;
    const char *algs = "Mandelbrot";
    int algChoice = 0;
    InitWindow(screenWidth, screenHeight, "Fractaler");
    Image img = GenImageColor(canvas.width, canvas.height, BLACK);
    int *pixels = (int *)img.data;
    Texture2D tex = LoadTextureFromImage(img);
    Fractaler fractaler{canvas.width, canvas.height, 200};
    fractaler.setPlotter((Algs)algChoice);
    while (!WindowShouldClose())
    {
        float y = 0;
        BeginDrawing();
        ClearBackground(BLACK);
        if (needsUpdate)
        {
            drawFractal(fractaler, pixels);
            UpdateTexture(tex, pixels);
            needsUpdate = false;
        }
        DrawTexture(tex, 0, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            zoom();
            needsUpdate = true;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            zoom(false);
            needsUpdate = true;
        }
        if (IsKeyPressed(KEY_R))
        {
            reset();
            needsUpdate = true;
        }
        if (editAlgsMode)
            GuiLock();
        if (GuiButton({canvas.width + controlsOffset, y + controlsHeight, controlsWidth - controlsOffset, controlsHeight}, "Start"))
        {
            fractaler.setPlotter((Algs)algChoice);
            needsUpdate = true;
        }
        if (GuiDropdownBox({canvas.width + controlsOffset, y, controlsWidth - controlsOffset, controlsHeight}, algs, &algChoice, editAlgsMode))
            editAlgsMode = !editAlgsMode;
        if (editAlgsMode)
            GuiUnlock();
        EndDrawing();
    }
}