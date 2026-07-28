#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>

class Tuple 
{
private: 
    double m_x {};
    double m_y {};
    double m_z {};
    double m_w {}; // 0 for vector, 1 for point


public:
    Tuple(double x, double y, double z, double w);
    
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }
    double getW() const { return m_w; }

    bool isPoint() const;
    bool isVector() const;

    double size() const;
    Tuple normalize() const;


};

Tuple operator+(const Tuple& a, const Tuple& b);
Tuple operator-(const Tuple& a, const Tuple& b);
Tuple operator-(const Tuple& a);
Tuple operator*(const Tuple& t, const double scalar);
Tuple operator*(const double scalar, const Tuple& t);
Tuple operator/(const Tuple& t, const double scalar);
Tuple operator/(const double scalar, const Tuple& t);
bool operator==(const Tuple& a, const Tuple& b);

double dot(const Tuple& a, const Tuple& b);
Tuple cross(const Tuple& a, const Tuple& b);

Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);

Tuple reflect(const Tuple& inVec, const Tuple& normalVec);

std::ostream& operator<<(std::ostream& os, const Tuple& t);



#endif