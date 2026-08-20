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

Tuple Shape::worldToObject(const Tuple& worldPoint) const {
    Tuple point {worldPoint};

    if (m_parent != NULL) {
        point = m_parent->worldToObject(worldPoint);
    }
    return m_inverseTransform * point;
}

Tuple Shape::normalToWorld(const Tuple& localNormal) const {
    Tuple normal {m_inverseTranspose * localNormal};
    normal.setW(0.0);
    normal = normal.normalize();
    
    if (m_parent != NULL) {
        normal = m_parent->normalToWorld(normal);
    }
    return normal;

}



Tuple Shape::normalAt(const Tuple& worldPoint) const {
    const Tuple localPoint{ worldToObject(worldPoint) };
    const Tuple localNormal { localNormalAt(localPoint) };

    return normalToWorld(localNormal);
}

bool operator==(const Shape& a, const Shape& b) {
    return &a == &b;
}

bool operator!=(const Shape& a, const Shape& b) {
    return !(a==b);
}


