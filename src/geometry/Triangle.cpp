#include "Triangle.h"
#include "Constants.h"
#include "Intersections.h"


Triangle::Triangle(const Tuple& p1, const Tuple& p2, const Tuple& p3,
                    const Color& c, double ambient, double diffuse,
                    double specular, double shininess, double reflectivity,
                    double transparency, double reflectiveIndex)
    : Shape(Materials(c, ambient, diffuse, specular, shininess,
                       reflectivity, transparency, reflectiveIndex))
    , m_p1 {p1}
    , m_p2 {p2}
    , m_p3 {p3}
    , m_e1 {p2 - p1}
    , m_e2 {p3 - p1}
    , m_normal {(cross(m_e2, m_e1)).normalize()}
    {
    }


std::vector<Intersection> Triangle::localIntersect(const Ray& localRay) const {

    auto dirCrossE2 {cross(localRay.getDirection(), m_e2)};
    auto det {dot(m_e1, dirCrossE2)};
    if (std::abs(det) < EPSILON ) {
        return {};
    }


    double f {1.0 / det};
    auto p1ToOrigin {localRay.getOrigin() - m_p1};
    auto u {f * dot(p1ToOrigin, dirCrossE2)};
    if (u > 1.0 || u < 0.0) {
        return {};
    }

    auto originCrossE1 {cross(p1ToOrigin, m_e1)};
    auto v {f * dot(localRay.getDirection(), originCrossE1)};
    if (v < 0.0 || ((u + v) > 1.0) ) {
        return {};
    }
    auto t {f * dot(m_e2, originCrossE1)};

    return {getIntersect(t, *this)};
}


// placeholder
Bounds Triangle::bounds() const {
    return Bounds(point(-1, -1, -1), point(1, 1, 1));
}