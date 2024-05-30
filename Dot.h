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


private:
    void update();

    bool outBounds();

    void wrapCoordinates();

    int x{};
    int y{};
    float radius{};
    Color color{};
    float direction{};
    float speed{};

};


#endif //MY_PROJECT_DOT_H
