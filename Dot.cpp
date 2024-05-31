//
// Created by Matthew F Tang on 30/5/2024.
//

#include "Dot.h"
#include "raylib.h"
#include <cstdlib>
#include <cmath>

void Dot::draw() {
    int x1 = std::floor(x);
    int y1 = std::floor(y);
    DrawCircle(x1 + xOffset, y1 + yOffset, radius, color);                         // Draw a color-filled circle
    update();
}

void Dot::update() {
    x += speed * std::cos(direction);
    y += speed * std::sin(direction);
    if (outBounds()) {
        wrapCoordinates();
    }
}

bool Dot::outBounds() const {
    int dist = (x - aperture / 2) * (x - aperture / 2) + (y - aperture / 2) * (y - aperture / 2);
    return dist > (aperture * aperture) / 4;
}

void Dot::wrapCoordinates() {

    x = aperture - x;
    y = aperture - y;

}

Dot::Dot() {
    this->color = WHITE;

}


void Dot::make(int aperture, float direction, float speed, float radius) {
    this->aperture = aperture;
    this->radius = radius;
    this->speed = speed;
    this->direction = direction;
    int display = GetCurrentMonitor();
    this->xOffset = GetMonitorWidth(display) / 2 - aperture / 2;
    this->yOffset = GetMonitorHeight(display) / 2 - aperture / 2;

    this->x = (std::rand() % aperture);
    this->y = (std::rand() % aperture);

    if (outBounds()) {
        make(aperture, direction, speed, radius);
    }
}


