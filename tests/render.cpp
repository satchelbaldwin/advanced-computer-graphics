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
  Canvas canvas{1280, 720};
  Scene scene;
  Camera camera{60, 1280, 720};

  PointLight light{Point(-10, 10, -10), Color(0.2, 0.2, 0.2)};
  PointLight light2{Point(10, 10, -10), Color(0.5, 0.5, 0.5)};
  // scene.add_light(light);
  // scene.add_light(light2);

  //camera.set_transformation(Vector(-5, -2, -5), Vector(0, 0, 0), Vector(0, 1, 0));

  camera.set_transformation(Vector(-0.5, -1, -4), Vector(-1.5, 1, 0), Vector(0, 1, 0));


  PointLight light3{Point(5, 5, -10), Color(1, 1, 1)};
  scene.add_light(light3);

  Plane wall{};
  wall.rotate(90, 0, 0);
  wall.translate(0, 0, 3);
  wall.material.color = Color(1, 1, 1);
  StripePattern x = StripePattern(Color(0.3, 0.3, 0.3), Color(0.7, 0.7, 0.7));
  x.transform = Matrix::scale(Vector{0.2, 0.2, 0.2}) * x.transform;
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
  one.material.casts_shadow = false;

  // one.material.set_pattern(x, &one);
  one.scale(2, 2, 2);

  Sphere two{};
  two.material.transparency = 1.0;
  two.material.reflectivity = 0.6;
  two.material.ior = 1.0;
  two.material.color = Color{0, 0, 0.2};
  two.material.diffuse = 0.3;
  two.material.ambient = 0.1;
  two.material.emission = 0.0;
  two.translate(0.75, 0.50, -0.25);
  two.material.casts_shadow = false;

  Sphere three{};
  three.material.transparency = 1.0;
  three.material.reflectivity = 0.6;
  three.material.ior = 1.0;
  three.material.color = Color{0, 0.2, 0};
  three.material.diffuse = 0.3;
  three.material.ambient = 0.1;
  three.material.emission = 0.0;
  three.translate(-1.75, -0.75, 0.25);
  three.material.casts_shadow = false;
  three.scale(0.7, 0.7, 0.7);

  Sphere four{};
  four.material.transparency = 1.0;
  four.material.reflectivity = 0.6;
  four.material.ior = 1.0;
  four.material.color = Color{0.2, 0, 0};
  four.material.diffuse = 0.3;
  four.material.ambient = 0.1;
  four.material.emission = 0.0;
  four.scale(0.5, 0.3, 0.3);
  four.translate(0, -1, 0);
  four.material.casts_shadow = false;


  scene.add_object(one);
  scene.add_object(wall);
  scene.add_object(two);
  scene.add_object(three);
  scene.add_object(four);

  // scene.add_object(three);

  scene.calculate_inverses();

  camera.render_scene(&canvas, scene);
  canvas.write("second-image.ppm");

  return 0;
}
