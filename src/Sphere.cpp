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

Tuple normalAt(const Sphere& s, const Tuple& worldPoint) {
    Tuple objectPoint {s.getTransform().inverse() * worldPoint };
    Tuple objectNormal {objectPoint - point(0,0,0)};
    Tuple worldNormal  {(s.getTransform().inverse().transpose()) * objectNormal};
    return worldNormal.normalize();

}

const Materials& Sphere::getMaterials() const {
    return m_materials;
}

Materials& Sphere::getMaterials() {
    return m_materials;
} 
void Sphere::setMaterials(const Materials& m) {
    m_materials = m;
}

