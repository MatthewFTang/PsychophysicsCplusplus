//
// Created by Matthew F Tang on 26/6/2024.
//

#ifndef MOTION_JUDGEMENTS_DOTFIELDPARAMS_H
#define MOTION_JUDGEMENTS_DOTFIELDPARAMS_H

#include <raylib.h>

struct DotFieldParams {

    int n_dots;
    float coherence;
    float aperture;
    float direction;
    float speed;
    float radius;
    Color color;
    Vector2 centreLocation;
};
#endif//MOTION_JUDGEMENTS_DOTFIELDPARAMS_H
