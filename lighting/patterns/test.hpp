#pragma once
#include "../pattern.hpp"
#include "math/math.hpp"

class TestPattern : Pattern {
public:
  Color color;
  Color color_at(Point &) override;
  TestPattern(Color);
};