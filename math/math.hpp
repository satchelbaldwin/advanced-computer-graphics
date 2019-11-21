#pragma once
#include "constants.hpp"
#include "matrix.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "v3.hpp"
#include "vector.hpp"

inline double degrees_to_radians(double degrees) {
  return (degrees * PI / 180.);
}

inline double radians_to_degrees(double radians) {
  return (radians * 180. / PI);
}