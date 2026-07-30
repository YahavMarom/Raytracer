#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "Sphere.h"
#include "Ray.h"
#include <vector>
#include <optional>
#include <initializer_list>



/* maybe changing sphere to shape */
struct Intersection {
    double t; 
    const Sphere* object;
};

struct Comp {
    double t;
    const Sphere* object;
    Tuple point;
    Tuple eyeVec;
    Tuple normVec;
    bool inside;
};


Intersection getIntersect(double t, const Sphere& s);

std::vector<Intersection> intersect(const Sphere& s, const Ray& r);

std::vector<Intersection> intersections(std::initializer_list<Intersection> list);

std::optional<Intersection> hit(const std::vector<Intersection>& xs);

Comp prepareComputations(const Intersection& I, const Ray& ray);



#endif