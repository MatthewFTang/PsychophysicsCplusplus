//
// Created by Matthew F Tang on 31/5/2024.
//

#include "Experiment.h"

#include <fstream>
#include <iostream>
#include <random>// std::default_random_engine
#include <vector>

void Experiment::onRender() {
    // fixation cross displayed for 500 ms. Then dot field displayed for 1000ms
    // then response screen. The next trial begins immediately after feedback is
    // finished.
    if (savedFile)
        displayEndScreen();
    else if (frameCount < 30)
        fixationCross();
    else if (frameCount < 90) {
        field.run();
        fixationCross();
    } else
        response.run();

    frameCount++;
}

void Experiment::newTrial() {
    // a random direction is chosen for each trial.  The condition table
    // indicates the coherence level and speed to be presented.
    presented_direction = generateRandomFloat(0, 2 * PI);

    dotFieldParams.coherence = conditions[trialCount][1];
    dotFieldParams.speed = conditions[trialCount][2];
    dotFieldParams.direction = presented_direction;


    field.make(dotFieldParams);
    response.setFinished(false);
    response.set(params.aperture, RED, 5, presented_direction);
    frameCount = 0;
    trialCount++;
}


void Experiment::onInit(const ExperimentParams &_params) {
    params = _params;

    dotFieldParams.n_dots = params.n_dots;

    dotFieldParams.aperture = (float) params.aperture;
    dotFieldParams.radius = (float) params.dotRadius;
    dotFieldParams.centreLocation = {Vector2{(float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2}};
    dotFieldParams.color = params.dotColor;
    makeFileSaveName();
    // makes  a condition table so every trial has parameters for coherence and
    // motion speed. THe condition table is randomised.
    makeTrialConditions();
    newTrial();
}

void Experiment::makeTrialConditions() {
    auto nLevels1 = (int) params.coherence_levels.size();
    auto nLevels2 = (int) params.speed_levels.size();
    std::vector<std::vector<float>> conditions_temp;
    std::vector<int> order;
    int count = 0;
    for (int i = 0; i < params.condition_repetitions; i++) {
        for (int j = 0; j < nLevels1; j++) {
            for (int k = 0; k < nLevels2; k++) {
                std::vector<float> temp;
                temp.push_back(float(count));
                temp.push_back(params.coherence_levels[j]);
                temp.push_back(params.speed_levels[k]);
                conditions_temp.push_back(temp);
                order.push_back(count);
                count++;
            }
        }
    }

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::ranges::shuffle(order, std::default_random_engine(seed));

    conditions = conditions_temp;
    for (int i = 0; i < order.size(); i++) {
        conditions[i][0] = (float) i;
        conditions[i][1] = conditions_temp[order[i]][1];
        conditions[i][2] = conditions_temp[order[i]][2];
    }
}


void Experiment::fixationCross() {

    DrawLine(GetScreenWidth() / 2 - 20, GetScreenHeight() / 2,
             GetScreenWidth() / 2 + 20, GetScreenHeight() / 2, BLACK);
    DrawLine(GetScreenWidth() / 2, GetScreenHeight() / 2 - 20,
             GetScreenWidth() / 2, GetScreenHeight() / 2 + 20, BLACK);
}
void Experiment::run() {


    onRender();

    if (response.isResponseFinished()) {
        saveResponse();
        if (trialCount < conditions.size())
            newTrial();
        else if (!savedFile)
            writeResults();
    }
}
void Experiment::displayEndScreen() {
    DrawText("Experiment completed ", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, BLACK);
    DrawText("Thank you ", GetScreenWidth() / 2, GetScreenHeight() / 2 + 20, 20, BLACK);
}
void Experiment::saveResponse() {

    std::vector<float> temp;
    temp.push_back(conditions[trialCount - 1][0]);
    temp.push_back(conditions[trialCount - 1][1]);
    temp.push_back(conditions[trialCount - 1][2]);
    temp.push_back(presented_direction);
    temp.push_back(response.showResponseAngle());
    results.push_back(temp);
    frameCount = 0;
}

void Experiment::writeResults() {
    std::ofstream file(fileSaveName);
    file << "Trial,Coherence,Speed,Presented Direction,Response Direction\n";
    for (auto const &c: results) {
        for (auto const &r: c) {
            file << r << ",";
        }
        file << "\n";
    }
    savedFile = true;
}


float Experiment::generateRandomFloat(float min, float max) {

    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}
void Experiment::makeFileSaveName() {

    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_t);
    std::string time = std::format("{}{:04} - {:02}{:02}_{:02}_{:02}_{:04}.csv", params.subjectID, params.runNumber, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_mday, now_tm->tm_mon + 1, now_tm->tm_year);
    fileSaveName = time;
}
void Experiment::displayExperimentInstructions(Font const &font) {
    const char *text =
            "In this experiment, you will  judge the overall direction of the dots. \n\n"
            "In each trial, a fixation cross and a field of dots will be presented.\n"
            "Please try and keep your gaze centered on the fixation cross.\n"
            "A certain proportion  will move in the same direction.\n"
            "At the end of the trial you will use your mouse to make the blue arrow point in that direction.\n"
            "When you are satisfied, with your answer, press the LEFT MOUSE BUTTON. \n"
            "A red arrow wil appear to show the actually-presented direction.\n"
            "The next trial will begin shortly afterwards. \n\n\n "
            "Click to start";

    Vector2 textSize = MeasureTextEx(font, text, 48, 1);
    SetTextLineSpacing(52);
    bool click = false;
    float xPos = (float) GetScreenWidth() / 2 - textSize.x / 2;
    float yPos = (float) GetScreenHeight() / 2 - textSize.y / 2;
    while (!click) {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawTextEx(font, text, {xPos, yPos}, 48, 1, BLACK);
        if (IsMouseButtonDown(0)) { click = true; }
        EndDrawing();
    }
}
