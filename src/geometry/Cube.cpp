#include "Cube.h"
#include "Constants.h"
#include <algorithm>
Cube::Cube(const Color& c, double ambient, double diffuse, double specular, double shininess, double reflectivity,
                double transparency, double reflectiveIndex)
            : Shape(
                Materials(c, ambient, diffuse, specular, shininess,
                        reflectivity, transparency, reflectiveIndex)
            ) 
            {}



std::array<double, 2> Cube::checkAxis(double cordRayOrigin, double cordRayDirection) const {
    double tminNumerator {-1 - cordRayOrigin};
    double tmaxNumerator {1 - cordRayOrigin};
    double tmin {};
    double tmax {};
    if (std::abs(cordRayDirection) >= EPSILON ) {
        tmin = tminNumerator / cordRayDirection;
        tmax = tmaxNumerator / cordRayDirection;
    }
    else {
        tmin = tminNumerator * INF;
        tmax = tmaxNumerator * INF;
    }
    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }
    return {tmin, tmax};
}

std::vector<Intersection> Cube::localIntersect(const Ray& localRay) const {
    
    auto xBounds {checkAxis(localRay.getOrigin().getX(), localRay.getDirection().getX() ) };
    double xtMin {xBounds[0]};
    double xtMax {xBounds[1]};

    auto yBounds {checkAxis(localRay.getOrigin().getY(), localRay.getDirection().getY() ) };
    double ytMin {yBounds[0]};
    double ytMax {yBounds[1]};


    auto zBounds {checkAxis(localRay.getOrigin().getZ(), localRay.getDirection().getZ() ) };
    double ztMin {zBounds[0]};
    double ztMax {zBounds[1]};


    double tMin {std::max({xtMin, ytMin, ztMin})};
    double tMax {std::min({xtMax, ytMax, ztMax})};
    if (tMin > tMax) {
        return {};
    }
    return {getIntersect(tMin, *this), getIntersect(tMax, *this) } ;
    
    

}

Tuple Cube::localNormalAt(const Tuple& localPoint) const {
    double maxC {std::max(
                        {std::abs(localPoint.getX()),
                        std::abs(localPoint.getY()), 
                        std::abs(localPoint.getZ())
                        }
                    )   
                };

    if (maxC == std::abs(localPoint.getX())) {
        return vector(localPoint.getX(), 0, 0);
    }
    else if (maxC == std::abs(localPoint.getY())) {
        return vector(0, localPoint.getY(), 0);
    }
    return vector(0, 0, localPoint.getZ());
}