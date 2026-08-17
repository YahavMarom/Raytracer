#ifndef CYLINDER_H
#define CYLINDER_H


#include "Shape.h"
#include "Color.h"
#include "Constants.h"

// unit cylinder - radius is 1, the unit circle on xz
class Cylinder : public Shape {

private:
    double m_min {-INF};
    double m_max {INF};
    bool m_closed {false};
public:
    // Only the signature is declared in the header


    Cylinder(const Color& c = Color(1, 1, 1), 
           double ambient = 0.1, 
           double diffuse = 0.9, 
           double specular = 0.9, 
           double shininess = 200.0, 
           double reflectivity = 0.0,
           double transparency = 0.0,
           double reflectiveIndex = 1.0);

           
    ~Cylinder() override = default;

    double getMin() const {return m_min;}
    double getMax() const {return m_max;}
    bool getClosed() const {return m_closed;}

    void setMin(double minimum) {m_min = minimum;}
    void setMax(double maximum) {m_max = maximum;}
    void setClosed(bool val) {m_closed = val;}


    bool checkCap(const Ray& ray, double t) const;
    void intersectCaps(const Ray& ray, std::vector<Intersection>& xs) const;
    std::vector<Intersection> localIntersect(const Ray& localRay) const override;
    Tuple localNormalAt(const Tuple& localPoint) const override;

    bool checkCap(const Ray& ray, double t);
};

#endif
