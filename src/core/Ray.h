#ifndef RAY_H
#define RAY_H

#include "Tuple.h"
#include <iostream>

class Ray {

private:
    Tuple m_origin;
    Tuple m_direction;

public:
    Ray(const Tuple& origin, const Tuple& direction);
    const Tuple& getOrigin() const;
    const Tuple& getDirection() const;


    Tuple getPosition(double time) const;

};

std::ostream& operator<<(std::ostream& os, const Ray& r);

#endif