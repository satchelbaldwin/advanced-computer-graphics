#pragma once
#include "v3.hpp"

class Point;

class Vector : public V3<double> {
public:
	friend class Point;
	operator Point() const;

	Vector(double x, double y, double z) : V3(x, y, z, 0.0) {}
	Vector() : V3() {}

	Point operator+(const Point& p) const;

	Vector operator*(const Vector v2) const
	{
		return Vector(x * v2.x, y * v2.y, z * v2.z);
	};
};
	
/*template <class T>
inline Vector operator*(const T& scalar, const Vector& v)
{
	return (v * scalar);
}
*/ 