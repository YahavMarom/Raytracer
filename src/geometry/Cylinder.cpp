#include "Cylinder.h"



Cylinder::Cylinder(const Color& c, double ambient, double diffuse, double specular, double shininess, double reflectivity,
                double transparency, double reflectiveIndex) 
    : Shape(
                Materials(c, ambient, diffuse, specular, shininess,
                        reflectivity, transparency, reflectiveIndex)
            )

{
}

bool Cylinder::checkCap(const Ray& ray, double t) const{
    double x {ray.getOrigin().getX() + t * ray.getDirection().getX()};
    double z {ray.getOrigin().getZ() + t * ray.getDirection().getZ()};

    return (x * x + z * z <= 1.0);
}

void Cylinder::intersectCaps(const Ray& ray, std::vector<Intersection>& xs) const{
    if (!m_closed || std::abs(ray.getDirection().getY()) < EPSILON) {
        return;
    }

    // intersection with possibly the lower end cap
    double t { (getMin() - ray.getOrigin().getY() ) / ray.getDirection().getY() };
    if (checkCap(ray, t)) {
        xs.push_back(getIntersect(t, *this));
    }

    t = (getMax() - ray.getOrigin().getY() ) / ray.getDirection().getY() ;
    if (checkCap(ray, t)) {
        xs.push_back(getIntersect(t, *this));
    }


}


std::vector<Intersection> Cylinder::localIntersect(const Ray& localRay) const { 
    double a {std::pow(localRay.getDirection().getX(), 2) + std::pow(localRay.getDirection().getZ(), 2) };
    std::vector<Intersection> xs = {};

    if (std::abs(a) < EPSILON) {
        intersectCaps(localRay, xs);
        return xs;
    }

    double b {2 * (localRay.getOrigin().getX() * localRay.getDirection().getX() + 
                   localRay.getOrigin().getZ() * localRay.getDirection().getZ() )
            };
    double c {std::pow(localRay.getOrigin().getX(), 2) + std::pow(localRay.getOrigin().getZ(), 2) - 1.0  };

    double disc {b * b - 4.0 * a * c};

    if (disc < 0.0) {
        return {};
    }
    double t0 {(-b - std::sqrt(disc)) / (2.0 * a)};
    double t1 {(-b + std::sqrt(disc)) / (2.0 * a)};
    if (t0 > t1) {
        std::swap(t0, t1);
    }
    

    
    double y0 {localRay.getOrigin().getY() + t0 * localRay.getDirection().getY()};
    if (m_min < y0 && y0 < m_max) {
        xs.push_back(getIntersect(t0, *this));
    }

    double y1 {localRay.getOrigin().getY() + t1 * localRay.getDirection().getY()};

    if (m_min < y1 && y1 < m_max) {
        xs.push_back(getIntersect(t1, *this));
    }

    intersectCaps(localRay, xs);
    return xs;


}

Tuple Cylinder::localNormalAt(const Tuple& localPoint) const {
    double dist {localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ()  };

    if (dist < 1.0 && localPoint.getY() >= m_max - EPSILON) {
        return vector(0, 1, 0);
    }

    if (dist < 1.0 && localPoint.getY() <= m_min + EPSILON) {
        return vector(0, -1, 0);
    }
    return vector(localPoint.getX(), 0.0, localPoint.getZ() ) ;

}