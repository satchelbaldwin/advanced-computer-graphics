#pragma once
#include "object.hpp"

class Plane : public Object {
public:
	Plane();
	std::vector<Intersection> intersects_with(Ray&) override;
	Vector normal_at(Point&) override;
};
