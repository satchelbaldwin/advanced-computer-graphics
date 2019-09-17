#pragma once
#include "math/math.hpp"
#include <vector>

class Sphere {
public:
	Sphere();
	std::vector<double> intersections_with(Ray&);
	Vector normal_at(Point&);
};
