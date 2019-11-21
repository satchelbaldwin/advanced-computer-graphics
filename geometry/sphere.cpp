#include "sphere.hpp"

Sphere::Sphere() : Object() {}

std::vector<Intersection> Sphere::local_intersects_with(Ray &ray,
                                                        Ray &original_ray) {
  Vector adjusted_origin = ray.origin - Point(0, 0, 0);
  double a = ray.direction.dot(ray.direction);
  double b = ray.direction.dot(adjusted_origin) * 2;
  double c = adjusted_origin.dot(adjusted_origin) - 1;
  double discriminant = b * b - 4 * a * c;
  std::vector<Intersection> v;
  auto make_intersection = [&](double t) -> Intersection {
    return Intersection(t, original_ray, this);
  };

  if (discriminant < 0) {
  } else if (discriminant == 0) {
    double t = (-1 * b) / (2 * a);
    v.push_back(make_intersection(t));
    v.push_back(make_intersection(t));
  } else {
    double nb = -1 * b;
    double sq = sqrt(discriminant);
    double t1 = (nb - sq) / (2 * a);
    double t2 = (nb + sq) / (2 * a);
    v.push_back(make_intersection(t1));
    v.push_back(make_intersection(t2));
  }

  return v;
}

Vector Sphere::local_normal_at(Point &object_point) {
  Point object_normal = object_point - Point(0, 0, 0); // origin
  return object_normal;
}