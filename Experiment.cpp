//
// Created by Matthew F Tang on 31/5/2024.
//

#include "Experiment.h"
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <iostream>
#include <vector>
#include <fstream>

void Experiment::onRender() {

    if (frameCount < 30) {
        fixationCross();
    } else if (frameCount < 90) {
        field.run();
        fixationCross();
    } else {
        response.run();
        if (response.finished) {
            std::vector<float> temp;
            temp.push_back(conditions[trialCount][0]);
            temp.push_back(conditions[trialCount][1]);
            temp.push_back(conditions[trialCount][2]);
            temp.push_back(presented_direction);
            temp.push_back(response.showResponseAngle());
            results.push_back(temp);
            newTrial();
            trialCount++;

            frameCount = 0;
        }
    }

    frameCount++;
}


void Experiment::newTrial() {
    presented_direction = (float) (std::rand() % 360) * PI / 180;
    field.make(nDots, conditions[trialCount][1], aperture, presented_direction, conditions[trialCount][2], radius,
               color);
    response.set(aperture, RED, 5, presented_direction);

}

Experiment::Experiment() = default;

void Experiment::onInit(int _nDots, int _aperture, int _radius, Color _color, int _repetitions,
                        std::vector<float> &_coherenceLevels, std::vector<float> &_speeds) {

    makeTrialConditions(_repetitions, _coherenceLevels, _speeds);
    this->nDots = _nDots;
    this->aperture = _aperture;
    this->radius = _radius;
    this->color = _color;

}

void
Experiment::makeTrialConditions(int repetitions, std::vector<float> &_coherenceLevels, std::vector<float> &_speeds) {
    int nLevels1 = (int) _coherenceLevels.size();
    int nLevels2 = (int) _speeds.size();
    std::vector<std::vector<float>> conditions_temp;
    std::vector<int> order;
    int count = 0;
    for (int i = 0; i < repetitions; i++) {
        for (int j = 0; j < nLevels1; j++) {
            for (int k = 0; k < nLevels2; k++) {
                std::vector<float> temp;
                temp.push_back(float(count));
                temp.push_back(_coherenceLevels[j]);
                temp.push_back(_speeds[k]);
                conditions_temp.push_back(temp);

                order.push_back(count);
                count++;
            }
        }
    }


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(order.begin(), order.end(), std::default_random_engine(seed));
    conditions = conditions_temp;
    for (int i = 0; i < order.size(); i++) {
        conditions[i][0] = (float) i;
        conditions[i][1] = conditions_temp[order[i]][1];
        conditions[i][2] = conditions_temp[order[i]][2];
    }

}

bool Experiment::experimentState() {
    if (trialCount < conditions.size()) {
        return true;
    } else {
        writeResults();
        return false;
    }
}

void Experiment::writeResults() {
    std::ofstream file("results.csv");
    file << "Trial,Coherence,Speed,Presented Direction,Response Direction\n";
    for (auto &c: results) {
        for (auto &r: c) {
            file << r << ",";
        }
        file << "\n";
    }

}

void Experiment::fixationCross() {

    DrawLine(GetScreenWidth() / 2 - 10, GetScreenHeight() / 2, GetScreenWidth() / 2 + 10, GetScreenHeight() / 2, BLACK);
    DrawLine(GetScreenWidth() / 2, GetScreenHeight() / 2 - 10, GetScreenWidth() / 2, GetScreenHeight() / 2 + 10, BLACK);

}









