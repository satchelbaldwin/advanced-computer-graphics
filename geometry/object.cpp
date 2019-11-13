#include "object.hpp"
#include <vector>
#include "lighting/material.hpp"

Object::Object() : transform(Matrix::identity(4)), material(Material::default_material)
{

}

void Object::scale(const Tuple& t)
{
	transform = Matrix::scale(t) * transform;
}

void Object::scale(double x, double y, double z)
{
	transform = Matrix::scale(Vector(x, y, z)) * transform;
}

void Object::translate(const Tuple& t)
{
	transform = Matrix::translate(t) * transform;
}

void Object::translate(double x, double y, double z)
{
	transform = Matrix::translate(Vector(x, y, z)) * transform;
}

void Object::rotate(const Tuple& t)
{
	rotate(t.x, t.y, t.z);
}

void Object::rotate(double x, double y, double z)
{
	if (x != 0) transform = Matrix::rotate_x(x) * transform;
	if (y != 0) transform = Matrix::rotate_y(y) * transform;
	if (z != 0) transform = Matrix::rotate_z(z) * transform;
}

std::vector<Intersection> Object::intersects_with(Ray& ray)
{
	Ray object_ray = *(transform.get_inverse()) * ray;
	return local_intersects_with(object_ray, ray);
}

Vector Object::normal_at(Point& point)
{
	Point object_point = (*transform.get_inverse()) * point;
	Point object_normal = local_normal_at(object_point);
	Point world_normal = transform.get_inverse()->transpose() * object_normal;
	return (Vector)world_normal.normalize();
}