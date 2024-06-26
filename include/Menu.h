//
// Created by Matthew F Tang on 21/6/2024.
//

#ifndef MOTION_JUDGEMENTS_MENU_H
#define MOTION_JUDGEMENTS_MENU_H
#pragma once

#include <raylib.h>

#include <vector>

#include "imgui.h"
class Menu {

public:
    Menu() = default;

    void make(int _monitorHeight, int _monitorWidth);
    void run();
    std::vector<float> getCoherenceLevels() const { return coherence_levels; }
    std::vector<float> getSpeed() const { return speed_levels; }
    int getNDots() const { return n_dots; }
    int getStimRadius() const { return stimRadius; }
    int getDotSize() const { return dotSize; }
    int getConditionReps() const { return condition_repetitions; }
    char getParticipantID() const { return participant_ident; };
    int getRunNumber() const { return run_number; }
    Color getDotColor() const;

private:
    void draw();

    ImGuiWindowFlags window_flags;
    std::vector<float> makeLevels(float min, float max, int levels) const;

    int min_coherence = 1;
    int max_coherence = 50;
    int n_steps_coherence = 3;

    float min_speed = 1;
    float max_speed = 10;
    int n_steps_speed = 1;

    int n_dots = 1000;
    int stimRadius = 800;
    int dotSize = 4;
    char participant_ident;
    int run_number = 1;
    int condition_repetitions = 10;
    bool startClicked = false;
    float col[3] = {1.0f, 1.0f, 1.0f};
    int monitorWidth;
    int monitorHeight;
    std::vector<float> coherence_levels;
    std::vector<float> speed_levels;
};

#endif// MOTION_JUDGEMENTS_MENU_H
