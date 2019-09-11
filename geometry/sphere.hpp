#pragma once
#include "math.hpp"
#include <vector>

class Sphere {
public:
	Sphere();
	std::vector<double> intersections_with(Ray);
};
