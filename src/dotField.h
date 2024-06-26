//
// Created by Matthew F Tang on 30/5/2024.
//

#pragma once

#include <random>
#include <vector>

#include "Dot.h"
#include "DotFieldParams.h"
class dotField {

public:
    dotField();
    void run();
    void make(const DotFieldParams &params);


private:
    std::random_device rd;
    std::mt19937 gen;

    float generateRandomFloat(float min, float max);
    std::vector<Dot> dots;
};
