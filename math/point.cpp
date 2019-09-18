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
