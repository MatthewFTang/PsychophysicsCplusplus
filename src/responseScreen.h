//
// Created by Matthew F Tang on 31/5/2024.
//


#pragma once

#include <raylib.h>

#include <chrono>

class responseScreen {
public:
    responseScreen();

    void run();

    void set(int aperture, Color col, float line_width, float presentedAngle);

    bool isResponseFinished() const { return finished; }
    void setFinished(bool _finished) { finished = _finished; }

    float showResponseAngle() const;

private:
    void getResponse();

    void giveFeedback() const;

    void drawAngle(float angle, Color _color) const;


    bool finished = false;
    int aperture{};

    float responseAngle;
    float line_width;
    float xOffset;
    float yOffset;
    float actualAngle;
    std::chrono::high_resolution_clock::time_point clickTime;
    bool beenClicked = false;
    Color color{};
};
