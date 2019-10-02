#include "sphere.hpp"

Sphere::Sphere() {}

std::vector<Intersection> Sphere::intersects_with(Ray& ray)
{
	Vector adjusted_origin = ray.origin - Point(0, 0, 0);
	double b = ray.direction.dot(adjusted_origin) * 2;
	double c = adjusted_origin.dot(adjusted_origin) - 1;
	double discriminant = b * b - 4 * c;
	std::vector<Intersection> v;
	auto make_intersection = [&](double t) -> Intersection
	{
		return Intersection(t, ray, this);
	};

	if (discriminant < 0) {
		
	} else if (discriminant == 0) {
		double t = (-1 * b) / 2;
		v.push_back(make_intersection(t));
		v.push_back(make_intersection(t));
	} else {
		double nb = -1 * b;
		double sq = sqrt(discriminant);
		double t1 = (nb - sq) / 2;
		double t2 = (nb + sq) / 2;
		v.push_back(make_intersection(t1));
		v.push_back(make_intersection(t2));
	}

	return v;
}

Vector Sphere::normal_at(Point& p)
{
	return (Vector)(p.normalize());
}