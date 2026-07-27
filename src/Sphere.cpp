#include "Sphere.h"


int Sphere::m_nextId {0};

Sphere::Sphere()
    : m_id {m_nextId++}
    {

    }
int Sphere::getID() const {
    return m_id;
}


bool operator==(const Sphere& a, const Sphere& b) {
    return (a.getID() == b.getID());
}

