//
// Created by Matthew F Tang on 31/5/2024.
//


#pragma once

#include <raylib.h>
#include <chrono>

class responseScreen {
public :
    responseScreen();

    void run();

    void set(int aperture, Color col, float line_width, float presentedAngle);

    bool finished = false;

    float showResponseAngle() const;

private:
    int aperture{};
    float responseAngle, line_width, xOffset, yOffset, actualAngle;
    std::chrono::high_resolution_clock::time_point clickTime;
    bool beenClicked = false;
    Color color{};

    void getResponse();

    void giveFeedback();

    void drawAngle(float angle, Color _color);

};


