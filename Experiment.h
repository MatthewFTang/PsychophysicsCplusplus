//
// Created by Matthew F Tang on 31/5/2024.
//

#ifndef MOTION_JUDGEMENTS_EXPERIMENT_H
#define MOTION_JUDGEMENTS_EXPERIMENT_H

#include "dotField.h"
#include "responseScreen.h"
#include <vector>

class Experiment {
private:

    int frameCount = 0;
    int trialCount = 0;
    int nDots{}, aperture{}, radius{};
    float presented_direction = 0.0f;
    Color color{};

    std::vector<std::vector<float>> conditions;

    std::vector<std::vector<float>> results;

    dotField field = dotField();

    responseScreen response = responseScreen();

    void newTrial();

    void makeTrialConditions(int repetitions, std::vector<float> &_coherenceLevels, std::vector<float> &_speeds);

    void writeResults();

    static void fixationCross();


public:

    void onRender();

    bool experimentState();

    void
    onInit(int _nDots, int _aperture, int _radius, Color _color, int _repetitions,
           std::vector<float> &_coherenceLevels, std::vector<float> &_speeds);

    Experiment();

};


#endif //MOTION_JUDGEMENTS_EXPERIMENT_H
