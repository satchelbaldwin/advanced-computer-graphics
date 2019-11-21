#pragma once
#include <iostream>
#include <vector>

#include "geometry/intersection.hpp"
#include "lighting/material.hpp"
#include "math/math.hpp"

class Object {
public:
  Object();
  Matrix transform;
  Material material;
  // takes transformed ray into object space and world space ray
  virtual std::vector<Intersection> local_intersects_with(Ray &, Ray &) {
    std::cout << "Something got sliced! Uh-oh.\n";
    return std::vector<Intersection>();
  };
  virtual Vector local_normal_at(Point &) { return Vector(); };

  std::vector<Intersection> intersects_with(Ray &);
  Vector normal_at(Point &);

  void scale(const Tuple &);
  void scale(double, double, double);
  void translate(const Tuple &);
  void translate(double, double, double);
  void rotate(const Tuple &);
  void rotate(double, double, double);
};
