#ifndef GROUP_H
#define GROUP_H

#include "Shape.h"
#include <vector>
#include <memory>

class Group : public Shape {

private:
    std::vector<std::shared_ptr<Shape> > m_children {};
    Bounds m_cachedBounds {};

public:
    Group() = default;
    ~Group() override = default;

    void addChild(const std::shared_ptr<Shape>& child);

    std::vector<Intersection> localIntersect(const Ray& localRay) const override;

    Tuple localNormalAt(const Tuple& localPoint) const override {
    (void)localPoint;
    throw std::runtime_error("localNormalAt should never be called directly on a Group");
    }   

    Bounds bounds() const override;

};

#endif