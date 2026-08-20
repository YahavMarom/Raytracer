#include "Bounds.h"


Bounds::Bounds() 
    : m_min {point(INF, INF, INF)}
    , m_max {point(-INF, -INF, -INF)}
    {}


Bounds::Bounds(const Tuple& minPoint, const Tuple& maxPoint) 
    : m_min {minPoint}
    , m_max {maxPoint}
    {}

void Bounds::insert(const Tuple& p) {
    m_min = point(
        std::min(m_min.getX(), p.getX()),
        std::min(m_min.getY(), p.getY()),
        std::min(m_min.getZ(), p.getZ())
    );

    m_max = point(
        std::max(m_max.getX(), p.getX()),
        std::max(m_max.getY(), p.getY()),
        std::max(m_max.getZ(), p.getZ())
    );
}

void Bounds::insert(const Bounds& b) {
    insert(b.getMin());
    insert(b.getMax());
}

Bounds merge(const Bounds& b1, const Bounds& b2) {
    Bounds res = b1;
    res.insert(b2);
    return res;
}

Bounds Bounds::transform(const Matrix& m) const {
    Tuple p0 {m_min};
    Tuple p1 {point(m_max.getX(), m_min.getY(), m_min.getZ())};
    Tuple p2 {point(m_min.getX(), m_max.getY(), m_min.getZ())};
    Tuple p3 {point(m_min.getX(), m_min.getY(), m_max.getZ())};
    Tuple p4 {point(m_max.getX(), m_max.getY(), m_min.getZ())};
    Tuple p5 {point(m_max.getX(), m_min.getY(), m_max.getZ())};
    Tuple p6 {point(m_min.getX(), m_max.getY(), m_max.getZ())};
    Tuple p7 {m_max};

    Bounds box;
    Tuple corners[8] = {p0, p1, p2, p3, p4, p5, p6, p7};
    for (const auto& c : corners) {
        box.insert(m * c);
    }
    return box;
}

bool Bounds::intersects(const Ray& r) const {
    auto checkAxis = [](double origin, double direction, double minVal, double maxVal) {
        double tminNum = minVal - origin;
        double tmaxNum = maxVal - origin;
        double tmin, tmax;
        if (std::abs(direction) >= EPSILON) {
            tmin = tminNum / direction;
            tmax = tmaxNum / direction;
        } else {
            tmin = tminNum * INF;
            tmax = tmaxNum * INF;
        }
        if (tmin > tmax) {
            std::swap(tmin, tmax);
        }
        return std::make_pair(tmin, tmax);
    };

    auto xBounds = checkAxis(r.getOrigin().getX(), r.getDirection().getX(), m_min.getX(), m_max.getX());
    auto yBounds = checkAxis(r.getOrigin().getY(), r.getDirection().getY(), m_min.getY(), m_max.getY());
    auto zBounds = checkAxis(r.getOrigin().getZ(), r.getDirection().getZ(), m_min.getZ(), m_max.getZ());

    double tMin = std::max({xBounds.first, yBounds.first, zBounds.first});
    double tMax = std::min({xBounds.second, yBounds.second, zBounds.second});

    return (tMin <= tMax && tMax >= 0.0);
}

