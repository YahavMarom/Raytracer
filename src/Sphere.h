#ifndef SPHERE_H
#define SPHERE_H

#include "Matrix.h"

class Sphere {

private:
    int m_id;
    static int m_nextId; 
    Matrix m_transform {Matrix::identity()};


public:
    Sphere();
    int getID() const;
    void setTransform(const Matrix& t);
    const Matrix& getTransform() const;


};


bool operator==(const Sphere& a, const Sphere& b);


#endif