#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "lighting/point_light.hpp"
#include "math/constants.hpp"
#include "math/v3.hpp"
#include "scene/scene.hpp"
#include "tests/catch.hpp"

auto glass = []() {
  Sphere s;
  s.material.transparency = 1.0;
  s.material.ior = 1.5;
  return s;
};

auto default_world = []() {
  Scene s;
  PointLight light{Point{-10, 10, -10}, Color{1, 1, 1}};

  Sphere s1;
  s1.material.color = Color{0.8, 1.0, 0.6};
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;
  s1.material.shininess = 200;
  s1.material.ambient = 0.1;
  s1.material.ior = 1;
  s1.material.reflectivity = 0;
  s1.material.transparency = 0;
  s.add_object(s1);

  Sphere s2;
  s2.scale(0.5, 0.5, 0.5);
  s2.material.color = Color{1, 1, 1};
  s2.material.diffuse = 0.9;
  s2.material.specular = 0.9;
  s2.material.shininess = 200;
  s2.material.ambient = 0.1;
  s2.material.ior = 1;
  s2.material.reflectivity = 0;
  s2.material.transparency = 0;
  s.add_object(s2);

  s.add_light(light);

  return s;
};

TEST_CASE("Refraction") {

  SECTION("default material") {
    Material m;
    REQUIRE(m.transparency == 0.0);
    REQUIRE(m.ior == 1.0);
  }
  SECTION("glass sphere") {
    Sphere g = glass();
    REQUIRE(g.material.transparency == 1.0);
    REQUIRE(g.material.ior == 1.5);
  }
  SECTION("IORs at various intersections") {
    Sphere a = glass();
    a.scale(2, 2, 2);

    Sphere b = glass();
    b.translate(0, 0, -0.25);
    b.material.ior = 2.0;

    Sphere c = glass();
    c.translate(0, 0, 0.25);
    c.material.ior = 2.5;

    Scene s;
    s.add_object(a);
    s.add_object(b);
    s.add_object(c);

    Ray r{Point{0, 0, -4}, Vector{0, 0, 1}};
    auto xs = s.intersections_with(r);

    auto h0 = xs[0].hitrecord(xs);
    REQUIRE(h0.ior_incoming == 1.0);
    REQUIRE(h0.ior_transmitted == 1.5);

    auto h1 = xs[1].hitrecord(xs);
    REQUIRE(h1.ior_incoming == 1.5);
    REQUIRE(h1.ior_transmitted == 2.0);

    auto h2 = xs[2].hitrecord(xs);
    REQUIRE(h2.ior_incoming == 2.0);
    REQUIRE(h2.ior_transmitted == 2.5);

    auto h3 = xs[3].hitrecord(xs);
    REQUIRE(h3.ior_incoming == 2.5);
    REQUIRE(h3.ior_transmitted == 2.5);

    auto h4 = xs[4].hitrecord(xs);
    REQUIRE(h4.ior_incoming == 2.5);
    REQUIRE(h4.ior_transmitted == 1.5);

    auto h5 = xs[5].hitrecord(xs);
    REQUIRE(h5.ior_incoming == 1.5);
    REQUIRE(h5.ior_transmitted == 1.0);
  }
  SECTION("Under point") {
    Ray r{Point(0, 0, -5), Vector{0, 0, 1}};
    Sphere shape = glass();
    shape.translate(0, 0, 1);
    Scene s;
    s.add_object(shape);
    auto xs = s.intersections_with(r);
    auto hr = xs[0].hitrecord(xs);
    REQUIRE(hr.underpoint.z > EPSILON / 2);
    REQUIRE(hr.hit_point.z < hr.underpoint.z);
  }
  SECTION("Refracted color: opaque") {
    Scene s = default_world();
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    auto xs = s.intersections_with(r);
    auto h = xs[0].hitrecord(xs);
    REQUIRE(xs[0].object->material.refract_color(h, s, 0) == Color{0, 0, 0});
  }
  SECTION("Refracted color: Maximum depth") {
    Scene s = default_world();
    s.objects[0]->material.transparency = 1.0;
    s.objects[0]->material.ior = 1.5;
    Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
    auto xs = s.intersections_with(r);
    auto h = xs[0].hitrecord(xs);
    REQUIRE(xs[0].object->material.refract_color(h, s, 5) == Color{0, 0, 0});
  }
  SECTION("Refracted color: Maximum depth") {
    Scene s = default_world();
    s.objects[0]->material.transparency = 1.0;
    s.objects[0]->material.ior = 1.5;
    Ray r{Point{0, 0, sqrt(2) / 2}, Vector{0, 1, 0}};
    auto xs = s.intersections_with(r);
    auto h = xs[1].hitrecord(xs);
    REQUIRE(xs[1].object->material.refract_color(h, s, 0) == Color{0, 0, 0});
  }
  SECTION("Color at ray: Refraction") {
    Scene s = default_world();

    Plane floor{};
    floor.translate(0, -1, 0);
    floor.material.transparency = 0.5;
    floor.material.ior = 1.5;
    floor.material.color.y = 1;
    s.add_object(floor);

    Sphere ball{};
    ball.material.color = Color{1, 0, 0};
    ball.material.ambient = 0.5;
    ball.translate(0, -3.5, -0.5);
    s.add_object(ball);

    Ray r{Point{0, 0, -3}, Vector{0, -sqrt(2) / 2, sqrt(2) / 2}};
    auto xs = s.intersections_with(r);

    auto c = s.color_with_ray(r);
    REQUIRE(c == Color{0.936425, 0.686425, 0.686425});
  }
  SECTION("Schlick : IOR") {
    Scene s;
    auto g = glass();
    s.add_object(g);
    Ray r{Point{0, 0, sqrt(2) / 2}, Vector{0, 1, 0}};
    auto xs = s.intersections_with(r);
    REQUIRE(xs[1].object->material.schlick(xs[1].hitrecord(xs)) == 1.0);
  }
  SECTION("Schlick : Perpendicular") {
    Scene s;
    auto g = glass();
    s.add_object(g);
    Ray r{Point{0, 0, 0}, Vector{0, 1, 0}};
    auto xs = s.intersections_with(r);
    REQUIRE(xs[1].object->material.schlick(xs[1].hitrecord(xs)) == 0.04);
  }
  SECTION("Schlick : Small angle and n2 > n1") {
    Scene s;
    auto g = glass();
    s.add_object(g);
    Ray r{Point{0, 0.99, -2}, Vector{0, 0, 1}};
    auto xs = s.intersections_with(r);
    REQUIRE(xs[0].object->material.schlick(xs[0].hitrecord(xs)) == 0.48873);
  }
  SECTION("Schlick : Small angle and n2 > n1") {
    Scene s = default_world();

    Ray r{Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Plane plane{};
    plane.translate(0, -1, 0);
    plane.material.reflectivity = 0.5;
    plane.material.transparency = 0.5;
    plane.material.ior = 1.5;
    plane.material.color.y = 1.0;
    s.add_object(plane);

    Sphere ball{};
    ball.material.color = Color{1, 0, 0};
    ball.material.ambient = 0.5;
    ball.translate(0, -3.5, -0.5);
    s.add_object(ball);

    auto xs = s.intersections_with(r);
    REQUIRE(s.color_at_intersection(xs[0], xs) == Color{0.9, 0.7, 0.7});
  }
}