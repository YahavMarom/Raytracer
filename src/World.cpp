#include "World.h"
#include "Transformations.h"

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

    // Create S2 (Inner Sphere)
    auto s2 = std::make_shared<Sphere>();
    s2->setTransform(scaling(0.5, 0.5, 0.5));
    w.addObject(s2);

    return w;
}


std::vector<Intersection> intersect_world(const World& w, const Ray& ray) {
    std::vector<Intersection> world_intersections {};

    for (const auto& object : w.getObjects()) {
        auto xs {intersect(*object, ray)};
        
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


Color shade_hit(const World& w, const Comp& comp) {
    return lighting(comp.object->getMaterials(), w.getLight(), comp.point, comp.eyeVec, comp.normVec);

}



Color color_at(const World& w, const Ray& ray) {
    auto world_intersections {intersect_world(w, ray)};
    auto xs {hit(world_intersections)};
    if (xs.has_value()) {
        Comp comp {prepareComputations(*xs, ray)};
        return shade_hit(w, comp);
    }
    else {
        return Color(0,0,0);
    }
}