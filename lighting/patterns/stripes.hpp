#pragma once
#include "../pattern.hpp"
#include "math/math.hpp"

class StripePattern : public Pattern {
public:
  Color color1;
  Color color2;
  Color color_at(Point &) override;
  StripePattern(Color, Color);
};