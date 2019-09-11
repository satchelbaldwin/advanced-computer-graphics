#pragma once
#include "point.hpp"
#include "vector.hpp"

class Ray {
public:
	Ray();
	Ray(Point, Vector);
	
	Point origin;
	Vector direction; // needs to be a unit vector!

	Point point_at(double);
};

