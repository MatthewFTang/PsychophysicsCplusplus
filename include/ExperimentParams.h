//
// Created by Matthew F Tang on 24/6/2024.
//

#pragma once

#include <raylib.h>
#include <vector>
struct ExperimentParams
{
  int n_dots;
  int aperture;
  int dot_radius;
  int condition_repetitions;
  std::vector<float> coherence_levels;
  std::vector<float> speed_levels;
  char subject_id;
  int run_number;
  Color dot_color;
};
