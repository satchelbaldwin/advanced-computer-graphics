#pragma once
#include "math/math.hpp"
#include<string>

class Canvas {
public:
	unsigned int width;
	unsigned int height;
	Canvas();
	Canvas(unsigned int, unsigned int);
	Color **pixels;

	Color clamp_color(const Color&);
	void write(std::string);
};
