#pragma once
#include "math/math.hpp"

class HitRecord {
public:
    HitRecord(){}
    Point hit_point;
    Vector normal;
    Vector eye;
    bool is_inside;
};

class Object;
class Intersection {
public:
    Intersection(){}
    Intersection(double t, Ray r, Object *o) : t(t), ray(r), object(o) {}
    double t;
    Ray ray;
    Object *object;
    HitRecord hitrecord() 
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
};