#include "Intersections.h"
#include "Constants.h"
#include "World.h"
#include "Transformations.h"
#include "Shape.h"
#include <cmath>
#include <algorithm>

Intersection getIntersect(double t, const Shape& s) {
    return Intersection{t, &s};
}

std::vector<Intersection> intersections(std::initializer_list<Intersection> list){
    std::vector<Intersection> xs {list};
    std::sort(xs.begin(), xs.end(),
                [](const Intersection& a, const Intersection& b) {
                    return a.t < b.t;
                }
            );
    return xs;
}

std::optional<Intersection> hit(const std::vector<Intersection>& xs) {
    for (const auto& i : xs) {
        if (i.t >= 0) {
            return i;
        }
    }
    return std::nullopt;
}

Comp prepareComputations(const Intersection& I, const Ray& ray, const std::vector<Intersection>& xs) {
    Tuple pos {ray.getPosition(I.t)};

    Comp res{};
    res.t = I.t;
    res.object = I.object;
    res.point = pos;
    res.eyeVec = -ray.getDirection();
    res.normVec = I.object->normalAt(pos);
    res.inside = false;

    if (dot(res.normVec, res.eyeVec) < 0.0) {
        res.inside = true;
        res.normVec = -res.normVec;
    }
    res.overPoint = res.point + res.normVec * EPSILON;
    res.underPoint = res.point - res.normVec * EPSILON;
    res.reflectVec = reflect(ray.getDirection(), res.normVec);


    const std::vector<Intersection>& intersectionsList = xs.empty() ? std::vector<Intersection>{I} : xs;

    std::vector<const Shape*> containers{};

    for (const auto& i : intersectionsList) {
        const bool isHit {i == I};

        if (isHit) {
            if (containers.empty()) {
                res.n1 = 1.0;
            }
            else {
                res.n1 = containers.back()->getMaterials().getReflectiveIndex();
            }
        }

        auto it = std::find(containers.begin(), containers.end(), i.object);
        if (it != containers.end()) {
            containers.erase(it);
        } else {
            containers.push_back(i.object);
        }

        if (isHit) {
            if (containers.empty()) {
                res.n2 = 1.0;
            } else {
                res.n2 = containers.back()->getMaterials().getReflectiveIndex();
            }
            break;
        }


    }

    return res;
}

// approximation to Fresnel
double schlick(const Comp& comps) {
    double cos {dot(comps.eyeVec, comps.normVec)};

    if (comps.n1 > comps.n2 ){
        double n {comps.n1 / comps.n2};
        
        double sin2_t {(n * n) * (1.0 - cos * cos) };

        if (sin2_t > 1.0) {
            return 1.0;
        }

        cos = std::sqrt(1.0 - sin2_t) ;
    }

    double r_theta {std::pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2) };
    return r_theta + (1.0 - r_theta) * std::pow(1.0 - cos, 5);
}