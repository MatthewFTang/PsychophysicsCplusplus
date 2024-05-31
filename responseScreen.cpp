//
// Created by Matthew F Tang on 31/5/2024.
//

#include "responseScreen.h"
#include <raylib.h>
#include <cmath>

responseScreen::responseScreen(int aperture, Color col, float line_width) {
    this->aperture = aperture;
    this->color = col;
    this->line_width = line_width;
}

void responseScreen::draw() {
    Vector2 mousePos = GetMousePosition();
    float angle = std::atan2(mousePos.y - aperture / 2, mousePos.x - aperture / 2);
    float x = (aperture / 2 - 10) * std::cos(angle);
    float y = (aperture / 2 - 10) * std::sin(angle);
    DrawLine(aperture / 2, aperture / 2, x + aperture / 2, y + aperture / 2, color);
    DrawRing(Vector2{(float) aperture / 2, (float) aperture / 2}, (float) aperture / 2 - 10 - line_width,
             (float) aperture / 2 - 10,
             0, 360, 120,
             color);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        beenClicked = true;
    }
}
