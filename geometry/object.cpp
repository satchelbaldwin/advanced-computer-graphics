#include "object.hpp"
#include <vector>
#include "lighting/material.hpp"

Object::Object() : transform(Matrix::identity(4)), material(Material::default_material)
{

}

void Object::scale(const Tuple& t)
{
	transform = Matrix::scale(t) * transform;
	transform.store_inverse();
}

void Object::translate(const Tuple& t)
{
	transform = Matrix::translate(t) * transform;
	transform.store_inverse();
}

void Object::rotate(const Tuple& t)
{
	if (t.x != 0) transform = Matrix::rotate_x(t.x) * transform;
	if (t.y != 0) transform = Matrix::rotate_y(t.y) * transform;
	if (t.z != 0) transform = Matrix::rotate_z(t.z) * transform;
	if (t.x != 0 || t.y != 0 || t.z != 0)
		transform.store_inverse();
}