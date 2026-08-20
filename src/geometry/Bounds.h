#ifndef BOUNDS_H
#define BOUNDS_H

#include "Tuple.h"
#include "Ray.h"
#include "Matrix.h"
#include "Constants.h"

class Bounds {

private:
    Tuple m_min;
    Tuple m_max;

public:

    Bounds();
    Bounds(const Tuple& minPoint, const Tuple& maxPoint);

    const Tuple& getMin() const { return m_min; }
    const Tuple& getMax() const { return m_max; }

    void insert(const Tuple& p);
    void insert(const Bounds& b);
    Bounds transform(const Matrix& m) const;
    bool intersects(const Ray& r) const;
};

Bounds merge(const Bounds& b1, const Bounds& b2);


#endif