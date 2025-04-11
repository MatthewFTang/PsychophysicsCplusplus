//
// Created by Matthew F Tang on 31/5/2024.
//

#pragma once

#include <raylib.h>

#include <chrono>

class ResponseScreen
{
public:
  ResponseScreen ();

  void Run ();
  void Set (int aperture, Color col, float line_width, float presented_angle);
  float ShowResponseAngle () const;

  bool IsResponseFinished () const { return finished_; }
  void SetFinished (const bool finished) { finished_ = finished; }

private:
  void GetResponse ();
  void GiveFeedback () const;
  void DrawAngle (float angle, Color color) const;

  bool finished_ = false;
  int aperture_{};

  float response_angle_{};
  float line_width_{};
  float x_offset_{};
  float y_offset_{};
  float actual_angle_{};
  std::chrono::high_resolution_clock::time_point click_time_;
  bool been_clicked_ = false;
  Color color_{};
};
