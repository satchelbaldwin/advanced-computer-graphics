#include "scene.hpp"
#include <algorithm>
#include "lighting/light.hpp"
#include "lighting/material.hpp"

void Scene::add_object(const Object& o)
{
    objects.push_back(o);
}

void Scene::add_light(const PointLight& pl)
{
    lights.push_back(pl);
}

std::vector<Intersection> Scene::intersections_with(Ray& ray)
{
    std::vector<Intersection> intersections;
    for (auto object : objects) {
        for (auto intersection : object.intersects_with(ray)) {
            intersections.push_back(intersection);
        }
    }
    std::sort(intersections.begin(), intersections.end());
    return intersections;
}

Color Scene::color_at_intersection(Intersection& i)
{
    return i.object->material.color_at_point(i.hitrecord(), lights);
}