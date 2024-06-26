//
// Created by Matthew F Tang on 31/5/2024.
//

#include "responseScreen.h"

#include <raylib.h>

#include <chrono>
#include <cmath>

void responseScreen::set(int _aperture, Color col, float _line_width,
                         float presentedAngle) {
    this->aperture = _aperture;
    this->color = col;
    this->line_width = _line_width;
    this->xOffset = (float) GetScreenWidth() / 2;
    this->yOffset = (float) GetScreenHeight() / 2;
    this->actualAngle = presentedAngle;
    beenClicked = false;
    finished = false;
}

void responseScreen::run() {
    if (!beenClicked) {
        getResponse();
    }
    if (beenClicked) {
        giveFeedback();
        std::chrono::high_resolution_clock::time_point currentTime =
                std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span =
                std::chrono::duration_cast<std::chrono::duration<double>>(currentTime -
                                                                          clickTime);
        if (time_span.count() > 0.5) {
            finished = true;
        }
    }
}

void responseScreen::getResponse() {
    Vector2 mousePos = GetMousePosition();
    float angle = std::atan2(mousePos.y - yOffset, mousePos.x - xOffset);

    drawAngle(angle, color);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        responseAngle = angle;
        clickTime = std::chrono::high_resolution_clock::now();
        beenClicked = true;
    }
}

void responseScreen::giveFeedback() const {
    drawAngle(responseAngle, color);
    drawAngle(actualAngle, BLUE);
}

float responseScreen::showResponseAngle() const { return responseAngle; }

void responseScreen::drawAngle(float angle, Color _color) const {
    float x = ((float) aperture / 2 - 10) * std::cos(angle);
    float y = ((float) aperture / 2 - 10) * std::sin(angle);

    DrawLineEx(Vector2({xOffset + x, yOffset + y}), Vector2({xOffset, yOffset}),
               line_width, _color);
    DrawPoly(Vector2{xOffset + x, yOffset + y}, 3, 20,
             angle * 180 / PI, _color);
}

responseScreen::responseScreen() = default;
