#pragma once
#include "math/math.hpp"
#include "lighting/point_light.hpp"
#include "geometry/intersection.hpp"
#include <vector>

class Material {
public:
    Material(){}
    Material(
        Color color, 
        double diffuse, 
        double ambient, 
        double specular, 
        double emission,
        double shininess
    ) 
        : color(color), 
          diffuse(diffuse), 
          ambient(ambient), 
          specular(specular),
          emission(emission),
          shininess(shininess) 
    {}
    Color color;
    double diffuse;
    double ambient;
    double specular;
    double emission;
    double shininess;

    Color color_at_point(HitRecord, std::vector<std::shared_ptr<PointLight>>);
    /*
        diffuse color: colorLight * colorObj * cos of angle between light vector and normal * diffuse
        ambient color: colorLight * colorObj * ambient
        emission color: colorObj * emission
        specular color: specIntensity * specular * colorLight

        diffuseIntensity: max( unitvector to light . unit vector normal,  0)
        specular intensity: max(unitvector to light reflected . unit vector to origin of ray (eye), 0 )
        raise specintensity to the power of shininess (phong)
     */
};