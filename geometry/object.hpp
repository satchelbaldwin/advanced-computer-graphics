#pragma once
#include "math/math.hpp"
#include "lighting/material.hpp"
#include "geometry/intersection.hpp"
#include <vector>

class Object {
public:
	Object();
	Matrix transform;
	Material material;
	virtual std::vector<Intersection> intersects_with(Ray&) = 0;
	virtual Vector normal_at(Point&) = 0;

	void scale(const Tuple&);
	void translate(const Tuple&);
};
