#pragma once
#include "math/math.hpp"
#include <vector>

class HitRecord {
public:
  HitRecord() {}
  Point hit_point;
  Vector normal;
  Vector eye;
  bool is_inside;
  Point overpoint;
  Point underpoint;

  double ior_incoming;
  double ior_transmitted;
};

class Object;
class Intersection {
public:
  Intersection() {}
  Intersection(double t, Ray r, Object *o) : t(t), ray(r), object(o) {}
  double t;
  Ray ray;
  Object *object;
  // refactor to have intersections save
  HitRecord hitrecord(std::vector<Intersection> &);
};

bool operator<(Intersection &a, Intersection &b);
bool operator==(Intersection &a, Intersection &b);
/*

refraction notes:

index of refraction

I N R   incoming/normal/reflected
\ | /
 \|/
-------------
   \    transmitted
--------------

ior:
vacuum: 1
air: 1.0001
water: 1.33
glass: 1.5

snell
sin (theta i) / sin (theta t) = ior(transmitting) / ior(incoming)

air -> water:
n(air) sin(theta i) = n(water) sin(theta t);

we have to_eye and normal

cos(theta i) = eye dot normal
sin^2(theta i) = 1-cos^2(theta u)
sin(theta i) = sqrt(1-cos^2(theta i))
-
sin (theta i) = sqrt(1 - (eye dot normal)^2);

sin (theta t) = (ior_i/ior_t) sin (theta i)

if (ior_i/ior_t) sin (theta i) > 1
    return black, bail out, run away, just quit

cos (theta t) = sqrt(1 - (sin^2 theta t));

total internal reflection: bad

t = t normal + t tangent
t tangent =

new direction = normal * ((ni/nt) * cos(theta i) - cos(theta t)) - eye * (ni/nt)



calculating ni/nt!

t:-6|r:1.5     t:-4|t:2      t:-2|t:2.5      <-o->     t:2|r:3     t:6|r:3
t:8|r:1
*/