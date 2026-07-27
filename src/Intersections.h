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


Intersection intersection(double t, const Sphere& s);

std::vector<Intersection> intersect(const Sphere& s, const Ray& r);

std::vector<Intersection> intersections(std::initializer_list<Intersection> list);

std::optional<Intersection> hit(std::vector<Intersection>& xs);
#endif