#include "plane.hpp"

Plane::Plane() {}

std::vector<Intersection> Plane::intersects_with(Ray& ray)
{

}

Vector Plane::normal_at(Point& p)
{
    Vector object_normal = Vector(0, 1, 0);
    Vector world_normal = transform.get_inverse()->transpose() * object_normal;
    return world_normal.normalize();
}