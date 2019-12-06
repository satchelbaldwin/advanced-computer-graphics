#include "pattern.hpp"
#include "geometry/object.hpp"

class Object;
Pattern::Pattern(Object *o) : parent(o), transform(Matrix::identity(4)) {}
Pattern::Pattern() : transform(Matrix::identity(4)) {}