#include "plane.hpp"

Plane::Plane() {}

std::vector<Intersection> Plane::intersects_with(Ray& original_ray)
{
    Ray ray = *(transform.get_inverse()) * original_ray;

    std::vector<Intersection> intersections;
    if (abs(ray.direction.y) < 0.0001) {
        return intersections;
    }
    double t = -ray.origin.y / ray.direction.y;
    intersections.push_back(Intersection{t, ray, this});    
    return intersections;
} 

Vector Plane::normal_at(Point& p)
{
    Vector object_normal = Vector(0, 1, 0);
    Vector world_normal = transform.get_inverse()->transpose() * object_normal;
    return world_normal.normalize();
}