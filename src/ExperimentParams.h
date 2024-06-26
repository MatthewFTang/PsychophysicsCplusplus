//
// Created by Matthew F Tang on 24/6/2024.
//

#ifndef MOTION_JUDGEMENTS_EXPERIMENTPARAMS_H
#define MOTION_JUDGEMENTS_EXPERIMENTPARAMS_H
#include <raylib.h>
#include <vector>
struct ExperimentParams {
    int n_dots;
    int aperture;
    int dotRadius;
    int condition_repetitions;
    std::vector<float> coherence_levels;
    std::vector<float> speed_levels;
    char subjectID;
    int runNumber;
    Color dotColor;
};
#endif//MOTION_JUDGEMENTS_EXPERIMENTPARAMS_H
