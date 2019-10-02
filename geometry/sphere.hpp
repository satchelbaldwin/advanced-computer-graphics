#pragma once
#include "object.hpp"

class Sphere : public Object {
public:
	Sphere();
	std::vector<Intersection> intersects_with(Ray&) override;
	Vector normal_at(Point&) override;
};
