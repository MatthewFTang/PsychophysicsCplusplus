//
// Created by Matthew F Tang on 31/5/2024.
//

#ifndef MOTION_JUDGEMENTS_EXPERIMENT_H
#define MOTION_JUDGEMENTS_EXPERIMENT_H
#pragma once

#include <random>
#include <vector>

#include "DotFieldParams.h"
#include "ExperimentParams.h"
#include "dotField.h"
#include "responseScreen.h"

class Experiment {

public:
    Experiment() : gen(rd()) {}

    void run();
    void onInit(const ExperimentParams &_params);
    static void displayExperimentInstructions(Font const &font);

private:
    void newTrial();
    void onRender();
    static void fixationCross();
    void saveResponse();
    void writeResults();
    void makeTrialConditions();
    static void displayEndScreen();

    void makeFileSaveName();
    responseScreen response = responseScreen();
    dotField field = dotField();

    std::random_device rd;// random number seed
    std::mt19937 gen;     // random number generator
    float generateRandomFloat(float min, float max);

    int frameCount = 0;
    int trialCount = 0;
    float presented_direction;
    bool savedFile = false;
    std::string fileSaveName;

    ExperimentParams params;
    DotFieldParams dotFieldParams;
    std::vector<std::vector<float>> conditions;
    std::vector<std::vector<float>> results;
};

#endif// MOTION_JUDGEMENTS_EXPERIMENT_H
