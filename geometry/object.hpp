#pragma once
#include "math/math.hpp"
#include "lighting/material.hpp"
#include "geometry/intersection.hpp"
#include <vector>
#include <iostream>

class Object {
public:
	Object();
	Matrix transform;
	Material material;
	virtual std::vector<Intersection> intersects_with(Ray&) {
		std::cout << "Something got sliced! Uh-oh.\n"; 
		return std::vector<Intersection>();
	};
	virtual Vector normal_at(Point&) {return Vector();};

	void scale(const Tuple&);
	void translate(const Tuple&);
};
