#include "scene.hpp"
#include <algorithm>
#include "lighting/light.hpp"
#include "lighting/material.hpp"
#include <iostream>

std::vector<Intersection> Scene::intersections_with(Ray& ray)
{
    std::vector<Intersection> intersections;
    for (auto& object : objects) {
        std::vector<Intersection> obj_i = object->intersects_with(ray);
        for (Intersection& i : obj_i) {
            intersections.push_back(i);
        }
    }
    std::sort(intersections.begin(), intersections.end());
    return intersections;
}

Color Scene::color_at_intersection(Intersection& i)
{
    return i.object->material.color_at_point(i.hitrecord(), *this);
}

Color Scene::color_with_ray(Ray& r)
{
    auto intersections = intersections_with(r);
    for (auto in : intersections) {
        if (in.t > 0) {
            return color_at_intersection(in);
        }
    }
}