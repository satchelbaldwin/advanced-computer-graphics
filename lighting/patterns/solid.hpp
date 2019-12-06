#pragma once
#include "../pattern.hpp"
#include "math/math.hpp"

class SolidPattern : Pattern {
public:
  Color color;
  Color color_at(Point &) override;
  SolidPattern(Color);
};