#include <iostream>

#include "canvas/canvas.hpp"
#include "geometry/sphere.hpp"
#include "math/math.hpp"

int main(int argc, char **argv) {
  Canvas canvas{100, 100};
  Sphere s;
  Color red{1.0, 0, 0};
  Color black{0, 0, 0};

  Point light{5, 0, -5};

  // orthographic camera
  for (size_t row = 0; row < canvas.height; ++row) {
    for (size_t col = 0; col < canvas.width; ++col) {
      double x = (row / 25.f) - 2;
      double y = (col / 25.f) - 2;
      Point origin{x, y, -5};
      Ray r{origin, Vector(0, 0, 1)};
      auto i = s.intersects_with(r);
      if (i.size() > 0) {
        Point hit = r.point_at(i[0]);
        Vector to_light = light - hit;
        Vector unit_to_light = to_light.normalize();
        Vector normal = s.normal_at(hit);

        auto light_intensity = normal.dot(unit_to_light);
        Color c = light_intensity * red;

        // std::cout << row << " " << col << " " << light_intensity <<
        // std::endl;
        canvas.pixels[col][row] = c;
      } else {
        canvas.pixels[col][row] = black;
      }
    }
  }

  canvas.write("first-image.ppm");

  return 0;
}
