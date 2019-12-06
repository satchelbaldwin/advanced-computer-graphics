#include "v3.hpp"
#include "point.hpp"
#include "vector.hpp"

template <> V3<double>::operator Vector() const { return Vector(x, y, z); }

template <> V3<double>::operator Point() const { return Point(x, y, z); }
