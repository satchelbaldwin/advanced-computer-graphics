#pragma once
#include "math/math.hpp"
#include "scene.hpp"
#include "canvas/canvas.hpp"

// perspective camera
class Camera
{
public:
    Camera();
    Camera(double, int, int);
    
    double fov;
    double pixel_size;

    double aspect;
    int width;
    int height;
    double half_width;
    double half_height;

    Matrix transform;
    Vector forward;
    Vector up;
    Vector right;

    Ray ray_for_pixel(int, int);
    void render_scene(Canvas*, Scene&);
    void set_transformation(Vector, Vector, Vector);
};

