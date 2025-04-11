//
// Created by Matthew F Tang on 26/6/2024.
//

#pragma once

#include <raylib.h>

struct DotFieldParams {
  int n_dots;
  float coherence;
  float aperture;
  float direction;
  float speed;
  float radius;
  Color color;
  Vector2 centre_location;
};
