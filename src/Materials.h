#ifndef MATERIALS_H
#define MATERIALS_H

#include "Color.h"
#include "Light.h"

class Materials {

private:
    Color m_color {Color(1, 1, 1)};
    double m_ambient {0.1};
    double m_diffuse {0.9};
    double m_specular {0.9};
    double m_shininess {200.0};

public:
    Materials() = default;
    Materials(const Color& c, double ambient, double diffuse, double specular, double shininess);
    
    const Color& getColor() const { return m_color; }
    double getAmbient() const { return m_ambient; }
    double getDiffuse() const { return m_diffuse; }
    double getSpecular() const { return m_specular; }
    double getShininess() const { return m_shininess; }

    void setColor(const Color& c) { m_color = c; }
    void setAmbient(double a) { m_ambient = a; }
    void setDiffuse(double d) { m_diffuse = d; }
    void setSpecular(double s) { m_specular = s; }
    void setShininess(double s) { m_shininess = s; }
};


bool operator==(const Materials& a, const Materials& b);

Color lighting(const Materials& m, const pointLight& light, const Tuple& position,
                const Tuple& eyeVec, const Tuple& normalVec);


#endif