//
// Created by Matthew F Tang on 31/5/2024.
//

#include "../include/Application.h"

#include <raylib.h>
Application::Application() = default;

void Application::Loop() {

    BeginDrawing();
    ClearBackground(backgroundColor);
    experiment.run();
    DrawFPS(0, 0);
    EndDrawing();
}
void Application::Run() {

    int display = GetCurrentMonitor();

    InitWindow(GetMonitorWidth(display), GetMonitorHeight(display),
               "Motion judgement");
    font = LoadFontEx("fonts/FiraCodeNerdFontMono-Regular.ttf", 48, nullptr, 0);
    SetTargetFPS(60);
    InitExperiment();

    while (!WindowShouldClose()) {
        Loop();
    }
    CloseWindow();
}

void Application::InitExperiment() {
    int display = GetCurrentMonitor();
    menu.make(GetMonitorHeight(display), GetMonitorWidth(display));
    menu.run();// show the menu for entering experimental parameters
    loadParams();
    experiment.onInit(params);// init experiment with the chosen options
    Experiment::displayExperimentInstructions(font);
}

void Application::loadParams() {
    params.n_dots = menu.getNDots();
    params.aperture = menu.getStimRadius();
    params.dotRadius = menu.getDotSize();
    params.condition_repetitions = menu.getConditionReps();
    params.coherence_levels = menu.getCoherenceLevels();

    params.speed_levels = menu.getSpeed();
    params.subjectID = menu.getParticipantID();
    params.runNumber = menu.getRunNumber();
    params.dotColor = menu.getDotColor();
}
