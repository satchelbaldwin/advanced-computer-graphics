#pragma once
#include "v3.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "matrix.hpp"
#include "constants.hpp"

inline double degrees_to_radians(double degrees)
{
    return (degrees * PI / 180.);
}

inline double radians_to_degrees(double radians)
{
    return (radians * 180. / PI);
}