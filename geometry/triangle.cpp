#include "triangle.hpp"

#include <iostream>

Triangle::Triangle()
    : Triangle(Point{1, 0, 0}, Point{0, 1, 0}, Point{0, 0, 1}) {}
Triangle::Triangle(const Point &a, const Point &b, const Point &c)
    : Object(), a(a), b(b), c(c) {}

std::vector<Intersection> Triangle::local_intersects_with(Ray &ray,
                                                          Ray &original_ray) {
  double d[9] = {
      a.x - b.x,       a.x - c.x, ray.direction.x, a.y - b.y,       a.y - c.y,
      ray.direction.y, a.z - b.z, a.z - c.z,       ray.direction.z,
  };
  Matrix denominator = Matrix::from(3, d);

  double beta_numerator[9] = {
      a.x - ray.origin.x, a.x - c.x, ray.direction.x,
      a.y - ray.origin.y, a.y - c.y, ray.direction.y,
      a.z - ray.origin.z, a.z - c.z, ray.direction.z,
  };
  double beta =
      Matrix::from(3, beta_numerator).determinant() / denominator.determinant();

  double gamma_numerator[9] = {
      a.x - b.x, a.x - ray.origin.x, ray.direction.x,
      a.y - b.y, a.y - ray.origin.y, ray.direction.y,
      a.z - b.z, a.z - ray.origin.z, ray.direction.z,
  };
  double gamma = Matrix::from(3, gamma_numerator).determinant() /
                 denominator.determinant();

  // refactor
  auto make_intersection = [&](double t) -> Intersection {
    return Intersection(t, original_ray, this);
  };
  std::vector<Intersection> r;
  // constraints
  if (beta >= 0 && gamma >= 0 && beta + gamma <= 1) {
    double time_numerator[9] = {
        a.x - b.x, a.x - c.x, a.x - ray.origin.x,
        a.y - b.y, a.y - c.y, a.y - ray.origin.y,
        a.z - b.z, a.z - c.z, a.z - ray.origin.z,
    };
    double time = Matrix::from(3, time_numerator).determinant() /
                  denominator.determinant();
    r.push_back(make_intersection(time));
  }
  return r;
}

Vector Triangle::local_normal_at(Point &p) {
  return cross((b - a), (c - a)).normalize();
}