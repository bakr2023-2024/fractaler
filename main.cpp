#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "fractaler.hpp"
float screenWidth = 1280, screenHeight = 720;
Rectangle canvas = {0, 0, screenWidth * 0.8f, screenHeight};

float controlsWidth = screenWidth - canvas.width, controlsHeight = 20;
float yGap = 10;
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
void createStrInput(Rectangle &pos, const char *label, char *input, bool &editMode, int size)
{
    pos.x = canvas.width;
    pos.width = controlsOffset;
    GuiLabel(pos, label);
    pos.x = canvas.width + controlsOffset;
    pos.width = controlsWidth - controlsOffset;
    if (GuiTextBox(pos, input, size, editMode))
        editMode = !editMode;
    pos.y += controlsHeight + yGap;
}
void createDoubleInput(Rectangle &pos, const char *label, char *input, double &val, bool &editMode)
{
    createStrInput(pos, label, input, editMode, 16);
    if (!editMode)
        val = atof(input);
}
int main(void)
{
    const char *algs = "Multibrot;Julia;Burning Ship;Newton;Nova;Sin;Sinh;Newton Cosh;Collatz;Septagon;Magnet 1;Magnet 2;Cactus;Lambda;Barnsley Tree;Rings;Roger Rational";
    char pInput[16] = "0";
    char qInput[16] = "0";
    char cxInput[16] = "0";
    char cyInput[16] = "0";
    char λInput[16] = "0";
    char polyInput[100] = "";
    std::string lastPolyInput = "";
    bool needsUpdate = false;
    bool editPInputMode = false;
    bool editQInputMode = false;
    bool editCxInputMode = false;
    bool editCyInputMode = false;
    bool editλInputMode=false;
    bool editPolyInputMode = false;
    bool editAlgsMode = false;
    bool editMaxItrsMode = false;
    Rectangle controlsPos = {canvas.width + controlsOffset, 0, controlsWidth - controlsOffset, controlsHeight};
    int maxIterations = 100;
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
        controlsPos.y = controlsHeight + yGap;
        if (editAlgsMode)
            GuiLock();

        createDoubleInput(controlsPos, "P", pInput, params.P, editPInputMode);
        createDoubleInput(controlsPos, "Q", qInput, params.Q, editQInputMode);
        createDoubleInput(controlsPos, "cx", cxInput, params.cx, editCxInputMode);
        createDoubleInput(controlsPos, "cy", cyInput, params.cy, editCyInputMode);
        createDoubleInput(controlsPos, "delta", λInput, params.λ, editλInputMode);
        createStrInput(controlsPos, "polynomial", polyInput, editPolyInputMode, 100);
        if (!editPolyInputMode)
            params.poly.str = polyInput;
        if (GuiSpinner(controlsPos, "iterations", &maxIterations, 1, 1000, editMaxItrsMode))
            editMaxItrsMode = !editMaxItrsMode;
        if (!editMaxItrsMode)
            maxItrs = maxIterations;
        controlsPos.y += controlsHeight + yGap;

        if (GuiButton(controlsPos, "Start"))
        {
            setPlotter(algChoice);
            reset();
            needsUpdate = true;
        }
        controlsPos.y += controlsHeight + yGap;

        if (editAlgsMode)
            GuiUnlock();
        controlsPos.y = 0;
        if (GuiDropdownBox(controlsPos, algs, &algChoice, editAlgsMode))
        {
            editAlgsMode = !editAlgsMode;
            EndDrawing();
            continue;
        }
        EndDrawing();
    }
}