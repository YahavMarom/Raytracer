#include "Materials.h"
#include "Tuple.h"

Materials::Materials(const Color& c, double ambient, double diffuse, double specular, double shininess)
    : m_color {c}
    , m_ambient {ambient}
    , m_diffuse {diffuse}
    , m_specular {specular}
    , m_shininess {shininess}
    {

    }

Color lighting(const Materials& m, const pointLight& light, const Tuple& position,
                const Tuple& eyeVec, const Tuple& normalVec, bool isShadowed) {
                    Color effective_color {m.getColor() * light.intensity};
                    Color ambient = effective_color * m.getAmbient();

                    if (isShadowed) {
                        return ambient;
                    }
                    
                    Tuple lightVec { (light.position - position).normalize() };
                    Color diffuse(0,0,0);
                    Color specular(0,0,0);
                    
                    double light_dot_normal {dot(lightVec, normalVec)};
                    if (light_dot_normal >= 0) {
                        diffuse = effective_color * m.getDiffuse() * light_dot_normal;

                        Tuple reflectVec {reflect(-lightVec, normalVec)};
                        double reflect_dot_eye {dot(reflectVec, eyeVec)};

                        if (reflect_dot_eye > 0) {
                            double factor {std::pow(reflect_dot_eye, m.getShininess())};
                            specular = light.intensity * m.getSpecular() * factor;

                        }
                    }
                    return ambient + diffuse + specular;

                }
