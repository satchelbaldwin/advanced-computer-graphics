#include "ray.hpp"
#include "point.hpp"
#include "vector.hpp"

Ray::Ray() : origin(Point(0, 0, 0)), direction(Vector(1, 0, 0))
{
}

Ray::Ray(Point p, Vector v) : origin(p), direction(v)
{
}

Point Ray::point_at(double t)
{
	return (t * direction+ origin);
}
