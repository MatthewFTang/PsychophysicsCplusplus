//
// Created by Matthew F Tang on 31/5/2024.
//

#include "../include/ResponseScreen.h"

#include <raylib.h>

#include <chrono>
#include <cmath>

void
ResponseScreen::Set (const int aperture, const Color col,
		     const float line_width, const float presented_angle)
{
  this->aperture_ = aperture;
  this->color_ = col;
  this->line_width_ = line_width;
  this->x_offset_ = static_cast<float> (GetScreenWidth ()) / 2;
  this->y_offset_ = static_cast<float> (GetScreenHeight ()) / 2;
  this->actual_angle_ = presented_angle;
  been_clicked_ = false;
  finished_ = false;
}

void
ResponseScreen::Run ()
{
  if (!been_clicked_)
    {
      GetResponse ();
    }
  if (been_clicked_)
    {
      GiveFeedback ();
      const std::chrono::high_resolution_clock::time_point currentTime
	= std::chrono::high_resolution_clock::now ();
      const std::chrono::duration<double> time_span
	= std::chrono::duration_cast<std::chrono::duration<double>> (
	  currentTime - click_time_);
      if (time_span.count () > 0.5)
	{
	  finished_ = true;
	}
    }
}

void
ResponseScreen::GetResponse ()
{
  auto [x, y] = GetMousePosition ();
  const float angle = std::atan2 (y - y_offset_, x - x_offset_);

  DrawAngle (angle, color_);

  if (IsMouseButtonPressed (MOUSE_LEFT_BUTTON))
    {
      response_angle_ = angle;
      click_time_ = std::chrono::high_resolution_clock::now ();
      been_clicked_ = true;
    }
}

void
ResponseScreen::GiveFeedback () const
{
  DrawAngle (response_angle_, color_);
  DrawAngle (actual_angle_, BLUE);
}

float
ResponseScreen::ShowResponseAngle () const
{
  return response_angle_;
}

void
ResponseScreen::DrawAngle (const float angle, const Color color) const
{
  float x = (static_cast<float> (aperture_) / 2 - 10) * std::cos (angle);
  float y = (static_cast<float> (aperture_) / 2 - 10) * std::sin (angle);

  DrawLineEx (Vector2 ({x_offset_ + x, y_offset_ + y}),
	      Vector2 ({x_offset_, y_offset_}), line_width_, color);
  DrawPoly (Vector2{x_offset_ + x, y_offset_ + y}, 3, 20, angle * 180 / PI,
	    color);
}

ResponseScreen::ResponseScreen () = default;
