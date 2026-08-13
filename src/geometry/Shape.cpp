#include "Shape.h"

void Shape::setTransform(const Matrix& transform) {
    m_transform = transform;
    m_inverseTransform = m_transform.inverse();
    m_inverseTranspose = m_inverseTransform.transpose();
}

std::vector<Intersection> Shape::intersect(const Ray& worldRay) const {
    const Ray localRay{ transform(worldRay, m_inverseTransform) };
    return localIntersect(localRay);
}

Tuple Shape::normalAt(const Tuple& worldPoint) const {
    const Tuple objectPoint{ m_inverseTransform * worldPoint };
    const Tuple objectNormal{ localNormalAt(objectPoint) };

    Tuple worldNormal{ m_inverseTranspose * objectNormal };
    worldNormal.setW(0.0);
    return worldNormal.normalize();
}

bool operator==(const Shape& a, const Shape& b) {
    return &a == &b;
}

bool operator!=(const Shape& a, const Shape& b) {
    return !(a==b);
}


