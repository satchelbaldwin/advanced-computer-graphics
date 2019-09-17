#include "math.hpp"
#include "vector.hpp"

Point::operator Vector() const 
{
	return Vector(x, y, z);
}

Vector Point::operator-(const Point& p) const
{
	return Vector(x - p.x, y - p.y, z - p.z);
}


template <typename T>
Point Point::operator*(const T& scalar) const
{
	return Point(x * scalar, y * scalar, z * scalar, 1.0);
}
