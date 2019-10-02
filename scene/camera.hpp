#pragma once
#include "math/math.hpp"

// perspective camera
class Camera
{
public:
    Camera();
    double fov_h;
    double fov_w;
    Point origin;
    int width;
    int height;
    Matrix transform;
    Vector forward;
    Vector up;
    Vector right;
};

