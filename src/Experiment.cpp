//
// Created by Matthew F Tang on 31/5/2024.
//

#include "../include/Experiment.h"

#include <fstream>
#include <iostream>
#include <random> // std::default_random_engine
#include <vector>

void
Experiment::OnRender ()
{
  // fixation cross displayed for 500 ms. Then dot field displayed for 1000ms
  // then response screen. The next trial begins immediately after feedback is
  // finished.
  if (saved_file_)
    DisplayEndScreen ();
  else if (frame_count_ < 30)
    FixationCross ();
  else if (frame_count_ < 90)
    {
      field_.Run ();
      FixationCross ();
    }
  else
    response_.Run ();

  frame_count_++;
}

void
Experiment::NewTrial ()
{
  // a random direction is chosen for each trial.  The condition table
  // indicates the coherence level and speed to be presented.
  presented_direction_ = GenerateRandomFloat (0, 2 * PI);

  dot_field_params_params_.coherence = conditions_[trial_count_][1];
  dot_field_params_params_.speed = conditions_[trial_count_][2];
  dot_field_params_params_.direction = presented_direction_;

  field_.Make (dot_field_params_params_);
  response_.SetFinished (false);
  response_.Set (params_.aperture, RED, 5, presented_direction_);
  frame_count_ = 0;
  trial_count_++;
}

void
Experiment::OnInit (const ExperimentParams &params)
{
  params_ = params;

  dot_field_params_params_.n_dots = params_.n_dots;

  dot_field_params_params_.aperture = static_cast<float> (params_.aperture);
  dot_field_params_params_.radius = static_cast<float> (params_.dot_radius);
  dot_field_params_params_.centre_location
    = {Vector2{static_cast<float> (GetScreenWidth ()) / 2,
	       static_cast<float> (GetScreenHeight ()) / 2}};
  dot_field_params_params_.color = params_.dot_color;
  MakeFileSaveName ();
  // makes  a condition table so every trial has parameters for coherence and
  // motion speed. THe condition table is randomised.
  MakeTrialConditions ();
  NewTrial ();
}

void
Experiment::MakeTrialConditions ()
{
  const auto nLevels1 = static_cast<int> (params_.coherence_levels.size ());
  const auto nLevels2 = static_cast<int> (params_.speed_levels.size ());
  std::vector<std::vector<float> > conditions_temp;
  std::vector<int> order;
  int count = 0;
  for (int i = 0; i < params_.condition_repetitions; i++)
    {
      for (int j = 0; j < nLevels1; j++)
	{
	  for (int k = 0; k < nLevels2; k++)
	    {
	      std::vector<float> temp;
	      temp.push_back (static_cast<float> (count));
	      temp.push_back (params_.coherence_levels[j]);
	      temp.push_back (params_.speed_levels[k]);
	      conditions_temp.push_back (temp);
	      order.push_back (count);
	      count++;
	    }
	}
    }

  auto seed = std::chrono::system_clock::now ().time_since_epoch ().count ();

  std::random_device rd;
  std::mt19937 g (rd ());

  std::shuffle (order.begin (), order.end (), g);

  conditions_ = conditions_temp;
  for (int i = 0; i < order.size (); i++)
    {
      conditions_[i][0] = static_cast<float> (i);
      conditions_[i][1] = conditions_temp[order[i]][1];
      conditions_[i][2] = conditions_temp[order[i]][2];
    }
}

void
Experiment::FixationCross ()
{
  DrawLine (GetScreenWidth () / 2 - 20, GetScreenHeight () / 2,
	    GetScreenWidth () / 2 + 20, GetScreenHeight () / 2, BLACK);
  DrawLine (GetScreenWidth () / 2, GetScreenHeight () / 2 - 20,
	    GetScreenWidth () / 2, GetScreenHeight () / 2 + 20, BLACK);
}
void
Experiment::Run ()
{
  OnRender ();

  if (response_.IsResponseFinished ())
    {
      SaveResponse ();
      if (trial_count_ < conditions_.size ())
	NewTrial ();
      else if (!saved_file_)
	WriteResults ();
    }
}
void
Experiment::DisplayEndScreen ()
{
  DrawText ("Experiment completed ", GetScreenWidth () / 2,
	    GetScreenHeight () / 2, 20, BLACK);
  DrawText ("Thank you ", GetScreenWidth () / 2, GetScreenHeight () / 2 + 20,
	    20, BLACK);
}
void
Experiment::SaveResponse ()
{
  std::vector<float> temp;
  temp.push_back (conditions_[trial_count_ - 1][0]);
  temp.push_back (conditions_[trial_count_ - 1][1]);
  temp.push_back (conditions_[trial_count_ - 1][2]);
  temp.push_back (presented_direction_);
  temp.push_back (response_.ShowResponseAngle ());
  results_.push_back (temp);
  frame_count_ = 0;
}

void
Experiment::WriteResults ()
{
  std::ofstream file (file_save_name_);
  file << "Trial,Coherence,Speed,Presented Direction,Response Direction\n";
  for (auto const &c : results_)
    {
      for (auto const &r : c)
	{
	  file << r << ",";
	}
      file << "\n";
    }
  saved_file_ = true;
}

float
Experiment::GenerateRandomFloat (const float min, const float max)
{
  std::uniform_real_distribution<float> dist (min, max);
  return dist (gen_);
}
void
Experiment::MakeFileSaveName ()
{
  auto now = std::chrono::system_clock::now ();
  const std::time_t now_t = std::chrono::system_clock::to_time_t (now);
  std::tm *now_tm = std::localtime (&now_t);
  std::string time
    = std::format ("{}{:04} - {:02}{:02}_{:02}_{:02}_{:04}.csv",
		   params_.subject_id, params_.run_number, now_tm->tm_hour,
		   now_tm->tm_min, now_tm->tm_mday, now_tm->tm_mon + 1,
		   now_tm->tm_year);
  file_save_name_ = time;
}
void
Experiment::DisplayExperimentInstructions (Font const &font)
{
  const char *text
    = "In this experiment, you will  judge the overall direction of the dots. "
      "\n\n"
      "In each trial, a fixation cross and a field of dots will be presented.\n"
      "Please try and keep your gaze centered on the fixation cross.\n"
      "A certain proportion  will move in the same direction.\n"
      "At the end of the trial you will use your mouse to make the blue arrow "
      "point in that direction.\n"
      "When you are satisfied, with your answer, press the LEFT MOUSE BUTTON. "
      "\n"
      "A red arrow wil appear to show the actually-presented direction.\n"
      "The next trial will begin shortly afterwards. \n\n\n "
      "Click to start";

  auto [x, y] = MeasureTextEx (font, text, 48, 1);
  SetTextLineSpacing (52);
  bool click = false;
  const float xPos = static_cast<float> (GetScreenWidth ()) / 2 - x / 2;
  const float yPos = static_cast<float> (GetScreenHeight ()) / 2 - y / 2;
  while (!click)
    {
      BeginDrawing ();
      ClearBackground (GRAY);
      DrawTextEx (font, text, {xPos, yPos}, 48, 1, BLACK);
      if (IsMouseButtonDown (0))
	{
	  click = true;
	}
      EndDrawing ();
    }
}
