#include <stdio.h>

#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Hot Reloading");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
