#pragma once
#include "canvas/canvas.hpp"
#include "math/math.hpp"
#include "math/sampler.hpp"
#include "scene.hpp"

// perspective camera
class Camera {
public:
  Camera();
  Camera(double, int, int);

  double fov;
  double pixel_size;

  int width;
  int height;
  double aspect;
  double half_width;
  double half_height;

  Matrix transform;
  Vector forward;
  Vector up;
  Vector right;

  Sampler sampler;

  Ray ray_for_pixel(double, double);
  void render_scene(Canvas *, Scene &);
  void set_transformation(Vector, Vector, Vector);
};
