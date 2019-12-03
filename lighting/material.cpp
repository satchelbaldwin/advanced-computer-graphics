#include "material.hpp"

#include <algorithm>
#include <memory>
#include <vector>

#include "geometry/intersection.hpp"
#include "light.hpp"
#include "scene/scene.hpp"

const Material Material::default_material =
    Material(Color(1, 0.2, 1), 0.9, 0.1, 0.9, 0, 200.0, 0, 0);

const int Material::recursion_limit = 5;

Color Material::color_at_point(HitRecord r, Scene &scene) {
  return color_at_point(r, scene, 0);
}

Color Material::color_at_point(HitRecord r, Scene &scene, int recursion_depth) {
  Color total = Color(0, 0, 0);

  // per light
  for (auto light_ptr : scene.lights) {
    PointLight &light = *light_ptr;
    auto to_light = (light.position - r.hit_point).normalize();
    auto diffuse_intensity = std::max(0.0, to_light.dot(r.normal));
    auto specular_intensity =
        std::max(0.0, reflect(to_light, r.normal).dot(r.eye));

    auto ambient_color = light.intensity * color * ambient;
    total = total + ambient_color;

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

    // reflection
    Ray reflected{};
    reflected.direction = reflect(r.eye, r.normal);
    reflected.origin = r.overpoint;

    Color reflected_color;
    if (recursion_depth > Material::recursion_limit)
      reflected_color = Color(0, 0, 0);
    else
      reflected_color = scene.color_with_ray(reflected, recursion_depth + 1);
    total = total + reflected_color * reflectivity;

    // refraction
    Color refracted_color;
    if (transparency <= 0 || recursion_depth >= Material::recursion_limit) {
      refracted_color = Color{0, 0, 0};
    } else {
      // total internal refraction
      double n_ratio = r.ior_incoming / r.ior_transmitted;
      double cos_i = r.eye.dot(r.normal);
      double sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));

      double cos_t = sqrt(1.0 - sin2_t);
      auto direction = r.normal * (n_ratio * cos_i - cos_t) - r.eye * n_ratio;
      Ray refracted{r.underpoint, direction};

      refracted_color =
          scene.color_with_ray(refracted, recursion_depth + 1) * transparency;
      std::cout << refracted_color << "\n";
    }
    total = total + refracted_color;
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
