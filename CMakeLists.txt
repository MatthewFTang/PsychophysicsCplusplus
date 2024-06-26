cmake_minimum_required(VERSION 3.15)
project(motion_judgements LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
find_package(imgui REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(CMAKE_C_STANDARD 21) # Requires C11 standard

add_executable(${PROJECT_NAME} main.cpp
        main.cpp
        src/Dot.cpp
        src/Dot.h
        src/dotField.cpp
        src/responseScreen.cpp
        src/responseScreen.h
        src/Application.cpp
        src/Application.h
        src/Experiment.cpp
        src/Experiment.h
        src/Menu.cpp
        src/Menu.h
        src/rlimgui/rlImGui.h
        src/rlimgui/rlImGui.cpp
        src/ExperimentParams.h
        src/ExperimentParams.h
        src/DotFieldParams.h
        src/DotFieldParams.h)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} imgui::imgui)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
# Checks if OSX and links appropriate frameworks (only required on MacOS)
#if (APPLE)
#    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
#endif ()