//
// Created by Matthew F Tang on 21/6/2024.
//

#include "../include/Menu.h"

#include <fmt/core.h>

#include <string>

#include "imgui.h"
#include "rlimgui/rlImGui.h"

void
Menu::Draw ()
{
  ImGui::Begin ("Menu", nullptr, window_flags_);
  ImGui::SetWindowPos (ImVec2 (static_cast<float> (monitor_width_) / 2 - 500,
			       static_cast<float> (monitor_height_) / 2 - 375));
  ImGui::SetWindowSize (ImVec2 (1000.f, 750.f));

  ImGui::Separator ();
  ImGui::SeparatorText ("Experiment parameters");
  ImGui::InputInt ("Min coherence", &min_coherence_);
  ImGui::InputInt ("Max coherence", &max_coherence_);
  ImGui::InputInt ("Number of steps", &n_steps_coherence_);

  coherence_levels_ = MakeLevels (static_cast<float> (min_coherence_) / 100,
				  static_cast<float> (max_coherence_) / 100,
				  n_steps_coherence_);

  ImGui::Text ("Coherence levels ( %% )");

  for (const auto c : coherence_levels_)
    {
      std::string str = fmt::format ("{:.2f}", c * 100);
      ImGui::SameLine ();
      ImGui::Button (str.c_str ());
    }

  ImGui::InputFloat ("Min speed", &min_speed_);
  ImGui::InputFloat ("Max speed", &max_speed_);
  ImGui::InputInt ("Number of steps (speed)", &n_steps_speed_);

  speed_levels_ = MakeLevels (min_speed_, max_speed_, n_steps_speed_);
  ImGui::Text ("Dot speed (pixels / frame)");

  for (const auto c : speed_levels_)
    {
      std::string str = fmt::format ("{:.2f}", c);
      ImGui::SameLine ();
      ImGui::Button (str.c_str ());
    }

  ImGui::InputInt ("Repetitions of stimulus conditions",
		   &condition_repetitions_);
  ImGui::Separator ();
  ImGui::SeparatorText ("Stimulus parameters");

  ImGui::InputInt ("Number of dots", &n_dots_);

  ImGui::InputInt ("Stimulus size (pixels) ", &stim_radius_);
  ImGui::InputInt ("Dot size (pixels)", &dot_size_);

  ImGui::ColorEdit3 ("Dot color", col_);

  ImGui::Separator ();
  ImGui::SeparatorText ("Participant");
  ImGui::InputText ("Participant initials", &participant_ident_, 32);
  ImGui::InputInt ("Run number", &run_number_);

  ImGui::Separator ();
  ImGui::SeparatorText ("Ready to start?");
  constexpr auto sz = ImVec2 (-FLT_MIN, 0.0f);

  start_clicked_ = ImGui::Button ("Start", sz);

  ImGui::End ();
}
void
Menu::Run ()
{
  while (!start_clicked_)
    {
      BeginDrawing ();
      rlImGuiBegin ();

      ClearBackground (BLACK);
      Draw ();

      rlImGuiEnd ();
      EndDrawing ();
    }
}
void
Menu::Make (const int monitor_height, const int monitor_width)
{
  monitor_height_ = monitor_height;
  monitor_width_ = monitor_width;

  rlImGuiSetup (true);
  window_flags_ = 0;
  window_flags_ |= ImGuiWindowFlags_NoTitleBar;
  window_flags_ |= ImGuiWindowFlags_NoMove;
  window_flags_ |= ImGuiWindowFlags_NoResize;

  ImGui::StyleColorsDark ();

  ImGuiIO &io = ImGui::GetIO ();
  (void) io;
  io.Fonts->AddFontDefault ();
  ImFont *font
    = io.Fonts->AddFontFromFileTTF ("fonts/FiraCode-Retina.ttf", 18.f);
  io.FontDefault = font;

  ImGuiStyle &style = ImGui::GetStyle ();
  style.WindowPadding = ImVec2 (15, 15);
  style.WindowRounding = 10.0f;
  style.FramePadding = ImVec2 (5, 5);
  style.FrameRounding = 12.0f; // Make all elements (checkboxes, etc) circles
  style.ItemSpacing = ImVec2 (12, 8);
  style.ItemInnerSpacing = ImVec2 (8, 6);
  style.IndentSpacing = 25.0f;
  style.ScrollbarSize = 15.0f;
  style.ScrollbarRounding = 9.0f;
  style.GrabMinSize = 20.0f; // Make grab a circle
  style.GrabRounding = 12.0f;
  style.PopupRounding = 7.f;
  style.Alpha = 1.0;

  rlImGuiEndInitImGui ();
}
std::vector<float>
Menu::MakeLevels (const float min, const float max, const int n_levels)
{
  std::vector<float> levels;
  if (n_levels > 1)
    {
      const float stepSize
	= (max - min) / (static_cast<float> (n_levels) - 1.f);

      for (int i = 0; i <= n_levels - 1; i++)
	{
	  float c = min + (static_cast<float> (i) * stepSize);
	  levels.push_back (c);
	}
    }
  else if (n_levels == 1)
    {
      levels.push_back (min);
    }

  return levels;
}
Color
Menu::GetDotColor () const
{
  const Vector4 colTemp = {col_[0], col_[1], col_[2], 1.0f};
  return ColorFromNormalized (colTemp);
}