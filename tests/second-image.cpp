#include "math/math.hpp"
#include "canvas/canvas.hpp"
#include "geometry/sphere.hpp"
#include "scene/scene.hpp"
#include "scene/camera.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	Canvas canvas{250, 250};
    Scene scene;
    Camera camera;

	Sphere s;
    s.material = Material(Color(1, 0.2, 1),0.9,0.1,0.9,0,200.0);
	PointLight pl = PointLight(Point{-10, 10, -10}, Color(1, 1, 1));

    //s.scale(Tuple(1, 1, 1, 1));

    scene.add_object(&s);
    scene.add_light(&pl);

    scene.objects.push_back(std::make_shared<Sphere>(s));

    // does nothing
    camera.render_scene(&canvas, scene);

    Vector origin{0, 0, -5};
    for (int i = 0; i < canvas.height; ++i) {
        double y = 2 - (double)i / (canvas.height / 4);
        for (int j = 0; j < canvas.width; ++j) {
            double x = -2 + (double)j / (canvas.width / 4);
            Vector direction = (Vector{x, y, 0} - origin).normalize();
            Ray r{origin, direction};
            auto intersections = scene.intersections_with(r);
            for (auto in : intersections) {
                if (in.t > 0) {
                    canvas.pixels[i][j] = in.object->material.color_at_point(in.hitrecord(), scene);
                    break;
                }
            }

        }
    }

	canvas.write("second-image.ppm");

	return 0;
}