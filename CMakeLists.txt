cmake_minimum_required(VERSION 3.15)
project(motion_judgements LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 21) # Requires C11 standard

add_executable(${PROJECT_NAME} main.cpp
        main.cpp
        Dot.cpp
        Dot.h
        dotField.cpp
        responseScreen.cpp
        responseScreen.h
        Application.cpp
        Application.h)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()