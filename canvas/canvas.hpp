#pragma once
#include "math/math.hpp"
#include<string>

class Canvas {
public:
	unsigned int width;
	unsigned int height;
	Canvas();
	Canvas(unsigned int, unsigned int);
	~Canvas();
	Color **pixels;

	Color clamp_color(const Color&);
	void set(unsigned int, unsigned int, Color);
	Color get(unsigned int, unsigned int);
	void write(std::string);
};
