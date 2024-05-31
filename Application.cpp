//
// Created by Matthew F Tang on 31/5/2024.
//

#include "Application.h"
#include <raylib.h>
#include "responseScreen.h"

void Application::Loop() {


    BeginDrawing();
    ClearBackground(backgroundColor);

    field.run();
    DrawFPS(0, 0);
    EndDrawing();
    frameCount++;
}

void Application::Run() {

    int display = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), "Motion judgement");

//    MaximizeWindow();
    ToggleFullscreen();
    SetTargetFPS(60);

    InitExperiment();
    while (!WindowShouldClose()) {
        Loop();
    }
    CloseWindow();

}

void Application::InitExperiment() {
    int n_dots = 400;
    int aperture = 800;
    responseScreen response(aperture, RED, 3.0f);
    field.make(n_dots, .5, aperture, PI / 4, 2, 2);
    
}
