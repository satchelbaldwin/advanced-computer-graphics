#include "math/math.hpp"
#include "canvas/canvas.hpp"
#include "geometry/sphere.hpp"
#include "geometry/triangle.hpp"
#include "geometry/plane.hpp"
#include "scene/scene.hpp"
#include "scene/camera.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	Canvas canvas{1000, 500};
    Scene scene;
    Camera camera{60, 1000, 500};

    // Testing scene
    Sphere floor{};
    floor.scale(Vector(10, 0.01, 10));
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere left_wall{};
    left_wall.scale(Vector(10, 0.01, 10));
    left_wall.rotate(Vector(90, -45, 0));
    left_wall.translate(Vector(0, 0, 5));
    left_wall.material = floor.material;

    Sphere right_wall{};
    right_wall.scale(Vector(10, 0.01, 10));
    right_wall.rotate(Vector(90, 45, 0));
    right_wall.translate(Vector(0, 0, 5));
    right_wall.material = floor.material;
	
    Sphere middle{};
    middle.translate(Vector(-0.5, 1, 0.5));
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right{};
    right.scale(Vector(0.5, 0.5, 0.5));
    right.translate(Vector(1.5, 0.5, -0.5));
    right.material.color = Color(0.1, 1, 0.5);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    scene.add_object(floor);
    scene.add_object(left_wall);
    scene.add_object(right_wall);
    scene.add_object(middle);
    scene.add_object(right);

    PointLight light{Point(-10, 10, -10), Color(1,1,1)};
    scene.add_light(light);

    camera.set_transformation(Vector(0, 1.5, -5), Vector(0, 1, 0), Vector(0, 1, 0));

    camera.render_scene(&canvas, scene);

/*
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
*/
	canvas.write("second-image.ppm");

	return 0;
}
