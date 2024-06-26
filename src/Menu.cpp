//
// Created by Matthew F Tang on 21/6/2024.
//

#include "Menu.h"

#include <fmt/core.h>

#include <string>

#include "imgui.h"
#include "rlimgui/rlImGui.h"
void Menu::draw() {


    ImGui::Begin("Menu", nullptr, window_flags);
    ImGui::SetWindowPos(ImVec2((float) monitorWidth / 2 - 500, (float) monitorHeight / 2 - 375));
    ImGui::SetWindowSize(ImVec2(1000.f, 750.f));

    ImGui::Separator();
    ImGui::SeparatorText("Experiment parameters");
    ImGui::InputInt("Min coherence", &min_coherence);
    ImGui::InputInt("Max coherence", &max_coherence);
    ImGui::InputInt("Number of steps", &n_steps_coherence);

    coherence_levels = makeLevels((float) min_coherence / 100,
                                  (float) max_coherence / 100, n_steps_coherence);

    ImGui::Text("Coherence levels ( %% )");

    for (const auto c: coherence_levels) {
        std::string str = fmt::format("{:.2f}", c * 100);
        ImGui::SameLine();
        ImGui::Button(str.c_str());
    }

    ImGui::InputFloat("Min speed", &min_speed);
    ImGui::InputFloat("Max speed", &max_speed);
    ImGui::InputInt("Number of steps (speed)", &n_steps_speed);

    speed_levels = makeLevels(min_speed, max_speed, n_steps_speed);
    ImGui::Text("Dot speed (pixels / frame)");

    for (const auto c: speed_levels) {
        std::string str = fmt::format("{:.2f}", c);
        ImGui::SameLine();
        ImGui::Button(str.c_str());
    }

    ImGui::InputInt("Repetitions of stimulus conditions", &condition_repetitions);
    ImGui::Separator();
    ImGui::SeparatorText("Stimulus parameters");

    ImGui::InputInt("Number of dots", &n_dots);

    ImGui::InputInt("Stimulus size (pixels) ", &stimRadius);
    ImGui::InputInt("Dot size (pixels)", &dotSize);

    ImGui::ColorEdit3("Dot color", col);


    ImGui::Separator();
    ImGui::SeparatorText("Participant");
    ImGui::InputText("Participant initials", &participant_ident, 32);
    ImGui::InputInt("Run number", &run_number);

    ImGui::Separator();
    ImGui::SeparatorText("Ready to start?");
    auto sz = ImVec2(-FLT_MIN, 0.0f);

    startClicked = ImGui::Button("Start", sz);

    ImGui::End();
}
void Menu::run() {
    while (!startClicked) {
        BeginDrawing();
        rlImGuiBegin();

        ClearBackground(BLACK);
        draw();

        rlImGuiEnd();
        EndDrawing();
    }
}
void Menu::make(int _monitorHeight, int _monitorWidth) {

    monitorHeight = _monitorHeight;
    monitorWidth = _monitorWidth;

    rlImGuiSetup(true);
    window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;


    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.Fonts->AddFontDefault();
    ImFont *font =
            io.Fonts->AddFontFromFileTTF("fonts/FiraCode-Retina.ttf", 18.f);
    io.FontDefault = font;

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 10.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 12.0f;// Make all elements (checkboxes, etc) circles
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 20.0f;// Make grab a circle
    style.GrabRounding = 12.0f;
    style.PopupRounding = 7.f;
    style.Alpha = 1.0;

    rlImGuiEndInitImGui();
}
std::vector<float> Menu::makeLevels(float min, float max, int n_levels) const {
    std::vector<float> levels;
    if (n_levels > 1) {
        float stepSize = (max - min) / ((float) n_levels - 1.f);

        for (int i = 0; i <= n_levels - 1; i++) {
            float c = min + ((float) i * stepSize);
            levels.push_back(c);
        }
    } else if (n_levels == 1) {
        levels.push_back(min);
    }

    return levels;
}
Color Menu::getDotColor() const {

    Vector4 colTemp = {col[0], col[1], col[2], 1.0f};
    return ColorFromNormalized(colTemp);
}