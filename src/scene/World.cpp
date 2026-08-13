#include "World.h"
#include "Sphere.h"
#include "Constants.h"
#include "Transformations.h"
#include <algorithm>

World defaultWorld() {
    World w;

    w.setLight(pointLight(point(-10, 10, -10), Color(1, 1, 1)));

    auto s1 = std::make_shared<Sphere>();
    Materials m1;
    m1.setColor(Color(0.8, 1.0, 0.6));
    m1.setDiffuse(0.7);
    m1.setSpecular(0.2);
    s1->setMaterials(m1);
    w.addObject(s1);

    auto s2 = std::make_shared<Sphere>();
    s2->setTransform(scaling(0.5, 0.5, 0.5));
    w.addObject(s2);

    return w;
}

std::vector<Intersection> intersect_world(const World& w, const Ray& ray) {
    std::vector<Intersection> world_intersections {};

    for (const auto& object : w.getObjects()) {
        auto xs {object->intersect(ray)};
        
        for (const auto& i : xs) {
            world_intersections.push_back(i);
        }
    }

    std::sort(world_intersections.begin(), world_intersections.end(),
        [](const Intersection& a, const Intersection& b) {
            return a.t < b.t;
        }
    );
    
    return world_intersections;
}

bool isShadowed(const World& w, const Tuple& p, const pointLight& light) {
    Tuple v {light.position - p};
    double distance {v.size()};
    Tuple direction {v.normalize()};

    Ray r(p, direction);

    auto xs {intersect_world(w, r)};
    auto i {hit(xs)};
    if (i.has_value() && i->t < distance) {
        return true;
    }
    return false;
}

Color shadeHit(const World& w, const Comp& comp, int remaining) {
    const Materials& mat = comp.object->getMaterials();
    Color surface(0, 0, 0);

    for (const auto& light : w.getLights()) {
        bool shadow {isShadowed(w, comp.overPoint, light)};
        surface = surface + lighting(mat, *(comp.object), light, comp.point, comp.eyeVec, comp.normVec, shadow);
    }
    
    Color reflected {reflectedColor(w, comp, remaining)};
    Color refracted { refractedColor(w, comp, remaining)};

    if (mat.getTransparancy() > 0.0 && mat.getReflectivity() > 0.0) {
        double reflectance {schlick(comp)};
        return surface + reflected * reflectance + refracted * (1.0 - reflectance);
    }
    return surface + reflected + refracted;
}   


Color colorAt(const World& w, const Ray& ray, int remaining) {
    auto world_intersections {intersect_world(w, ray)};
    auto xs {hit(world_intersections)};
    if (xs.has_value()) {
        Comp comp {prepareComputations(*xs, ray, world_intersections)};
        return shadeHit(w, comp, remaining);
    }
    else {
        return Color::Black;
    }
}



Color reflectedColor(const World& w, const Comp& computations, int remaining) {
    if (remaining <= 0) {
        return Color::Black;
    }
    double t {computations.object->getMaterials().getReflectivity()};
    if (t < EPSILON) {
        return Color::Black;
    }

    Ray reflectedRay {Ray(computations.overPoint, computations.reflectVec)};
    Color c {colorAt(w, reflectedRay, remaining - 1)};

    return c * t;

}

Color refractedColor(const World& w, const Comp& computations, int remaining) {
    if (computations.object->getMaterials().getTransparancy() < EPSILON || remaining <= 0) {
        return Color::Black;
    }
    double n_ratio { computations.n1 / computations.n2 };
    double cos_i { dot(computations.eyeVec, computations.normVec) };

    double sin2_t { n_ratio * n_ratio * (1.0 - cos_i * cos_i) };

    if (sin2_t > 1.0) {
        return Color::Black;
    }

    double cos_t { std::sqrt(1.0 - sin2_t) };
    Tuple direction { computations.normVec * (n_ratio * cos_i - cos_t) - computations.eyeVec * n_ratio };

    Ray refractRay { computations.underPoint, direction };

    Color color { colorAt(w, refractRay, remaining - 1) };
    return color * computations.object->getMaterials().getTransparancy();
}
