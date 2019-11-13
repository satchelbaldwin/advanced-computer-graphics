#pragma once
#include "object.hpp"

class Sphere : public Object {
public:
	Sphere();
	std::vector<Intersection> local_intersects_with(Ray&, Ray&) override;
	Vector local_normal_at(Point&) override;
};
