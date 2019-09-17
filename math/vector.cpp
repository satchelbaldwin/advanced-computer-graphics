#include "math.hpp"
#include "vector.hpp"

Vector::operator Point() const 
{
	return Point(x, y, z);
}


Point Vector::operator+(const Point& p) const
{
	return Point(x + p.x, y + p.y, z + p.z);
}

template <typename T>
Vector Vector::operator*(const T& scalar) const
{
	return Vector(x * scalar, y * scalar, z * scalar, 0.0);
}
