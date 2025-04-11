//
// Created by Matthew F Tang on 30/5/2024.
//

#pragma once

#include <random>
#include <vector>

#include "Dot.h"
#include "DotFieldParams.h"
class DotField
{
public:
  DotField ();
  void Run ();
  void Make (const DotFieldParams &params);

private:
  std::random_device rd_;
  std::mt19937 gen_;

  float GenerateRandomFloat (float min, float max);
  std::vector<Dot> dots_;
};
