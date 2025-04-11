cmake_minimum_required(VERSION 3.15)
project(motion_judgements LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================================
# Dependencies
# ==========================================================

# Raylib Dependency
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
    message(STATUS "Raylib not found. Fetching Raylib ${RAYLIB_VERSION}...")
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
    )
    FetchContent_MakeAvailable(raylib) # Automatically handles population
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Prevent building Raylib examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()

# Include Raylib directories
include_directories(${raylib_INCLUDE_DIRS})

# fmt Dependency
find_package(fmt QUIET)

if (NOT fmt_FOUND)
    message(STATUS "fmt not found. Fetching fmt...")
    FetchContent_Declare(
            fmt
            URL https://github.com/fmtlib/fmt/archive/refs/heads/master.zip
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
    )
    FetchContent_MakeAvailable(fmt)
endif()

# ImGui Dependency
FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/heads/master.zip
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_MakeAvailable(imgui)

# Manually add ImGui sources
set(IMGUI_SOURCES
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

# Add ImGui as a static library
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

# ==========================================================
# Project Setup
# ==========================================================
add_executable(${PROJECT_NAME}
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
        include/DotFieldParams.h
)

# Link libraries to the executable
target_link_libraries(${PROJECT_NAME}
        raylib
        fmt::fmt
        imgui
)

# Copy fonts directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts/)