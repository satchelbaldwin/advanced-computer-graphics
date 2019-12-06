#include "material.hpp"
#include "geometry/intersection.hpp"
#include "light.hpp"
#include "math/math.hpp"
#include "pattern.hpp"
#include "scene/scene.hpp"
#include <algorithm>
#include <memory>
#include <vector>

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
    auto surface = surface_color(r, scene, light_ptr);
    auto reflect = reflect_color(r, scene, recursion_depth) * reflectivity;
    auto refract = refract_color(r, scene, recursion_depth);

    if (reflectivity > 0 && transparency > 0) {
      double reflectance = schlick(r);
      total +=
          surface + (reflect * reflectance) + (refract * (1 - reflectance));
    } else {
      total += surface + reflect + refract;
    }
  }
  // clamp
  total.x = (total.x > 1.) ? 1. : total.x;
  total.y = (total.y > 1.) ? 1. : total.y;
  total.z = (total.z > 1.) ? 1. : total.z;
  return total;
}

double Material::schlick(HitRecord r) {
  auto cos = r.eye.dot(r.normal);
  double n1 = r.ior_incoming;
  double n2 = r.ior_transmitted;
  if (n1 > n2) {
    auto n = n1 / n2;
    auto sin2_t = n * n * (1.0 - (cos * cos));
    if (sin2_t > 1.0)
      return 1.0;
    cos = sqrt(1.0 - sin2_t);
  }
  auto r0 = pow(((n1 - n2) / (n1 + n2)), 2);
  return pow((r0 + (1 - r0) * (1 - cos)), 5);
}

Color Material::surface_color(HitRecord &r, Scene &scene,
                              std::shared_ptr<PointLight> pl) {
  Color surface;
  PointLight &light = *pl;
  auto to_light = (light.position - r.hit_point).normalize();
  auto diffuse_intensity = std::max(0.0, to_light.dot(r.normal));
  auto specular_intensity =
      std::max(0.0, reflect(to_light, r.normal).dot(r.eye));

  Color calc;
  if (has_pattern) {
    Point object_point =
        (*pattern->parent->transform.get_inverse()) * r.hit_point;
    Point pattern_point = (*pattern->transform.get_inverse()) * object_point;

    calc = pattern->color_at(pattern_point);
  } else {
    calc = color;
  }

  auto ambient_color = light.intensity * calc * ambient;
  surface += ambient_color;

  // if not in shadow
  if (!scene.is_in_shadow(r.overpoint, light)) {
    auto diffuse_color = light.intensity * calc * diffuse * diffuse_intensity;
    auto emission_color = calc * emission;
    auto specular_color =
        light.intensity * std::pow(specular_intensity, shininess) * specular;
    surface += diffuse_color + emission_color + specular_color;
  }

  return surface;
}

Color Material::reflect_color(HitRecord &r, Scene &scene, int recursion_depth) {
  Color reflected_color;

  Ray reflected{};
  reflected.direction = reflect(r.eye, r.normal);
  reflected.origin = r.overpoint;

  if (recursion_depth > Material::recursion_limit)
    reflected_color = Color(0, 0, 0);
  else
    reflected_color = scene.color_with_ray(reflected, recursion_depth + 1);

  return reflected_color;
}

Color Material::refract_color(HitRecord &r, Scene &scene, int recursion_depth) {
  Color refracted_color;
  if (transparency <= 0 || recursion_depth >= Material::recursion_limit) {
    refracted_color = Color{0, 0, 0};
  } else {
    // total internal refraction
    double n_ratio = r.ior_incoming / r.ior_transmitted;
    double cos_i = r.eye.dot(r.normal);
    double sin2_t = (n_ratio * n_ratio) * (1.0 - (cos_i * cos_i));
    double cos_t = sqrt(1.0 - sin2_t);
    auto direction = (r.normal * (n_ratio * cos_i - cos_t)) - (r.eye * n_ratio);
    Ray refracted{r.underpoint, direction};

    refracted_color =
        scene.color_with_ray(refracted, recursion_depth + 1) * transparency;
  }
  return refracted_color;
}