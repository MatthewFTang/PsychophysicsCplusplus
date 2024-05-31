//
// Created by Matthew F Tang on 31/5/2024.
//


#pragma once

#include <raylib.h>

class responseScreen {
public :
    void draw();

    responseScreen(int aperture, Color col, float line_width);

    bool beenClicked = false;

private:
    int aperture;
    Color color;
    float line_width;
};


