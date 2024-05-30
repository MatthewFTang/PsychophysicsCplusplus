//
// Created by Matthew F Tang on 30/5/2024.
//

#include "Dot.h"
#include "raylib.h"
#include <cstdlib>
#include <cmath>

void Dot::draw() {
    DrawCircle(x, y, radius, color);                         // Draw a color-filled circle
    update();
}

void Dot::update() {
    x += speed * std::cos(direction);
    y += speed * std::sin(direction);
    if (outBounds()) {
        wrapCoordinates();
    }
}

bool Dot::outBounds() {
    float dist = (x - 400) * (x - 400) + (y - 400) * (y - 400);

    return dist > 350 * 350;
}

void Dot::wrapCoordinates() {
//    x = 800 - x;
//    y = 800 - y;
    while (outBounds()) {
        x = (std::rand() % 800);
        y = (std::rand() % 800);
    }

}

Dot::Dot() {
    this->x = (std::rand() % 800);
    this->y = (std::rand() % 800);
    if (outBounds()) {
        Dot();
    }

    this->radius = 5;
    float temp_direction = std::rand() % 360;
    temp_direction = temp_direction * PI / 180;
    this->direction = temp_direction;
    this->speed = 1.0f;
    this->color = Color({(unsigned char) (std::rand() % 255), (unsigned char) (std::rand() % 255),
                         (unsigned char) (std::rand() % 255), 255});

}


