#include "math.hpp"
#include "vector.hpp"

Vector Point::operator-(const Point& p) 
{
	return Vector(x - p.x, y - p.y, z - p.z);
}


template <typename T>
Point Point::operator*(const T& scalar)
{
	return Point(x * scalar, y * scalar, z * scalar, 1.0);
}
