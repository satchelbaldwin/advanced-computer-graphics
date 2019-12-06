#pragma once
#include "math/math.hpp"

class Object;
class Pattern {
public:
  Pattern(Object *);
  Pattern();
  Matrix transform;
  virtual Color color_at(Point &) { return Color(0, 0, 0); };
  Object *parent;
};