//
// Created by Matthew F Tang on 30/5/2024.
//

#include "dotField.h"
#include "Dot.h"
#include <cstdlib>
#include <cmath>


void dotField::run() {
    for (auto &dot: dots) {
        dot.draw();
    }
}

dotField::dotField() = default;

void
dotField::make(int n_dots, float coherence, int aperture, float direction, float speed, int radius, Color _color) {
    int n_coherent = std::floor((float) n_dots * coherence);
    float dir;
    dots.clear();
    for (int i = 0; i < n_dots; i++) {
        if (i < n_coherent) {
            dir = direction;

        } else {

            dir = (float) (std::rand() % 360) * PI / 180;
        }
        Dot dot;
        dot.make((float) aperture, dir, speed, (float) radius, _color);
        dots.push_back(dot);
    }
}

