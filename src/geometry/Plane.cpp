#include "Plane.h"
#include "Constants.h"
#include <cassert>

std::vector<Intersection> Plane::localIntersect(const Ray& localRay) const {
    if (std::abs(localRay.getDirection().getY()) < EPSILON) {
        return {};
    }

    double t {-localRay.getOrigin().getY() / localRay.getDirection().getY()};

    return {Intersection{t, this} };
}


Tuple Plane::localNormalAt(const Tuple& p) const {
    assert(std::abs(p.getY()) < EPSILON);
    return vector(0.0, 1.0, 0.0);
    
}

Bounds Plane::bounds() const {
    return Bounds(point(-INF, 0, -INF), point(INF, 0, INF));
}