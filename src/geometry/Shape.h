#ifndef SHAPE_H
#define SHAPE_H

#include "Matrix.h"
#include "Materials.h"
#include "Ray.h"
#include "Intersections.h"
#include "Transformations.h"
#include <vector>

class Shape {

protected: 
    Matrix m_transform {Matrix::Identity};
    Matrix m_inverseTransform{Matrix::Identity};
    Matrix m_inverseTranspose{Matrix::Identity};

    Materials m_materials{};


    Shape() = default;

    explicit Shape(const Materials& m)
    : m_materials {m}
    {}


public:
    virtual ~Shape() = default;

    void setTransform(const Matrix& t);

    const Matrix& getTransform() const {return m_transform;}
    const Matrix& getInverseTransform() const {return m_inverseTransform;}
    const Matrix& getInverseTranspose() const {return m_inverseTranspose;}

    void setMaterials(const Materials& m) {m_materials = m;}
    const Materials& getMaterials() const {return m_materials;}
    Materials& getMaterials() {return m_materials;}

    std::vector<Intersection> intersect(const Ray& r) const;
    Tuple normalAt(const Tuple& worldPoint) const;

    
    virtual std::vector<Intersection> localIntersect(const Ray& localRay) const = 0;
    virtual Tuple localNormalAt(const Tuple& localPoint) const = 0;


};

bool operator==(const Shape& a, const Shape& b);
bool operator!=(const Shape& a, const Shape& b);




class TestShape : public Shape {
public:
    // mutable allows modification inside the const localIntersect method
    mutable Ray saved_ray{ point(0, 0, 0), vector(0, 0, 0) };

    TestShape() = default;
    ~TestShape() override = default;

    std::vector<Intersection> localIntersect(const Ray& localRay) const override {
        saved_ray = localRay;
        return {};
    }

    Tuple localNormalAt(const Tuple& localPoint) const override {
        return vector(localPoint.getX(), localPoint.getY(), localPoint.getZ());
    }
};


#endif