#include "intersection.hpp"

#include "geometry/object.hpp"

HitRecord Intersection::hitrecord() {
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

  /*
  vector v
  for intersection in intersection
      if intersection is self
          if nothing in v
              ior_inc = 1
          else
              ior_inc = v[-1]->object->material->ior

  last object in v -> ior incoming

  if v/containers contains an intersection w/ the same object
      we're leaving
      pop out of v
  otherwise
      add to v

  if intersections is self
      if v is empty
          ior_t = 1 (leaaaaaaaaaaaaaaaaaaaaaaaaaving          )
*/

  return h;
}

bool operator<(Intersection &a, Intersection &b) { return (a.t < b.t); }