#include "test.hpp"

TestPattern::TestPattern(Color color) : color(color), Pattern(nullptr) {}

Color TestPattern::color_at(Point &p) { return color; }