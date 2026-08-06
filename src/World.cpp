#include "World.h"
#include "Sphere.h"
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

bool isShadowed(const World& w, const Tuple& p) {
    Tuple v {w.getLight().position - p};
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

Color shadeHit(const World& w, const Comp& comp) {
    bool shadow {isShadowed(w, comp.overPoint)};
    return lighting(comp.object->getMaterials(), *(comp.object), w.getLight(), comp.point, comp.eyeVec, comp.normVec, shadow);
}

Color colorAt(const World& w, const Ray& ray) {
    auto world_intersections {intersect_world(w, ray)};
    auto xs {hit(world_intersections)};
    if (xs.has_value()) {
        Comp comp {prepareComputations(*xs, ray)};
        return shadeHit(w, comp);
    }
    else {
        return Color(0,0,0);
    }
}