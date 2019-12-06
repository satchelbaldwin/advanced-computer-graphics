#pragma once
#include "geometry/intersection.hpp"
#include "lighting/pattern.hpp"
#include "lighting/point_light.hpp"
#include "math/math.hpp"
#include <vector>

class Scene;
class Material {
public:
  Material() {}
  Material(Color color, double diffuse, double ambient, double specular,
           double emission, double shininess, double reflectivity,
           double transparency)
      : color(color), diffuse(diffuse), ambient(ambient), specular(specular),
        emission(emission), shininess(shininess), reflectivity(reflectivity),
        transparency(transparency) {}
  Color color;
  double diffuse;
  double ambient;
  double specular;
  double emission;
  double shininess;
  double reflectivity;
  double transparency = 0.0;
  double ior = 1;

  bool has_pattern = false;
  std::shared_ptr<Pattern> pattern;

  template <class T> void set_pattern(T &p, Object *o) {
    has_pattern = true;
    pattern = std::make_shared<T>(p);
    pattern->parent = o;
  }

  static const Material default_material;
  static const int recursion_limit;

  Color color_at_point(HitRecord, Scene &);
  Color color_at_point(HitRecord, Scene &, int);

  double schlick(HitRecord);
  Color surface_color(HitRecord &, Scene &, std::shared_ptr<PointLight>);
  Color reflect_color(HitRecord &, Scene &, int);
  Color refract_color(HitRecord &, Scene &, int);
};