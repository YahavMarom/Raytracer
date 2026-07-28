#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
private:
    double m_red {};
    double m_green {};
    double m_blue {};

public:
    Color(double red, double green, double blue);

    double getRed() const {return m_red; }
    double getGreen() const {return m_green; }
    double getBlue() const {return m_blue; }


};



Color operator+(const Color& a, const Color& b);
Color operator-(const Color& a, const Color& b);
Color operator*(const double scalar, const Color& c);
Color operator*(const Color& c, const double scalar);
Color operator*(const Color& a, const Color& b);

std::ostream& operator<<(std::ostream& os, const Color& c); 


#endif