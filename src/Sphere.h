#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Color.h"

class Sphere : public Shape {
public:
    // Only the signature is declared in the header
    Sphere(const Color& c = Color(1, 1, 1), 
           double ambient = 0.1, 
           double diffuse = 0.9, 
           double specular = 0.9, 
           double shininess = 200.0, 
           double reflectivity = 0.0,
           double transparency = 0.0,
           double reflectiveIndex = 1.0);

           
    ~Sphere() override = default;

    std::vector<Intersection> localIntersect(const Ray& localRay) const override;
    Tuple localNormalAt(const Tuple& localPoint) const override;
};

#endif