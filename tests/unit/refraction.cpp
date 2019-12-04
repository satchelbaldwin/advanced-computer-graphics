#include "tests/catch.hpp"
#include "scene/scene.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "lighting/point_light.hpp"
#include "math/v3.hpp"

TEST_CASE("Refraction") {
    Scene default_world;
    Sphere sphere1{};
    sphere1.material.color = Color{1, 1, 1};
    

    auto glass = [](){};

    SECTION("default material") {
        Material m;
        REQUIRE(m.transparency == 0.0);
        REQUIRE(m.ior == 1.0);
    }
    SECTION("glass sphere") {

    }
    SECTION("IORs at various intersections") {

    }
}