#ifndef SPHERE_H
#define SPHERE_H

#include "Matrix.h"
#include "Materials.h"
#include <iostream>

class Sphere {

private:
    int m_id;
    static int m_nextId; 
    Matrix m_transform {Matrix::identity()};
    Materials m_materials {};


public:
    Sphere();
    int getID() const;
    void setTransform(const Matrix& t);
    const Matrix& getTransform() const;

    const Materials& getMaterials() const;
    Materials& getMaterials();
    void setMaterials(const Materials& m);

};


bool operator==(const Sphere& a, const Sphere& b);

Tuple normalAt(const Sphere& s, const Tuple& worldPoint);




#endif