#ifndef WORLD_H
#define WORLD_H


#include "Light.h"
#include "Sphere.h"
#include "Ray.h"
#include "Intersections.h"

#include <vector>
#include <memory>



class World {

private:
    std::vector<std::shared_ptr<Sphere>> m_objects {}; //maybe change to Shape after
    pointLight m_light{point(-10, 10, -10), Color(1, 1, 1)}; //maybe change to std::vector if there are several lights
  
public:
    World() = default;

    void addObject(std::shared_ptr<Sphere> object) {
        m_objects.push_back(std::move(object));
    }

    const std::vector<std::shared_ptr<Sphere> >& getObjects() const {
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

Color shade_hit(const World& w, const Comp& comps);
Color color_at(const World& w, const Ray& ray);
#endif