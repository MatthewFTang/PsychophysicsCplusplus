//
// Created by Matthew F Tang on 30/5/2024.
//

#include "../include/Dot.h"

#include <cmath>
#include <cstdlib>

#include "raylib.h"

void
Dot::Draw ()
{
  const auto x1 = static_cast<int> (std::floor (x_)); //
  const auto y1 = static_cast<int> (std::floor (y_));
  DrawCircle (x1 + x_offset_, y1 + y_offset_, radius_,
	      color_); // Draw a color-filled circle
  Update ();
}

void
Dot::Update ()
{
  if (OutBounds ())
    {
      // wrap dots around aperture if outside the circle
      WrapCoordinates ();
    }
  // could be calculated when dots created
  x_ = x_ + speed_ * std::cos (direction_);
  y_ = y_ + speed_ * std::sin (direction_);
}

bool
Dot::OutBounds () const
{
  const float dist = (x_ * x_ + y_ * y_);
  return dist > aperture_ * aperture_ / 4;
}

void
Dot::WrapCoordinates ()
{
  x_ = -x_;
  y_ = -y_;
}

Dot::Dot () = default;

void
Dot::Make (const float aperture, const float direction, const float speed,
	   const float radius, const Color color, const Vector2 center_location)
{
  this->aperture_ = aperture;
  this->radius_ = radius;
  this->speed_ = speed;
  this->color_ = color;
  this->direction_ = direction;
  this->y_offset_ = static_cast<int> (center_location.y);
  this->x_offset_ = static_cast<int> (center_location.x);

  MakeDotPosition ();
  while (OutBounds ())
    {
      MakeDotPosition ();
    }
}

void
Dot::MakeDotPosition ()
{
  // all dots are assigned a random x and y position so the centre of the
  // circle is at 0,0 to make the maths cleaner.
  float x_temp
    = static_cast<float> (std::rand ()) / static_cast<float> (RAND_MAX);
  x_temp = x_temp * aperture_ - aperture_ / 2;

  float y_temp
    = static_cast<float> (std::rand ()) / static_cast<float> (RAND_MAX);
  y_temp = y_temp * aperture_ - aperture_ / 2;
  x_ = x_temp;
  y_ = y_temp;
}
