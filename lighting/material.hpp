#pragma once
#include "math/math.hpp"

class Material {
public:
    Material(Color c, double d) : color(c), double(d) {}
    Color color;
    double diffuse;
};