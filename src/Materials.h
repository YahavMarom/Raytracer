#ifndef MATERIALS_H
#define MATERIALS_H

#include "Color.h"
#include "Light.h"
#include "Pattern.h"
#include <memory>

class Materials {

private:
    Color m_color {Color(1, 1, 1)};
    double m_ambient {0.1};
    double m_diffuse {0.9};
    double m_specular {0.9};
    double m_shininess {200.0};
    double m_reflectivity {0.0};

    std::shared_ptr<const Pattern> m_pattern {nullptr};




public:
    Materials() = default;
    Materials(const Color& c, double ambient, double diffuse, double specular, double shininess, double reflectivity);
    
    const Color& getColor() const { return m_color; }
    double getAmbient() const { return m_ambient; }
    double getDiffuse() const { return m_diffuse; }
    double getSpecular() const { return m_specular; }
    double getShininess() const { return m_shininess; }
    double getReflectivity() const { return m_reflectivity; }
    const std::shared_ptr<const Pattern>& getPattern() const { return m_pattern; }


    void setColor(const Color& c) { m_color = c; }
    void setAmbient(double a) { m_ambient = a; }
    void setDiffuse(double d) { m_diffuse = d; }
    void setSpecular(double s) { m_specular = s; }
    void setShininess(double s) { m_shininess = s; }
    void setReflectivity(double s) {m_reflectivity = s; }
    void setPattern(std::shared_ptr<const Pattern> pattern) { m_pattern = std::move(pattern); }

    
    bool hasPattern() const { return m_pattern != nullptr; }
};


Color lighting(const Materials& m, const Shape& s, const pointLight& light, const Tuple& position,
                const Tuple& eyeVec, const Tuple& normalVec, bool isShadowed);


#endif