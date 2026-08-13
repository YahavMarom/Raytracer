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

    bool operator==(const Intersection& other) const {
        return t == other.t && object == other.object; 
    }
};

struct Comp {
    double t {};
    const Shape* object{nullptr};
    Tuple point{};
    Tuple eyeVec{};
    Tuple normVec{};
    bool inside{false};
    Tuple overPoint{};
    Tuple reflectVec{};
    Tuple underPoint{};
    double n1 {1.0};
    double n2 {1.0};
};

Intersection getIntersect(double t, const Shape& s);

std::vector<Intersection> intersections(std::initializer_list<Intersection> list);

std::optional<Intersection> hit(const std::vector<Intersection>& xs);

Comp prepareComputations(const Intersection& I, const Ray& ray, const std::vector<Intersection>& xs = {});

double schlick(const Comp& comps);
#endif