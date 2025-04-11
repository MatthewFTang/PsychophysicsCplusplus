//
// Created by Matthew F Tang on 21/6/2024.
//

#pragma once

#include <raylib.h>

#include <vector>

#include "imgui.h"

class Menu
{
public:
  Menu () = default;

  void Make (int monitor_height, int monitor_width);
  void Run ();

  [[nodiscard]] std::vector<float> GetCoherenceLevels () const
  {
    return coherence_levels_;
  }
  [[nodiscard]] std::vector<float> GetSpeed () const { return speed_levels_; }
  [[nodiscard]] int GetNDots () const { return n_dots_; }
  [[nodiscard]] int GetStimRadius () const { return stim_radius_; }
  [[nodiscard]] int GetDotSize () const { return dot_size_; }
  [[nodiscard]] int GetConditionReps () const { return condition_repetitions_; }
  [[nodiscard]] char GetParticipantId () const { return participant_ident_; };
  [[nodiscard]] int GetRunNumber () const { return run_number_; }
  [[nodiscard]] Color GetDotColor () const;

private:
  void Draw ();

  ImGuiWindowFlags window_flags_{};
  static std::vector<float> MakeLevels (float min, float max, int levels);

  int min_coherence_ = 1;
  int max_coherence_ = 50;
  int n_steps_coherence_ = 3;

  float min_speed_ = 1;
  float max_speed_ = 10;
  int n_steps_speed_ = 1;

  int n_dots_ = 1000;
  int stim_radius_ = 800;
  int dot_size_ = 4;
  char participant_ident_{};
  int run_number_ = 1;
  int condition_repetitions_ = 10;
  bool start_clicked_ = false;
  float col_[3] = {1.0f, 1.0f, 1.0f};
  int monitor_width_{};
  int monitor_height_{};
  std::vector<float> coherence_levels_;
  std::vector<float> speed_levels_;
};
