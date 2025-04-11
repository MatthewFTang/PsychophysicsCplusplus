//
// Created by Matthew F Tang on 31/5/2024.
//

#pragma once

#include <random>
#include <vector>

#include "DotFieldParams.h"
#include "ExperimentParams.h"
#include "DotField.h"
#include "ResponseScreen.h"

class Experiment
{
public:
  Experiment () : gen_ (rd_ ()) {}

  void Run ();
  void OnInit (const ExperimentParams &params);
  static void DisplayExperimentInstructions (Font const &font);

private:
  void NewTrial ();
  void OnRender ();
  static void FixationCross ();
  void SaveResponse ();
  void WriteResults ();
  void MakeTrialConditions ();
  static void DisplayEndScreen ();

  void MakeFileSaveName ();
  ResponseScreen response_ = ResponseScreen ();
  DotField field_ = DotField ();

  std::random_device rd_; // random number seed
  std::mt19937 gen_;	  // random number generator
  float GenerateRandomFloat (float min, float max);

  int frame_count_ = 0;
  int trial_count_ = 0;
  float presented_direction_{};
  bool saved_file_ = false;
  std::string file_save_name_;

  ExperimentParams params_;
  DotFieldParams dot_field_params_params_{};
  std::vector<std::vector<float> > conditions_;
  std::vector<std::vector<float> > results_;
};
