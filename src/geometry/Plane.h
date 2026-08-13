#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"


// specifically plane XZ. LocalIntersect is different for other planes.
class Plane: public Shape {

public:
    Plane() = default;
    ~Plane() override = default;

    std::vector<Intersection> localIntersect(const Ray& localRay) const override;
    Tuple localNormalAt(const Tuple& localPoint) const override;

    

};


#endif