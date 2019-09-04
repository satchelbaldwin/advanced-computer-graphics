#include "math.hpp"
#include "vector.hpp"


Point Vector::operator+(const Point& p)
{
	return Point(x + p.x, y + p.y, z + p.z);
}

template <typename T>
Vector Vector::operator*(const T& scalar)
{
	return Point(x * scalar, y * scalar, z * scalar, 0.0);
}
