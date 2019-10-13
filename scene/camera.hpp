#pragma once
#include "math/math.hpp"
#include "scene.hpp"
#include "canvas/canvas.hpp"

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
    double aspect;
    Matrix transform;
    Vector forward;
    Vector up;
    Vector right;

    void render_scene(Canvas const*, const Scene&);
};

