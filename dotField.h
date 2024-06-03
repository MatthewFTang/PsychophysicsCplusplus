//
// Created by Matthew F Tang on 30/5/2024.
//



#pragma  once

#include "Dot.h"
#include <vector>


class dotField {

public :
    dotField();

    void run();

    void make(int n_dots, float coherence, int aperture, float direction, float speed, int radius, Color color);

private:
    std::vector<Dot> dots;

};


