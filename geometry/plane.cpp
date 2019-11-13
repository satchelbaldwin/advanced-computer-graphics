#include "plane.hpp"
#include <iostream>

Plane::Plane() {}

std::vector<Intersection> Plane::local_intersects_with(Ray& ray, Ray& original_ray)
{
    std::vector<Intersection> intersections;
    if (abs(ray.direction.y) < 0.00001) {
        return intersections;
    }
    double t = -ray.origin.y / ray.direction.y;
    intersections.push_back(Intersection{t, original_ray, this});    
    return intersections;
} 

Vector Plane::local_normal_at(Point& object_point)
{
    Vector object_normal = Vector(0, 1, 0);
    return object_normal;
}