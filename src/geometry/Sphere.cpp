#include "Sphere.h"

  
Sphere::Sphere(const Color& c, double ambient, double diffuse, double specular, double shininess, double reflectivity,
                double transparency, double reflectiveIndex) 
    : Shape(
                Materials(c, ambient, diffuse, specular, shininess,
                        reflectivity, transparency, reflectiveIndex)
            ) 
{
}


std::vector<Intersection> Sphere::localIntersect(const Ray& localRay) const {
    Tuple sphere_to_ray = localRay.getOrigin() - point(0.0, 0.0, 0.0);

    double a = dot(localRay.getDirection(), localRay.getDirection());
    double b = 2.0 * dot(localRay.getDirection(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1.0;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return {};
    }

    double sqrt_d = std::sqrt(discriminant);
    double t1 = (-b - sqrt_d) / (2.0 * a);
    double t2 = (-b + sqrt_d) / (2.0 * a);

    if (t1 > t2) {
        std::swap(t1, t2);
    }

    return { Intersection{t1, this}, Intersection{t2, this} };
}

Tuple Sphere::localNormalAt(const Tuple& localPoint) const {
    return localPoint - point(0.0, 0.0, 0.0);
}


Bounds Sphere::bounds() const {
    return Bounds(point(-1, -1, -1), point(1, 1, 1));
}