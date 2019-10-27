#include "ray.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "matrix.hpp"

Ray::Ray() : origin(Point(0, 0, 0)), direction(Vector(1, 0, 0))
{
}

Ray::Ray(Point p, Vector v) : origin(p), direction(v)
{
}

Point Ray::point_at(double t)
{
	return (direction * t + origin);
}

Ray Ray::transform(const Matrix& m)
{
	auto t_origin = m * origin;
	auto t_direction = m * direction;
	return Ray(t_origin, t_direction);
}

Ray operator*(const Matrix& m, const Ray& r)
{
    Ray ray;
    ray.origin = m * r.origin;
    ray.direction = m * r.direction;
    return ray;
}
