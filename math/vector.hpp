#pragma once
#include "v3.hpp"

class Point;

class Vector : public V3<double> {
public:
	friend class Point;
	Vector(double x, double y, double z) : V3(x, y, z, 0.0) {}

	Point operator+(const Point& p);

	template <typename T>
	Vector operator*(const T& scalar);
};

