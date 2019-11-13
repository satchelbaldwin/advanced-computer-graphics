#pragma once
#include "object.hpp"
#include "math/math.hpp"

class Plane : public Object {
public:
	Plane();
	std::vector<Intersection> local_intersects_with(Ray&, Ray&) override;
	Vector local_normal_at(Point&) override;
};
