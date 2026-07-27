#include "Ray.h"

Ray::Ray(const Tuple& origin, const Tuple& direction)
    : m_origin {origin}
    , m_direction {direction}
    {

    }

const Tuple& Ray::getOrigin() const {
    return m_origin;
}

const Tuple& Ray::getDirection() const {
    return m_direction;
}

Tuple Ray::getPosition(double time) const{
    return m_origin + m_direction * time;

}