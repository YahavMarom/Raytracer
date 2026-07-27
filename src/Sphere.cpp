#include "Sphere.h"


int Sphere::m_nextId {0};

Sphere::Sphere()
    : m_id {m_nextId++}
    {

    }
int Sphere::getID() const {
    return m_id;
}

const Matrix& Sphere::getTransform() const {
    return m_transform;
}

void Sphere::setTransform(const Matrix& t) {
    m_transform = t;
}

bool operator==(const Sphere& a, const Sphere& b) {
    return (a.getID() == b.getID());
}

