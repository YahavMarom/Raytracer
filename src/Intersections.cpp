#include "Intersections.h"
#include "Constants.h"
#include <cmath>
#include <algorithm>


// returns data struct "Intersection" when using this func
Intersection intersection(double t, const Sphere& s) {
    return Intersection{t, &s};
}


// computes the intersections of sphere and ray, and if there are points, sets the data structure Intersection for both.
std::vector<Intersection> intersect(const Sphere& s, const Ray& r) {
    Tuple sphere_to_ray = r.getOrigin() - point(0.0, 0.0, 0.0);

    double a = dot(r.getDirection(), r.getDirection());
    double b = 2.0 * dot(r.getDirection(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1.0;

    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0.0) {
        return {};
    }
    else {
        double sqrt_d = std::sqrt(discriminant);
        double t1 = (-b - sqrt_d) / (2.0 * a);
        double t2 = (-b + sqrt_d) / (2.0 * a);

        if (t1 > t2) {
        std::swap(t1, t2);
        }

        return { intersection(t1, s), intersection(t2, s) };
    }
}

// let's us use intersections on arbitrary amount of "i_1, i_2.. i_4"
// sorts the intersections from lower to higher based on t val
std::vector<Intersection> intersections(std::initializer_list<Intersection> list){
    std::vector<Intersection> xs {list};
    std::sort(xs.begin(), xs.end(),
                [](const Intersection& a, const Intersection& b) {
                    return a.t < b.t;
                }
            );
    return xs;


}

// returns the lowest non-negative.
std::optional<Intersection> hit(std::vector<Intersection>& xs) {
    for (const auto& i : xs) {
        if (i.t >= 0) {
            return i;
        }
    }
    return std::nullopt;
}
