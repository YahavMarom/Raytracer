#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Shape.h"

class Triangle : public Shape {
private:
    Tuple m_p1 {};
    Tuple m_p2 {};
    Tuple m_p3 {};
    Tuple m_e1 {};
    Tuple m_e2 {};
    Tuple m_normal {};

public:
    Triangle(const Tuple& p1, const Tuple& p2, const Tuple& p3,
            const Color& c = Color(1, 1, 1), 
            double ambient = 0.1, 
            double diffuse = 0.9, 
            double specular = 0.9, 
            double shininess = 200.0, 
            double reflectivity = 0.0,
            double transparency = 0.0,
            double reflectiveIndex = 1.0);
    
    ~Triangle() override = default;
    
    const Tuple& getP1() const { return m_p1; };
    const Tuple& getP2() const { return m_p2; }
    const Tuple& getP3() const { return m_p3; }
    const Tuple& getE1() const { return m_e1; }
    const Tuple& getE2() const { return m_e2; }
    const Tuple& getNormal() const { return m_normal; }

    std::vector<Intersection> localIntersect(const Ray& localRay) const override;
    Tuple localNormalAt(const Tuple& localPoint) const override {return m_normal;} //returns same normal for all points

    Bounds bounds() const override;
};
#endif