#pragma once
#include "math/math.h"

class PointLight {
public:
    PointLight(Point p, Color c) : position(p), color(c) {}
    Point position;
    Color intensity;
};