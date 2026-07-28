#ifndef LIGHT_H
#define LIGHT_H

#include "Tuple.h"
#include "Color.h"

struct pointLight {
    Tuple position;
    Color intensity;
    

    pointLight( const Tuple& t, const Color& c)
    : position {t}
    , intensity {c}
    {}
};

#endif