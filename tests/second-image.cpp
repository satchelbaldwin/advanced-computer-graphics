#include <iostream>

#include "canvas/canvas.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "geometry/triangle.hpp"
#include "math/math.hpp"
#include "scene/camera.hpp"
#include "scene/scene.hpp"

int main(int argc, char **argv) {
  Canvas canvas{500, 250};
  Scene scene;
  Camera camera{60, 500, 250};

  // Testing scene
  Plane floor{};
  floor.material.color = Color(1, 0.9, 0.9);
  floor.material.specular = 0;

  Plane right_wall{};
  right_wall.rotate(90, 0, 0);
  right_wall.rotate(0, 45, 0);
  right_wall.translate(0, 0, 5);
  right_wall.material = floor.material;

  Plane left_wall{};
  left_wall.material.color = Color(1, 0.9, 0.8);
  left_wall.rotate(90, 0, 0);
  left_wall.rotate(0, -45, 0);
  left_wall.translate(0, 0, 5);
  left_wall.material = floor.material;

  Sphere middle{};
  middle.translate(Vector(-0.5, 1, 0.5));
  middle.material.color = Color(0.1, 1, 0.5);
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;

  Sphere right{};
  right.scale(Vector(0.5, 0.5, 0.5));
  right.translate(Vector(1.5, 0.5, -0.5));
  right.material.color = Color(0.1, 1, 0.5);
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;

  scene.add_object(floor);
  scene.add_object(left_wall);
  scene.add_object(right_wall);
  scene.add_object(middle);
  scene.add_object(right);

  PointLight light{Point(-10, 10, -10), Color(0.2, 0.2, 0.2)};
  PointLight light2{Point(10, 10, -10), Color(0.5, 0.5, 0.5)};
  scene.add_light(light);
  scene.add_light(light2);
  scene.calculate_inverses();

  camera.set_transformation(Vector(0, 1.5, -5), Vector(0, 1, 0),
                            Vector(0, 1, 0));

  camera.render_scene(&canvas, scene);

  canvas.write("second-image.ppm");

  return 0;
}
