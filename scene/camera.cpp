#include "camera.hpp"
#include "scene.hpp"
#include <iostream>
#include "math/math.hpp"

Camera::Camera(/* args */) : transform(Matrix::identity(4))
{
}

Camera::Camera(
    double fov,
    int    width,
    int    height
) :
    fov(fov),
    width(width),
    height(height),
    aspect((double)width / (double)height),
    transform(Matrix::identity(4))
{
    double field_radians = degrees_to_radians(fov);
    double half_view = tan(field_radians / 2.);
    if (aspect >= 1) {
        half_width  = half_view;
        half_height = half_view / aspect;
    } else {
        half_width  = half_view * aspect;
        half_height = half_view;
    }
    pixel_size = (half_width * 2) / (double)height;
}

Ray Camera::ray_for_pixel(int x, int y)
{
    // antialiasing here, this aims at pixel center
    double x_offset = (x + 0.5) * pixel_size;
    double y_offset = (y + 0.5) * pixel_size;

    double world_x = half_width  - x_offset;
    double world_y = half_height - y_offset;

    Point pixel  = (*transform.get_inverse()) * Point(world_x, world_y, -1);
    Point origin = (*transform.get_inverse()) * Point(0, 0, 0);
    Vector direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

void Camera::render_scene(Canvas *canvas, Scene& scene)
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            Ray r = ray_for_pixel(x, y);
            Color c = scene.color_with_ray(r);
            canvas->pixels[y][x] = c;
        }
    }
}

void Camera::set_transformation(
    Vector from, 
    Vector to, 
    Vector up)
{
    Vector forward = (to - from).normalize();
    Vector left = cross(forward, up.normalize());
    Vector true_up = cross(left, forward);

    double m[] = 
    { 
         left.x,     left.y,     left.z,    0,
         true_up.x,  true_up.y,  true_up.z, 0,
        -forward.x, -forward.y, -forward.z, 0,
        0,           0,          0,         1
    };

    Matrix orientation = Matrix::from(4, m);
    Matrix adjusted = orientation * Matrix::translate(
        Vector(
            -from.x, 
            -from.y, 
            -from.z
        )
    );
    transform = adjusted;
    transform.store_inverse();
}