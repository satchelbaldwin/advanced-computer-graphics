#pragma once
#include "math/math.hpp"

class HitRecord {
public:
    HitRecord(){}
    Point hit_point;
    Vector normal;
    Vector eye;
    bool is_inside;
    Point overpoint;
    Point underpoint;
};

class Object;
class Intersection {
public:
    Intersection(){}
    Intersection(double t, Ray r, Object *o) : t(t), ray(r), object(o) {}
    double t;
    Ray ray;
    Object *object;
    HitRecord hitrecord();
};

bool operator<(Intersection& a, Intersection& b);