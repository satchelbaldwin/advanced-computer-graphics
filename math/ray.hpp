#pragma once
#include "point.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class Ray {
public:
	Ray();
	Ray(Point, Vector);
	
	Point origin;
	Vector direction; // needs to be a unit vector!
	Ray transform(const Matrix&);

	Point point_at(double);
};

