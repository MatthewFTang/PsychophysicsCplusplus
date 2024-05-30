
#include "raylib.h"
#include "raymath.h"
#include "Dot.h"

int main() {

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Test window");
    SetTargetFPS(60);
    int n_dots = 10000;
    Dot dots[n_dots];
    for (int i = 0; i < n_dots; i++) {
        dots[i] = Dot();
    }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < n_dots; i++) {
            dots[i].draw();
        }
        DrawFPS(50, 50);
        EndDrawing();
    };
    CloseWindow();
    return 0;
}
