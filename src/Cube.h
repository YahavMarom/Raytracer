#ifndef CUBE_H
#define CUBE_H


#include "Shape.h"
#include "Color.h"
#include <array>

// unit cube - the cube [-1, 1] ^ 3

class Cube : public Shape {
public:
    // Only the signature is declared in the header
    Cube(const Color& c = Color(1, 1, 1), 
           double ambient = 0.1, 
           double diffuse = 0.9, 
           double specular = 0.9, 
           double shininess = 200.0, 
           double reflectivity = 0.0,
           double transparency = 0.0,
           double reflectiveIndex = 1.0);

           
    ~Cube() override = default;


    std::array<double, 2> checkAxis(double cordRayOrigin, double cordRayDirection) const;
    std::vector<Intersection> localIntersect(const Ray& localRay) const override;
    Tuple localNormalAt(const Tuple& localPoint) const override;
    
};

#endif