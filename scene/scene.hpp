#pragma once
#include <vector>
#include "math/math.hpp"
#include "geometry/object.hpp"

class Scene {
public:
    std::vector<Object> objects;
    std::vector<PointLight> lights;
    
    void add_object(const Object&);
    void add_light(const PointLight&);
    std::vector<Intersection> intersections_with(Ray&);
    Color color_at_intersection(Intersection&);
};