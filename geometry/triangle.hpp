#pragma once
#include "object.hpp"

class Triangle : public Object {
public:
    Point a;
    Point b;
    Point c;

	Triangle();
    Triangle(const Point&, const Point&, const Point&);
	std::vector<Intersection> intersects_with(Ray&) override;
	Vector normal_at(Point&) override;
};
