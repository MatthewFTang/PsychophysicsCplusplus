//
// Created by Matthew F Tang on 30/5/2024.
//

#include "Dot.h"
#include "raylib.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

void Dot::draw() {
    int x1 = std::floor(x);
    int y1 = std::floor(y);
    DrawCircle(x1 + xOffset, y1 + yOffset, radius, color);                         // Draw a color-filled circle
    update();
}

void Dot::update() {


    if (outBounds()) {
        wrapCoordinates();
    }

    x = x + speed * std::cos(direction);
    y = y + speed * std::sin(direction);
}

bool Dot::outBounds() const {
    float dist = (x * x + y * y);
    return dist > aperture * aperture / 4;
}

void Dot::wrapCoordinates() {
    x = -x;
    y = -y;

}


Dot::Dot() = default;


void Dot::make(float _aperture, float _direction, float _speed, float _radius, Color _color) {
    this->aperture = _aperture;
    this->radius = _radius;
    this->speed = _speed;
    this->color = _color;
    this->direction = _direction;
    this->yOffset = GetScreenHeight() / 2;
    this->xOffset = GetScreenWidth() / 2;

    makeDotPosition();
    while (outBounds()) {
        makeDotPosition();
    }

}

void Dot::makeDotPosition() {

    float x_temp = (float) std::rand() / (float) RAND_MAX;
    x_temp = x_temp * aperture - aperture / 2;

    float y_temp = (float) std::rand() / (float) RAND_MAX;
    y_temp = y_temp * aperture - aperture / 2;
    x = x_temp;
    y = y_temp;


}


