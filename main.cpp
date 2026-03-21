#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "fractaler.hpp"
float screenWidth = 1280, screenHeight = 720;
Rectangle canvas = {0, 0, screenWidth * 0.8f, screenHeight};

float controlsWidth = screenWidth - canvas.width, controlsHeight = 20;
float controlsOffset = 50;
double minX = -2.5, minY = -1.5, maxX = 1.5, maxY = 1.5;
void drawFractal(int *pixels)
{
    double dx = (maxX - minX) / canvas.width;
    double dy = (maxY - minY) / canvas.height;
#pragma omp parallel for schedule(dynamic, 8)
    for (int y = 0; y < (int)canvas.height; y++)
    {
        for (int x = 0; x < (int)canvas.width; x++)
        {
            double mapX = minX + x * dx;
            double mapY = maxY - y * dy;
            pixels[y * (int)canvas.width + x] = plot(Complex{mapX, mapY});
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
void createDoubleInput(Rectangle &pos, const char *label, char *input, double &val, bool &editMode)
{
    pos.x = canvas.width;
    pos.width = controlsOffset;
    GuiLabel(pos, label);
    pos.x = canvas.width + controlsOffset;
    pos.width = controlsWidth - controlsOffset;
    if (GuiTextBox(pos, input, 16, editMode))
        editMode = !editMode;
    if (!editMode)
        val = atof(input);
    pos.y += controlsHeight;
}
int main(void)
{
    char pInput[16] = "0";
    char qInput[16] = "0";
    char cxInput[16] = "0";
    char cyInput[16] = "0";
    bool needsUpdate = false;
    bool editPInputMode = false;
    bool editQInputMode = false;
    bool editCxInputMode = false;
    bool editCyInputMode = false;
    bool editAlgsMode = false;
    bool editMaxItrsMode = false;
    Rectangle controlsPos = {canvas.width + controlsOffset, 0, controlsWidth - controlsOffset, controlsHeight};
    int maxIterations = 100;
    const char *algs = "Multibrot;Julia";
    int algChoice = 0;
    InitWindow(screenWidth, screenHeight, "Fractaler");
    Image img = GenImageColor(canvas.width, canvas.height, BLACK);
    int *pixels = (int *)img.data;
    Texture2D tex = LoadTextureFromImage(img);
    while (!WindowShouldClose())
    {
        float y = controlsHeight;
        BeginDrawing();
        ClearBackground(BLACK);
        if (needsUpdate)
        {
            if (plot != nullptr)
            {
                drawFractal(pixels);
                UpdateTexture(tex, pixels);
            }
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
        controlsPos.y = controlsHeight;

        createDoubleInput(controlsPos, "P", pInput, params.P, editPInputMode);
        createDoubleInput(controlsPos, "Q", qInput, params.Q, editQInputMode);
        createDoubleInput(controlsPos, "cx", cxInput, params.cx, editCxInputMode);
        createDoubleInput(controlsPos, "cy", cyInput, params.cy, editCyInputMode);

        if (GuiSpinner(controlsPos, "iterations", &maxIterations, 1, 1000, editMaxItrsMode))
            editMaxItrsMode = !editMaxItrsMode;
        if (!editMaxItrsMode)
            maxItrs = maxIterations;
        controlsPos.y += controlsHeight;

        if (GuiButton(controlsPos, "Start"))
        {
            setPlotter((Algs)algChoice);
            reset();
            needsUpdate = true;
        }
        controlsPos.y += controlsHeight;

        controlsPos.y = 0;
        if (editAlgsMode)
            GuiUnlock();
        if (GuiDropdownBox(controlsPos, algs, &algChoice, editAlgsMode))
            editAlgsMode = !editAlgsMode;
        EndDrawing();
    }
}