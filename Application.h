//
// Created by Matthew F Tang on 31/5/2024.
//



#include <raylib.h>
#include "dotField.h"

#pragma once

class Application {
private:
    void Loop();

    void InitExperiment();

    Color backgroundColor = {128, 128, 128};
    dotField field;
    int frameCount = 0;
public:
    void Run();
};



