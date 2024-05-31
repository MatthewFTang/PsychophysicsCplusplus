//
// Created by Matthew F Tang on 30/5/2024.
//

#ifndef MY_PROJECT_DOT_H
#define MY_PROJECT_DOT_H
#pragma once

#include "raylib.h"


class Dot {

public:
    Dot();

    void draw();

    void make(int aperture, float direction, float speed, float radius);

    void update();


private:

    bool outBounds() const;

    void wrapCoordinates();

    float x{};
    float y{};
    float radius{};
    Color color{};
    float direction{};
    float speed{};
    int aperture;
    int xOffset, yOffset;

};


#endif //MY_PROJECT_DOT_H
