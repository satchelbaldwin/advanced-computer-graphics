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
	virtual std::vector<Intersection> intersects_with(Ray&) {return std::vector<Intersection>();};
	virtual Vector normal_at(Point&) {return Vector();};

	void scale(const Tuple&);
	void translate(const Tuple&);
};
