#include "canvas.hpp"
#include <string>
#include <iostream>
#include <fstream>

Canvas::Canvas() 
{
	Canvas(0, 0);
}

Canvas::Canvas(unsigned int w, unsigned int h) : width(w), height(h)
{
	pixels = (Color**)malloc(height * sizeof(Color*));
	for (size_t row = 0; row < height; ++row) {
		pixels[row] = (Color*)malloc(width * sizeof(Color));
	}
}

Color Canvas::clamp_color(const Color& c)
{
	auto clamp = [](double x){
		int adjusted = (int)(x * 255);
		adjusted = adjusted > 255 ? 255 : adjusted;
		adjusted = adjusted <   0 ?   0 : adjusted;
		return adjusted;
	};
	return Color(clamp(c.x), clamp(c.y), clamp(c.z));
}

void Canvas::write(std::string filename)
{
	std::ofstream file;
	file.open(filename);
	file << "P3\n" << width << " " << height << "\n" << "255\n";
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			Color &oc = pixels[y][x];
			Color c = clamp_color(oc);
			file << c.x << " " << c.y << " " << c.z << " ";
		}
		file << "\n";
	}
	file.close();
}
