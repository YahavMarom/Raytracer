#include "Pattern.h"
#include "Shape.h"
#include "Constants.h"
#include <cmath>

Color Pattern::patternAtShape(const Shape& s, const Tuple& worldPoint) const {
    const Tuple objectPoint = s.getInverseTransform() * worldPoint;
    const Tuple patternPoint = m_inverseTransform * objectPoint;
    return patternAt(patternPoint);
}

Color StripePattern::patternAt(const Tuple& patternPoint) const {
    if (static_cast<int>(std::floor(patternPoint.getX() + EPSILON)) % 2 == 0) {
        return m_firstColor;
    }
    return m_secondColor;
}

Color GradientPattern::patternAt(const Tuple& patternPoint) const {
    const Color distance = m_secondColor - m_firstColor;
    const double frac = patternPoint.getX() - std::floor(patternPoint.getX() + EPSILON);
    return m_firstColor + distance * frac;
}

Color RingPattern::patternAt(const Tuple& patternPoint) const {
    const double distance = std::sqrt(patternPoint.getX() * patternPoint.getX() +
                                      patternPoint.getZ() * patternPoint.getZ());
    if (static_cast<int>(std::floor(distance + EPSILON)) % 2 == 0) {
        return m_firstColor;
    }
    return m_secondColor;
}

Color Checker3DPattern::patternAt(const Tuple& patternPoint) const {
    const int sum = static_cast<int>(std::floor(patternPoint.getX() + EPSILON)) +
                    static_cast<int>(std::floor(patternPoint.getY() + EPSILON)) +
                    static_cast<int>(std::floor(patternPoint.getZ() + EPSILON));
    if (sum % 2 == 0) {
        return m_firstColor;
    }
    return m_secondColor;
}