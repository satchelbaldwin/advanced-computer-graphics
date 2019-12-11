#include "camera.hpp"
#include "math/math.hpp"
#include "scene.hpp"
#include <iostream>

Camera::Camera(/* args */) : transform(Matrix::identity(4)), sampler(9, 16) {}

Camera::Camera(double fov, int width, int height)
    : fov(fov), width(width), height(height),
      aspect((double)width / (double)height), transform(Matrix::identity(4)),
      sampler(9, 16) {
  double field_radians = degrees_to_radians(fov);
  double half_view = tan(field_radians / 2.);
  if (aspect >= 1) {
    half_width = half_view;
    half_height = half_view / aspect;
  } else {
    half_width = half_view * aspect;
    half_height = half_view;
  }
  pixel_size = (half_width * 2) / (double)height;
}

Ray Camera::ray_for_pixel(double x, double y) {
  // antialiasing here, this aims at pixel center
  Sample next = sampler.next();
  //std::cout << "nf " << next.first << " ns " << next.second << "\n";
  double x_offset = (x + 0.5 + next.first) * pixel_size;
  double y_offset = (y + 0.5 + next.second) * pixel_size;

  if (x == 1 && y == 1 || x == 1 && y == 2) {
    std::cout << x_offset << " " << y_offset << "\n";
  }

  double world_x = half_width - x_offset;
  double world_y = half_height - y_offset;

  Point pixel = (*transform.get_inverse()) * Point(world_x, world_y, -1);
  Point origin = (*transform.get_inverse()) * Point(0, 0, 0);
  Vector direction = (pixel - origin).normalize();

  return Ray(origin, direction);
}

void Camera::render_scene(Canvas *canvas, Scene &scene) {
  sampler.generate_jitter(3);
#pragma omp parallel for
  for (int y = 0; y < height; ++y) {
#pragma omp parallel for
    for (int x = 0; x < width; ++x) {

      Color sum(0, 0, 0);
      double &sx = sum.x;
      double &sy = sum.y;
      double &sz = sum.z;
#pragma omp parallel for reduction(+:sx) reduction(+:sy) reduction(+:sz)
      for (int i = 0; i < sampler.num_samples; ++i) {

        // std::cout << "x: " << x << " n: " << next.first << "\n";
        Ray r = ray_for_pixel(x , y);
        Color c = scene.color_with_ray(r);
        sx += c.x;
        sy += c.y;
        sz += c.z;
      }

      sum.x = sum.x / sampler.num_samples;
      sum.y = sum.y / sampler.num_samples;
      sum.z = sum.z / sampler.num_samples;

      canvas->pixels[y][x] = sum;
    }
    std::cout << "Progress:\t\t " << (double)y / (double)height << "%\n";
  }
}

void Camera::set_transformation(Vector from, Vector to, Vector up) {
  Vector forward = (to - from).normalize();
  Vector left = cross(forward, up.normalize());
  Vector true_up = cross(left, forward);

  double m[] = {left.x,     left.y,     left.z,     0,
                true_up.x,  true_up.y,  true_up.z,  0,
                -forward.x, -forward.y, -forward.z, 0,
                0,          0,          0,          1};

  Matrix orientation = Matrix::from(4, m);
  Matrix adjusted =
      orientation * Matrix::translate(Vector(-from.x, -from.y, -from.z));
  transform = adjusted;
  transform.store_inverse();
}