cmake_minimum_required(VERSION 3.15)
project(motion_judgements LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
find_package(imgui REQUIRED)
find_package(fmt CONFIG REQUIRED)

#set(CMAKE_C_STANDARD 21) # Requires C11 standard

add_executable(${PROJECT_NAME} main.cpp
        main.cpp
        src/Dot.cpp
        include/Dot.h
        src/dotField.cpp
        src/responseScreen.cpp
        include/responseScreen.h
        src/Application.cpp
        include/Application.h
        src/Experiment.cpp
        include/Experiment.h
        src/Menu.cpp
        include/Menu.h
        src/rlimgui/rlImGui.h
        src/rlimgui/rlImGui.cpp
        include/ExperimentParams.h
        include/ExperimentParams.h
        include/DotFieldParams.h
        include/DotFieldParams.h)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} imgui::imgui)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts/)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
#if (APPLE)
#    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
#endif ()