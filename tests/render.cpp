#include <iostream>

#include "canvas/canvas.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "geometry/triangle.hpp"
#include "lighting/pattern.hpp"
#include "lighting/patterns/stripes.hpp"
#include "math/math.hpp"
#include "scene/camera.hpp"
#include "scene/scene.hpp"

int main(int argc, char **argv) {
  Canvas canvas{500, 500};
  Scene scene;
  Camera camera{60, 500, 500};

  PointLight light{Point(-10, 10, -10), Color(0.2, 0.2, 0.2)};
  PointLight light2{Point(10, 10, -10), Color(0.5, 0.5, 0.5)};
  // scene.add_light(light);
  // scene.add_light(light2);

  camera.set_transformation(Vector(0, 1.5, -5), Vector(0, 1, 0),
                            Vector(0, 1, 0));

  camera.set_transformation(Vector(0, 0, -5), Vector(0, 0, 0), Vector(0, 1, 0));

  PointLight light3{Point(5, 5, -10), Color(1, 1, 1)};
  scene.add_light(light3);

  Plane wall{};
  wall.rotate(90, 0, 0);
  wall.translate(0, 0, 3);
  wall.material.color = Color(1, 1, 1);
  StripePattern x = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
  x.transform = Matrix::scale(Vector{0.5, 0.5, 0.5}) * x.transform;
  wall.material.set_pattern(x, &wall);
  wall.material.specular = 0;

  Sphere one{};
  one.material.transparency = 1.0;
  one.material.reflectivity = 0.8;
  one.material.ior = 1.1;
  one.material.color = Color{0, 0, 0};
  one.material.diffuse = 0.0;
  one.material.ambient = 0.0;
  one.material.emission = 0.0;

  // one.material.set_pattern(x, &one);
  one.scale(2, 2, 2);

  Sphere two{};
  two.material.transparency = 1.0;
  two.material.ior = 1.0;
  two.material.color = Color{0, 0, 0};
  two.material.diffuse = 0.0;
  two.material.ambient = 0.0;
  two.material.emission = 0.0;
  two.translate(0.25, 0.25, -0.25);

  scene.add_object(one);
  scene.add_object(wall);
  // scene.add_object(two);
  // scene.add_object(three);

  scene.calculate_inverses();

  camera.render_scene(&canvas, scene);
  canvas.write("second-image.ppm");

  return 0;
}
