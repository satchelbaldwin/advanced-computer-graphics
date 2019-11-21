#pragma once
#include "object.hpp"

class Triangle : public Object {
public:
  Point a;
  Point b;
  Point c;

  Triangle();
  Triangle(const Point &, const Point &, const Point &);
  std::vector<Intersection> local_intersects_with(Ray &, Ray &) override;
  Vector local_normal_at(Point &) override;
};
