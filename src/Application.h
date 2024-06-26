//
// Created by Matthew F Tang on 31/5/2024.
//

#include <raylib.h>

#include "Experiment.h"
#include "ExperimentParams.h"
#include "Menu.h"
#include "dotField.h"
#pragma once


class Application {
private:
    void Loop();
    void InitExperiment();
    void loadParams();
    Color backgroundColor = {128, 128, 128};
    Font font{};

    Menu menu;
    Experiment experiment;

    ExperimentParams params;

public:
    void Run();

    Application();
};
