#include "Intersections.h"
#include "Constants.h"
#include "World.h"
#include "Transformations.h"
#include "Shape.h"
#include <cmath>
#include <algorithm>

Intersection getIntersect(double t, const Shape& s) {
    return Intersection{t, &s};
}

std::vector<Intersection> intersections(std::initializer_list<Intersection> list){
    std::vector<Intersection> xs {list};
    std::sort(xs.begin(), xs.end(),
                [](const Intersection& a, const Intersection& b) {
                    return a.t < b.t;
                }
            );
    return xs;
}

std::optional<Intersection> hit(const std::vector<Intersection>& xs) {
    for (const auto& i : xs) {
        if (i.t >= 0) {
            return i;
        }
    }
    return std::nullopt;
}

Comp prepareComputations(const Intersection& I, const Ray& ray) {
    Tuple pos {ray.getPosition(I.t)};
    Comp res {I.t, I.object, pos, -ray.getDirection(), I.object->normalAt(pos), false, pos, vector(0, 0, 0)};

    if (dot(res.normVec, res.eyeVec) < 0.0) {
        res.inside = true;
        res.normVec = -res.normVec;
    }
    res.overPoint = res.point + res.normVec * EPSILON;
    res.reflectVec = reflect(ray.getDirection(), res.normVec);


    return res;
}