#pragma once
#include <vector>

#include "geometry/object.hpp"
#include "math/math.hpp"

class Scene {
public:
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<PointLight>> lights;

  template <class T> void add_object(const T &o) {
    objects.push_back(std::make_shared<T>(o));
  }

  template <class T> void add_light(const T &l) {
    lights.push_back(std::make_shared<T>(l));
  }

  std::vector<Intersection> intersections_with(Ray &);
  Color color_at_intersection(Intersection &, std::vector<Intersection> &);
  Color color_at_intersection(Intersection &, std::vector<Intersection> &, int);

  Color color_with_ray(Ray &);
  Color color_with_ray(Ray &, int);

  const static int max_refraction_depth = 5;
  Color refracted_color(Intersection &, HitRecord &, int);

  void calculate_inverses();

  bool is_in_shadow(Point &, PointLight &);
};