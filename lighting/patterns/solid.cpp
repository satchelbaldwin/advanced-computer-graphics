#include "solid.hpp"

SolidPattern::SolidPattern(Color color) : color(color), Pattern(nullptr) {}

Color SolidPattern::color_at(Point &p) { return color; }