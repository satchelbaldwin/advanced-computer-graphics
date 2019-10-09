#include "material.hpp"
#include "geometry/intersection.hpp"
#include <vector>
#include <algorithm>
#include "light.hpp"

Color Material::color_at_point(HitRecord r, std::vector<PointLight> lights)
{
    Color total = Color(0, 0, 0);
    for (auto light : lights) {
        auto to_light = (light.position - r.hit_point).normalize();
        auto diffuse_intensity = std::max((double)0, to_light.dot(r.normal));    
        auto specular_intensity = std::max(
            (double)0, 
            reflect(to_light, r.normal).dot(r.eye)
        );

        auto diffuse_color = light.intensity * color * diffuse * diffuse_intensity;
        auto ambient_color = light.intensity * color * ambient;
        auto emission_color = color * emission;
        auto specular_color = light.intensity * std::pow(specular_intensity, shininess) * specular;
        auto color = diffuse_color + ambient_color + emission_color + specular_color;
        total += color;
    }
    return total;
}
