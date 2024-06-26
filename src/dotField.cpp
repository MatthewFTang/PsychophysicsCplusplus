//
// Created by Matthew F Tang on 30/5/2024.
//

#include "../include/dotField.h"

#include <cmath>

#include "../include/Dot.h"


void dotField::make(const DotFieldParams &params) {
    auto n_coherent = (int) std::floor((float) params.n_dots * params.coherence);
    //  number of coherent dots
    dots.clear();
    float dir;
    for (int i = 0; i < params.n_dots; i++) {
        if (i < n_coherent) {      // assigns the coherent dots the global direction
            dir = params.direction;// gives the dot the global direction
        } else {
            dir = generateRandomFloat(0, PI * 2);// gives dot random direction
        }
        Dot dot;
        dot.make(params.aperture, dir, params.speed, params.radius, params.color,
                 params.centreLocation);
        dots.push_back(dot);
    }
}


// loop through all the dots in field and draw them
void dotField::run() {
    for (auto &dot: dots) {
        dot.draw();
    }
}


float dotField::generateRandomFloat(float min, float max) {

    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}
dotField::dotField() : gen(rd()) {
}
