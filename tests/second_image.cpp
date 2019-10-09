#include "math/math.hpp"
#include "canvas/canvas.hpp"
#include "geometry/sphere.hpp"
#include "scene/scene.hpp"
#include "scene/camera.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	Canvas canvas{100, 100};
    Scene scene;
    Camera camera;

	Sphere s;
    s.material = Material(Color(1, 0, 0),0.8,0.2,0.6,0.1,10);
	PointLight pl = PointLight(Point{-2, 2, -3}, Color(1, 1, 1));

    scene.add_object(s);
    scene.add_light(pl);

    camera.render_scene(&canvas, scene);

	canvas.write("second-image.ppm");

	return 0;
}
