//
// Created by Matthew F Tang on 30/5/2024.
//

#pragma once

#include "raylib.h"

class Dot
{
public:
  Dot ();

  void Draw ();

  void Make (float aperture, float direction, float speed, float radius,
	     Color color, Vector2 center_location);

  void Update ();

private:
  [[nodiscard]] bool OutBounds () const;

  void MakeDotPosition ();

  void WrapCoordinates ();

  float x_{};
  float y_{};
  float radius_{};
  Color color_{};
  float direction_{};
  float speed_{};
  float aperture_{};
  int x_offset_{};
  int y_offset_{};
};
