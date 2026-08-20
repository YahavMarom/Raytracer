#include "Group.h"

void Group::addChild(const std::shared_ptr<Shape>& child) {
    m_children.push_back(child);
    child->setParent(this);
    m_cachedBounds.insert(child->parentSpaceBounds()); 
}

Bounds Group::bounds() const {
    return m_cachedBounds;
}

std::vector<Intersection> Group::localIntersect(const Ray& localRay) const {
    
    if (!m_cachedBounds.intersects(localRay)) {
        return {};
    }

    if (m_children.empty()) {
        return {};
    }

    std::vector<Intersection> res {};
    for (const auto& child : m_children) {
        auto xs = child->intersect(localRay);
        res.insert(res.end(), xs.begin(), xs.end());
    }

    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b) {
        return a.t < b.t;
    });

    return res;
}