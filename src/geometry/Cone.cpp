#include "Cone.h"



Cone::Cone(const Color& c, double ambient, double diffuse, double specular, double shininess, double reflectivity,
                double transparency, double reflectiveIndex) 
    : Shape(
                Materials(c, ambient, diffuse, specular, shininess,
                        reflectivity, transparency, reflectiveIndex)
            )

{
}

bool Cone::checkCap(const Ray& ray, double t) const{
    double x {ray.getPosition(t).getX()};
    double z {ray.getPosition(t).getZ()};

    return (x * x + z * z <= 1.0);
}

void Cone::intersectCaps(const Ray& ray, std::vector<Intersection>& xs) const{
    if (!m_closed || std::abs(ray.getDirection().getY()) < EPSILON) {
        return;
    }

    // intersection with possibly the lower end cap
    double t { (getMin() - ray.getOrigin().getY() ) / ray.getDirection().getY() };
    if (checkCap(ray, t)) {
        xs.push_back(getIntersect(t, *this));
    }

    // with upper end cap
    t = (getMax() - ray.getOrigin().getY() ) / ray.getDirection().getY() ;
    if (checkCap(ray, t)) {
        xs.push_back(getIntersect(t, *this));
    }


}


std::vector<Intersection> Cone::localIntersect(const Ray& localRay) const { 

    double a {std::pow(localRay.getDirection().getX(), 2) -
            std::pow(localRay.getDirection().getY(), 2) +
                std::pow(localRay.getDirection().getZ(), 2) };

    double b {2 * (localRay.getOrigin().getX() * localRay.getDirection().getX() -
                    localRay.getOrigin().getY() * localRay.getDirection().getY() +
                   localRay.getOrigin().getZ() * localRay.getDirection().getZ() )
            };

    double c {std::pow(localRay.getOrigin().getX(), 2) -
            std::pow(localRay.getOrigin().getY(), 2) +
            std::pow(localRay.getOrigin().getZ(), 2)  };

    std::vector<Intersection> xs = {};

    if (std::abs(a) < EPSILON) {
        if (std::abs(b) > EPSILON) {
            
            double t {- c / (2.0 * b) };
            double y {localRay.getPosition(t).getY()};
            if (m_min < y && y < m_max){
                xs.push_back(getIntersect(t, *this));
            }

        }
        intersectCaps(localRay, xs);
        return xs;
        
    
    }


    

    double disc {b * b - 4.0 * a * c};

    if (disc < 0.0) {
        intersectCaps(localRay, xs);
        return xs;
    }

    double t0 {(-b - std::sqrt(disc)) / (2.0 * a)};
    double t1 {(-b + std::sqrt(disc)) / (2.0 * a)};
    if (t0 > t1) {
        std::swap(t0, t1);
    }
    

    
    double y0 {localRay.getPosition(t0).getY()};
    if (m_min < y0 && y0 < m_max) {
        xs.push_back(getIntersect(t0, *this));
    }

    double y1 {localRay.getPosition(t1).getY()};

    if (m_min < y1 && y1 < m_max) {
        xs.push_back(getIntersect(t1, *this));
    }

    intersectCaps(localRay, xs);
    return xs;


}

Tuple Cone::localNormalAt(const Tuple& localPoint) const {
    double dist {localPoint.getX() * localPoint.getX() + localPoint.getZ() * localPoint.getZ()  };

   if (dist < (m_max * m_max) && localPoint.getY() >= m_max - EPSILON) {
        return vector(0, 1, 0);
    }

    if (dist < (m_min * m_min) && localPoint.getY() <= m_min + EPSILON) {
        return vector(0, -1, 0);
    }

    double y {std::sqrt(dist)};
    if (localPoint.getY() > 0.0) {
        y = -y;
    }

    return vector(localPoint.getX(), y, localPoint.getZ());

}


Bounds Cone::bounds() const {
    double maxDist = std::max(std::abs(m_min), std::abs(m_max));
    return Bounds(point(-maxDist, m_min, -maxDist), point(maxDist, m_max, maxDist));
}