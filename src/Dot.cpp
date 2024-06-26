//
// Created by Matthew F Tang on 30/5/2024.
//

#include "Dot.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>

void Dot::draw() {
  auto x1 = (int)std::floor(x); //
  auto y1 = (int)std::floor(y);
  DrawCircle(x1 + xOffset, y1 + yOffset, radius,
             color); // Draw a color-filled circle
  update();
}

void Dot::update() {

  if (outBounds()) { // wrap dots around aperture if outside the circle
    wrapCoordinates();
  }
  // could be calculated when dots created
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

void Dot::make(float _aperture, float _direction, float _speed, float _radius,
               Color _color, Vector2 centerLocation) {
  this->aperture = _aperture;
  this->radius = _radius;
  this->speed = _speed;
  this->color = _color;
  this->direction = _direction;
  this->yOffset = (int)centerLocation.y;
  this->xOffset = (int)centerLocation.x;

  makeDotPosition();
  while (outBounds()) {
    makeDotPosition();
  }
}

void Dot::makeDotPosition() {
  // all dots are assigned a random x and y position so the centre of the
  // circle is at 0,0 to make the maths cleaner.
  float x_temp = (float)std::rand() / (float)RAND_MAX;
  x_temp = x_temp * aperture - aperture / 2;

  float y_temp = (float)std::rand() / (float)RAND_MAX;
  y_temp = y_temp * aperture - aperture / 2;
  x = x_temp;
  y = y_temp;
}
