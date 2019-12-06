#include "stripes.hpp"
#include <iostream>

StripePattern::StripePattern(Color c1, Color c2)
    : color1(c1), color2(c2), Pattern(nullptr) {}

Color StripePattern::color_at(Point &p) {
  if ((int)floor(p.x) % 2 == 0)
    return color1;
  else
    return color2;
}