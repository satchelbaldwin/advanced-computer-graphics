#include "material.hpp"
#include "geometry/intersection.hpp"
#include <vector>
#include <algorithm>
#include "light.hpp"
#include <memory>
#include "scene/scene.hpp"

Color Material::color_at_point(HitRecord r, Scene& scene)
{
    Color total = Color(0, 0, 0);

    // per light
    for (auto light_ptr : scene.lights) {
        PointLight& light = *light_ptr;
        auto to_light = (light.position - r.hit_point).normalize();
        auto diffuse_intensity = std::max((double)0, to_light.dot(r.normal));    
        auto specular_intensity = std::max(
            (double)0, 
            reflect(to_light, r.normal).dot(r.eye)
        );


        // only do ambient if in shadow 
        auto ambient_color = light.intensity * color * ambient;
        total = total + ambient_color;
        // continue;

        // if not in shadow
        auto diffuse_color = light.intensity * color * diffuse * diffuse_intensity;
        auto emission_color = color * emission;
        auto specular_color = light.intensity * std::pow(specular_intensity, shininess) * specular;
        auto color = diffuse_color + emission_color + specular_color;
        total = total + color;
    }
    
    // reflectivity
    Ray reflected = Ray();
    reflected.direction = reflect(r.eye, r.normal);
    reflected.origin = r.overpoint;
    Color reflected_color = scene.color_with_ray(reflected);
    // color = world -> color from ray (r)  *   self reflectiveness
    // added to all of the other colors.

    // refraction
    Ray refracted = Ray();
    refracted.direction = Vector(0, 0, 0); // see notes!
    refracted.origin = r.underpoint;
    Color refracted_color = scene.color_with_ray(refracted) * transparency;

    return total;
}
