#include "intersection.hpp"
#include "geometry/object.hpp"

HitRecord Intersection::hitrecord()
{
    HitRecord h;
    h.hit_point = ray.point_at(t);
    h.eye = Vector(0, 0, 0) - ray.origin;
    h.normal = object->normal_at(h.hit_point);

    h.is_inside = false;
    if (h.normal.dot(h.eye) < 0) {
        h.normal = -1 * h.normal;
        h.is_inside = true;
    }

    return h;
}

bool operator<(Intersection& a, Intersection& b)
{
    return (a.t < b.t);
}