#pragma once
#include "math/math.hpp"

class PointLight {
public:
    PointLight(Point p, Color c) : position(p), intensity(c) {}
    Point position;
    Color intensity;
};