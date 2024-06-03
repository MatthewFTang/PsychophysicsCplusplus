//
// Created by Matthew F Tang on 31/5/2024.
//

#include "Application.h"
#include <raylib.h>
#include <vector>

void Application::Loop() {


    BeginDrawing();
    ClearBackground(backgroundColor);
    if (experiment.experimentState()) {
        experiment.onRender();
    } else {
        DrawTextEx(font, "Experiment complete", Vector2({200, 400}), 48, 0, BLACK);

    }
    DrawFPS(0, 0);
    EndDrawing();
}

void Application::Run() {

    int display = GetCurrentMonitor();

    InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), "Motion judgement");
    ToggleFullscreen();


    SetTargetFPS(60);

    InitExperiment();
    while (!WindowShouldClose()) {
        Loop();
    }
    CloseWindow();

}

void Application::InitExperiment() {
    int n_dots = 1200;
    int aperture = 800;
    int dotRadius = 3;
    int condition_repetitions = 20;

    std::vector<float> coherence_levels = {0.01, 0.02, 0.04, 0.08, 0.16, 0.32, 0.64};
    std::vector<float> speed_levels = {1.0};

    experiment.onInit(n_dots, aperture, dotRadius, WHITE, condition_repetitions, coherence_levels, speed_levels);

}


Application::Application() {
    font = LoadFontEx("../fonts/FiraCodeNerdFontMono-Regular.ttf", 96, nullptr,
                      100);
    InitExperiment();
}



