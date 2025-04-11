//
// Created by Matthew F Tang on 31/5/2024.
//

#include "../include/Application.h"

#include <raylib.h>
Application::Application () = default;

void
Application::Loop ()
{
  BeginDrawing ();
  ClearBackground (background_color_);
  experiment_.Run ();
  DrawFPS (0, 0);
  EndDrawing ();
}
void
Application::Run ()
{
  const int display = GetCurrentMonitor ();

  InitWindow (GetMonitorWidth (display), GetMonitorHeight (display),
	      "Motion judgement");
  font_ = LoadFontEx ("fonts/FiraCodeNerdFontMono-Regular.ttf", 48, nullptr, 0);
  SetTargetFPS (60);
  InitExperiment ();

  while (!WindowShouldClose ())
    {
      Loop ();
    }
  CloseWindow ();
}

void
Application::InitExperiment ()
{
  const int display = GetCurrentMonitor ();
  menu_.Make (GetMonitorHeight (display), GetMonitorWidth (display));
  menu_.Run (); // show the menu for entering experimental parameters
  LoadParams ();
  experiment_.OnInit (params_); // init experiment with the chosen options
  Experiment::DisplayExperimentInstructions (font_);
}

void
Application::LoadParams ()
{
  params_.n_dots = menu_.GetNDots ();
  params_.aperture = menu_.GetStimRadius ();
  params_.dot_radius = menu_.GetDotSize ();
  params_.condition_repetitions = menu_.GetConditionReps ();
  params_.coherence_levels = menu_.GetCoherenceLevels ();

  params_.speed_levels = menu_.GetSpeed ();
  params_.subject_id = menu_.GetParticipantId ();
  params_.run_number = menu_.GetRunNumber ();
  params_.dot_color = menu_.GetDotColor ();
}
