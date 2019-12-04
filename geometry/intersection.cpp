#include "intersection.hpp"
#include "geometry/object.hpp"
#include <algorithm>

HitRecord Intersection::hitrecord(std::vector<Intersection> &intersections) {
  HitRecord h;
  h.hit_point = ray.point_at(t);
  h.eye = (ray.origin - h.hit_point).normalize();
  h.normal = object->normal_at(h.hit_point);

  h.is_inside = false;
  if (h.normal.dot(h.eye) < 0) {
    h.normal = -1 * h.normal;
    h.is_inside = true;
  }

  h.overpoint = h.hit_point + (h.normal * 0.0001);
  h.underpoint = h.hit_point - (h.normal * 0.0001);

  std::vector<Object *> containers;
  for (auto &i : intersections) {
    if (i.t == t && i.object == object) {
      if (containers.size() == 0)
        h.ior_incoming = 1.0;
      else {
        h.ior_incoming = containers[containers.size() - 1]->material.ior;
      }
    }

    auto container_iter =
        std::find(containers.begin(), containers.end(), i.object);
    if (container_iter != containers.end()) {
      containers.erase(container_iter);
    } else {
      containers.push_back(i.object);
    }

    if (i.t == t && i.object == object) {
      if (containers.size() == 0)
        h.ior_transmitted = 1.0;
      else {
        h.ior_transmitted = containers[containers.size() - 1]->material.ior;
      }
      break;
    }
  }

  return h;
}

bool operator<(Intersection &a, Intersection &b) { return (a.t < b.t); }