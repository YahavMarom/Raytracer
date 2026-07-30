#ifndef LIGHT_H
#define LIGHT_H

#include "Tuple.h"
#include "Color.h"

struct pointLight {
    Tuple position;
    Color intensity;
    

    pointLight( const Tuple& pos, const Color& c)
    : position {pos}
    , intensity {c}
    {}
};

#endif