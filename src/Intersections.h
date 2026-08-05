#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "Ray.h"
#include <vector>
#include <optional>
#include <initializer_list>

class Shape;

struct Intersection {
    double t; 
    const Shape* object;
};

struct Comp {
    double t;
    const Shape* object;
    Tuple point;
    Tuple eyeVec;
    Tuple normVec;
    bool inside;
    Tuple overPoint;
};

Intersection getIntersect(double t, const Shape& s);

std::vector<Intersection> intersections(std::initializer_list<Intersection> list);

std::optional<Intersection> hit(const std::vector<Intersection>& xs);

Comp prepareComputations(const Intersection& I, const Ray& ray);

#endif