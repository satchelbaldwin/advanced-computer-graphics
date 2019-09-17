#pragma once
#include "v3.hpp"

class Vector;

class Point : public V3<double> {
public:
	friend class Vector;
	operator Vector() const;

	Point(double x, double y, double z): V3(x, y, z, 1.0) {}
	
	Vector operator-(const Point& p) const;

	template <typename T>
	Point operator*(const T& scalar) const;
};
