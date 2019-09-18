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
