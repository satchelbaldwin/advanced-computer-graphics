#pragma once
#include <vector>
#include "math/math.hpp"
#include "geometry/object.hpp"

class Scene {
public:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<PointLight>> lights;
    
    void add_object(Object*);
    void add_light(PointLight*);
    std::vector<Intersection> intersections_with(Ray&);
    Color color_at_intersection(Intersection&);
};