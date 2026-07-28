#include "Tuple.h"
#include "Constants.h"
#include <cassert>
#include <cmath>


Tuple::Tuple(double x, double y, double z, double w)
    : m_x {x}
    , m_y {y}
    , m_z {z}
    , m_w {w}
    {
        assert( (m_w == 0.0 || m_w == 1.0) );
    }

bool Tuple::isPoint() const {
    return m_w == 1;
} 

bool Tuple::isVector() const {
    return m_w == 0;
}

double Tuple::size() const {
    return std::sqrt( m_x * m_x + m_y * m_y + m_z * m_z );
}

// must be a vector, but I'm not doing an assert - it's expected from the user to not give bad inputs.
Tuple Tuple::normalize() const {

    
    double mag = size();

    if (mag == 0.0){
        return vector(0,0,0);
    }
    
    return Tuple( m_x / mag, m_y / mag, m_z / mag, 0);
}


Tuple operator+(const Tuple& a, const Tuple& b){
    return Tuple( a.getX() + b.getX(),
                  a.getY() + b.getY(),
                  a.getZ() + b.getZ(),
                  a.getW() + b.getW()
                 );

}
Tuple operator-(const Tuple& a, const Tuple& b){
    return Tuple( a.getX() - b.getX(),
                    a.getY() - b.getY(),
                    a.getZ() - b.getZ(),
                    a.getW() - b.getW()
                    );

}

Tuple operator-(const Tuple& t) {
    return Tuple(-t.getX(), -t.getY(), -t.getZ(), t.getW());
}

Tuple operator*(const double scalar, const Tuple& t) {
    return Tuple(scalar * t.getX(), scalar * t.getY(), scalar * t.getZ(), t.getW() );
}

Tuple operator*(const Tuple& t, const double scalar) {
    return scalar * t;

}

Tuple operator/(const Tuple& t, const double scalar) {
    assert( (scalar != 0.0) );
    return Tuple(
        t.getX() / scalar,
        t.getY() / scalar,
        t.getZ() / scalar, 
        t.getW()
    );
}

bool operator==(const Tuple& a, const Tuple& b) {
    
    return (a - b).size() < EPSILON && a.getW() == b.getW();
}

double dot(const Tuple& a, const Tuple& b){
    assert(a.getW() == 0 && b.getW() == 0);
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}
Tuple cross(const Tuple& a, const Tuple& b) {
    assert(a.getW() == 0 && b.getW() == 0);
    return Tuple(
                a.getY() * b.getZ() - a.getZ() * b.getY(),
                a.getZ() * b.getX() - a.getX() * b.getZ(),
                a.getX() * b.getY() - a.getY() * b.getX(),
                0 
        );

}


Tuple point(double x, double y, double z) {
    return Tuple(x, y, z, 1);
}
Tuple vector(double x, double y, double z) {
    return Tuple(x, y, z, 0);
}

Tuple reflect(const Tuple& inVec, const Tuple& normalVec) {
    return {inVec - normalVec * 2 * dot(inVec, normalVec)};
}



std::ostream& operator<<(std::ostream& os, const Tuple& t) 
{
    os << "(" << t.getX() << ", " << t.getY() << ", " << t.getZ() << ", " << t.getW() << ")";
    return os;
}

