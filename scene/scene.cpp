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
    return Color(0, 0, 0);
}

void Scene::calculate_inverses() 
{
    for (auto& o : objects) {
        o->transform.store_determinant();
        o->transform.store_inverse();
    }
}

bool Scene::is_in_shadow(Point& point, PointLight& light)
{
    auto v = light.position - point;
    auto distance = v.magnitude();
    auto direction = v.normalize();
    Ray ray{point, direction};
    std::cout << "po: " << point << " dir: " << direction << "\n";
    auto intersections = intersections_with(ray);
    if (intersections.size() < 1) 
        return false;

    std::cout << intersections[0].object;

    double lowest_t; 
    for (auto& i : intersections) {
        if (i.t >= 0) {
            lowest_t = i.t;
            break;
        }
    }
    std::cout << "lt: " << lowest_t << " dis" << distance << "\n";
    return (lowest_t < distance);
}