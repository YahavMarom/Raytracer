#ifndef PATTERN_H
#define PATTERN_H



#include "Color.h"
#include "Matrix.h"
#include "Tuple.h"

class Shape;


class Pattern {

protected:
    Color m_firstColor {Color::Black};
    Color m_secondColor {Color::White};
    Matrix m_transform {Matrix::Identity};
    Matrix m_inverseTransform{Matrix::Identity};



    Pattern() = default;
    Pattern(const Color& a, const Color& b)
        : m_firstColor{a}
        , m_secondColor{b}
        {}

public:
    virtual ~Pattern() = default;

    void setTransform(const Matrix& t) {
        m_transform = t;
        m_inverseTransform = t.inverse();
    }

    const Matrix& getTransform() const {
        return m_transform;
    }
    const Matrix& getInverseTransform() const {
        return m_inverseTransform;
    }

    const Color& getFirstColor() const { return m_firstColor; }
    const Color& getSecondColor() const { return m_secondColor; }

    Color patternAtShape(const Shape& shape, const Tuple& worldPoint) const;

    virtual Color patternAt(const Tuple& patternPoint) const = 0;


};



class StripePattern : public Pattern{

public:
    StripePattern() = default;
    
    StripePattern(const Color& a, const Color& b) 
    : Pattern{a, b}
    {}

    Color patternAt(const Tuple& patternPoint) const override;



};


class GradientPattern : public Pattern {
public:
    GradientPattern() = default;
    
    GradientPattern(const Color& a, const Color& b) 
    : Pattern{a, b}
    {}

    Color patternAt(const Tuple& patternPoint) const override;

    
};

class RingPattern : public Pattern {
public:
    RingPattern() = default;
    
    RingPattern(const Color& a, const Color& b) 
    : Pattern{a, b}
    {}

    Color patternAt(const Tuple& patternPoint) const override;

    
};



class Checker3DPattern : public Pattern {
public:
    Checker3DPattern() = default;
    
    Checker3DPattern(const Color& a, const Color& b) 
    : Pattern{a, b}
    {}

    Color patternAt(const Tuple& patternPoint) const override;

    
};


#endif