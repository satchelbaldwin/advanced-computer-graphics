#include "material.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "geometry/intersection.hpp"
#include "light.hpp"
#include "scene/scene.hpp"

const Material Material::default_material =
    Material(Color(1, 0.2, 1), 0.9, 0.1, 0.9, 0, 200.0);

Color Material::color_at_point(HitRecord r, Scene &scene) {
  Color total = Color(0, 0, 0);

  // per light
  for (auto light_ptr : scene.lights) {
    PointLight &light = *light_ptr;
    auto to_light = (light.position - r.hit_point).normalize();
    auto diffuse_intensity = std::max(0.0, to_light.dot(r.normal));
    auto specular_intensity =
        std::max(0.0, reflect(to_light, r.normal).dot(r.eye));

    // only do ambient if in shadow
    auto ambient_color = light.intensity * color * ambient;
    total = total + ambient_color;
    // continue;

    // if not in shadow
    if (!scene.is_in_shadow(r.overpoint, light)) {
      auto diffuse_color =
          light.intensity * color * diffuse * diffuse_intensity;
      auto emission_color = color * emission;
      auto specular_color =
          light.intensity * std::pow(specular_intensity, shininess) * specular;
      auto color = diffuse_color + emission_color + specular_color;
      total = total + color;
    }

    Ray reflected{};
    reflected.direction = reflect(r.eye, r.normal);
    reflected.origin = r.overpoint;
  }

  /*

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

  */
  total.x = (total.x > 1.) ? 1. : total.x;
  total.y = (total.y > 1.) ? 1. : total.y;
  total.z = (total.z > 1.) ? 1. : total.z;
  return total;
}
