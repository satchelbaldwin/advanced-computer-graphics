#pragma once
#include "math/math.hpp"
#include <vector>

class Sphere {
public:
	Sphere();
	Matrix transform;
	std::vector<double> intersects_with(Ray&);
	Vector normal_at(Point&);
};
