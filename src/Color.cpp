#include "Color.h"
#include "Constants.h"


Color::Color(double red, double green, double blue)
    : m_red {red}
    , m_green {green}
    , m_blue {blue}
    {}

Color operator+(const Color& a, const Color& b) {
    return Color(
        a.getRed() + b.getRed(),
        a.getGreen() + b.getGreen(),
        a.getBlue() + b.getBlue()
    );
}

Color operator-(const Color& a, const Color& b) {
    return Color(
        a.getRed() - b.getRed(),
        a.getGreen() - b.getGreen(),
        a.getBlue() - b.getBlue()
    );
}

Color operator*(double const scalar, const Color& c) {
    return Color(
        scalar * c.getRed(),
        scalar * c.getGreen(),
        scalar * c.getBlue()
    );
}

Color operator*(const Color& c, double const scalar) {
    return scalar * c;
}

Color operator*(const Color& a, const Color& b) {
    return Color(
        a.getRed() * b.getRed(),
        a.getGreen() * b.getGreen(),
        a.getBlue() * b.getBlue()
    );
}

bool operator==(const Color& a, const Color& b) {
    Color c {a - b};
    return std::abs(c.getRed()) < EPSILON &&
           std::abs(c.getGreen()) < EPSILON &&
           std::abs(c.getBlue()) < EPSILON;
}


std::ostream& operator<<(std::ostream& os, const Color& c) {

    os << "Red: " << c.getRed() << "\n";
    os << "Green: " << c.getGreen() << "\n";
    os << "Blue: " << c.getBlue() << "\n";

    return os;

}