#pragma once
#include "matrix.hpp"
#include "point.hpp"
#include "vector.hpp"

class Ray {
public:
  Ray();
  Ray(Point, Vector);

  Point origin;
  Vector direction; // needs to be a unit vector!
  Ray transform(const Matrix &);

  Point point_at(double);
};

Ray operator*(const Matrix &m, const Ray &r);