#include "scene.hpp"

#include <algorithm>
#include <iostream>

#include "lighting/light.hpp"
#include "lighting/material.hpp"

std::vector<Intersection> Scene::intersections_with(Ray &ray) {
  std::vector<Intersection> intersections;
  for (auto &object : objects) {
    std::vector<Intersection> obj_i = object->intersects_with(ray);
    for (Intersection &i : obj_i) {
      intersections.push_back(i);
    }
  }
  std::sort(intersections.begin(), intersections.end());
  return intersections;
}

Color Scene::color_at_intersection(Intersection &i,
                                   std::vector<Intersection> &intersections) {
  return i.object->material.color_at_point(i.hitrecord(intersections), *this,
                                           0);
}

Color Scene::color_at_intersection(Intersection &i,
                                   std::vector<Intersection> &intersections,
                                   int recursion_depth) {
  return i.object->material.color_at_point(i.hitrecord(intersections), *this,
                                           recursion_depth);
}

Color Scene::color_with_ray(Ray &r) { return color_with_ray(r, 0); }

Color Scene::color_with_ray(Ray &r, int recursion_depth) {
  auto intersections = intersections_with(r);
  for (auto in : intersections) {
    if (in.t > 0) {
      return color_at_intersection(in, intersections, recursion_depth);
    }
  }
  return Color(0, 0, 0);
}

Color Scene::refracted_color(Intersection &intersection, HitRecord &hr,
                             int recursion_depth) {
  if (intersection.object->material.transparency <= 0 ||
      recursion_depth >= max_refraction_depth) {
    return Color{0, 0, 0};
  }

  // total internal refraction

  double n_ratio = hr.ior_incoming / hr.ior_transmitted;
  double cos_i = hr.eye.dot(hr.normal);
  double sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));

  double cos_t = sqrt(1.0 - sin2_t);
  auto direction = hr.normal * (n_ratio * cos_i - cos_t) - hr.eye * n_ratio;
  Ray refracted{hr.underpoint, direction};

  return color_with_ray(refracted, recursion_depth + 1) *
         intersection.object->material.transparency;
}

void Scene::calculate_inverses() {
  for (auto &o : objects) {
    o->transform.store_determinant();
    o->transform.store_inverse();
  }
}

bool Scene::is_in_shadow(Point &point, PointLight &light) {
  auto v = light.position - point;
  auto distance = v.magnitude();
  auto direction = v.normalize();
  Ray ray{point, direction};
  auto intersections = intersections_with(ray);
  if (intersections.size() < 1)
    return false;
  if (intersections[intersections.size() - 1].t < 0)
    return false;

  double lowest_t;
  for (auto &i : intersections) {
    if (i.t >= 0) {
      lowest_t = i.t;
      break;
    }
  }
  return (lowest_t < distance);
}