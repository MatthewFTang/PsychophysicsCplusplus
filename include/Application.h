//
// Created by Matthew F Tang on 31/5/2024.
//
#pragma once

#include <raylib.h>

#include "Experiment.h"
#include "ExperimentParams.h"
#include "Menu.h"
#pragma once

class Application
{
public:
  Application ();
  void Run ();

private:
  void Loop ();
  void InitExperiment ();
  void LoadParams ();

  Color background_color_ = {128, 128, 128};
  Font font_{};

  Menu menu_;
  Experiment experiment_;

  ExperimentParams params_;
};
