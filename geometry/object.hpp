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
	// takes transformed ray into object space and world space ray
	virtual std::vector<Intersection> local_intersects_with(Ray&, Ray&) {
		std::cout << "Something got sliced! Uh-oh.\n"; 
		return std::vector<Intersection>();
	};
	virtual Vector local_normal_at(Point&) {return Vector();};

	std::vector<Intersection> intersects_with(Ray&);
	Vector normal_at(Point&);

	void scale(const Tuple&);
	void scale(double, double, double);
	void translate(const Tuple&);
	void translate(double, double, double);
	void rotate(const Tuple&);
	void rotate(double, double, double);
};
