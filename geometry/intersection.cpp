#include "intersection.hpp"
#include "geometry/object.hpp"

HitRecord Intersection::hitrecord()
{
    HitRecord h;
    h.hit_point = ray.point_at(t);
    h.eye = (ray.origin - h.hit_point).normalize();
    h.normal = object->normal_at(h.hit_point);

    h.is_inside = false;
    if (h.normal.dot(h.eye) < 0) {
        h.normal = -1 * h.normal;
        h.is_inside = true;
    }

    h.overpoint = h.hit_point + (h.normal * 0.005);

    return h;
}

bool operator<(Intersection& a, Intersection& b)
{
    return (a.t < b.t);
}