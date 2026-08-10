#ifndef WORLD_H
#define WORLD_H

#include "Light.h"
#include "Shape.h"
#include "Ray.h"
#include "Intersections.h"
#include <vector>
#include <memory>

class World {
private:
    std::vector<std::shared_ptr<Shape>> m_objects {}; 
    pointLight m_light{point(-10, 10, -10), Color(1, 1, 1)}; 
  
public:
    World() = default;

    void addObject(std::shared_ptr<Shape> object) {
        m_objects.push_back(std::move(object));
    }

    const std::vector<std::shared_ptr<Shape>>& getObjects() const {
        return m_objects;
    }

    void setLight(const pointLight& PL) {
        m_light = PL;
    }
    const pointLight& getLight() const {
        return m_light;
    }
};

World defaultWorld();

std::vector<Intersection> intersect_world(const World& world, const Ray& ray);

bool isShadowed(const World& w, const Tuple& p);
Color shadeHit(const World& w, const Comp& comps, int remaining = 5);
Color colorAt(const World& w, const Ray& ray, int remaining);
Color reflectedColor(const World& w, const Comp& computations, int remaining = 5);
Color refractedColor(const World& w, const Comp& computations, int remaining = 5);
#endif