#pragma once
#include <vector>

#include "geometry/intersection.hpp"
#include "lighting/point_light.hpp"
#include "math/math.hpp"

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

  static const Material default_material;
  static const int recursion_limit;

  Color color_at_point(HitRecord, Scene &);
  Color color_at_point(HitRecord, Scene &, int);
  /*
      diffuse color: colorLight * colorObj * cos of angle between light vector
     and normal * diffuse ambient color: colorLight * colorObj * ambient
      emission color: colorObj * emission
      specular color: specIntensity * specular * colorLight

      diffuseIntensity: max( unitvector to light . unit vector normal,  0)
      specular intensity: max(unitvector to light reflected . unit vector to
     origin of ray (eye), 0 ) raise specintensity to the power of shininess
     (phong)
   */
};