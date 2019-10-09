#include "object.hpp"
#include <vector>

Object::Object() 
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