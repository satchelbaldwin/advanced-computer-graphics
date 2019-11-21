#pragma once
#include "math/math.hpp"
#include "object.hpp"

class Plane : public Object {
public:
  Plane();
  std::vector<Intersection> local_intersects_with(Ray &, Ray &) override;
  Vector local_normal_at(Point &) override;
};
