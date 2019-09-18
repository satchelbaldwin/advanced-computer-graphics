#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../math/math.hpp"
#include "geometry/sphere.hpp"
#include "canvas/canvas.hpp"
#include <vector>

// tuples and vectors and points

TEST_CASE( "Tuple initialization", "[tuple]" ) 
{
	SECTION("w: 1.0") 
	{
		Tuple a{4.3, -4.2, 3.1, 1.0};
		REQUIRE(a == Tuple{4.3, -4.2, 3.1, 1.0});
	}
	SECTION("w: 0.0") 
	{
		Tuple a{4.3, -4.2, 3.1, 0.0};
		REQUIRE(a == Tuple{4.3, -4.2, 3.1, 0.0});
	}
}

TEST_CASE( "Point initialization", "[point]" )
{
	Point p{4, 4, -3};
	REQUIRE(p.w == 1.0);
}

TEST_CASE( "Vector initialization", "[vector]" )
{
	Vector p{4, 4, -3};
	REQUIRE(p.w == 0.0);
}

TEST_CASE( "Tuple addition", "[tuple]" )
{
	Tuple a1{3, -2, 5, 1};
	Tuple a2{-2, 3, 1, 0};
	Tuple a3 = a1 + a2;
	REQUIRE(a3 == Tuple{1, 1, 6, 1} );
}

TEST_CASE( "Point subtraction", "[tuple]" )
{
	Point p1{3, 2, 1};
	Point p2{5, 6, 7};
	Vector p3 = p1 - p2;
	REQUIRE(p3 == Vector{-2, -4, -6});
}

TEST_CASE( "Subtract vector from point", "[tuple]" )
{
	Point p{3, 2, 1};
	Vector v{5, 6, 7};
	Point p2 = p - v;
	REQUIRE(p2 == Point{-2, -4, -6});
}

TEST_CASE("Subtracting two vectors", "")
{
	Vector v1{3, 2, 1};
	Vector v2{5, 6, 7};
	Vector v3 = v1 - v2;
	REQUIRE(v3 == Vector{-2, -4, -6});
}

TEST_CASE("Subtracting from the zero Vector", "")
{
	Vector zero{0, 0, 0};
	Vector v{1, -2, 3};
	REQUIRE(zero - v == Vector{-1, 2, -3});
}

TEST_CASE("Negating a tuple", "")
{
	Tuple a{1, -2, 3, -4};
	REQUIRE(-1 * a == Tuple{-1, 2, -3, 4});
}

TEST_CASE("Multiplying a tuple scalar", "")
{
	Tuple a{1, -2, 3, -4};
	REQUIRE(a * 3.5 == Tuple{3.5, -7, 10.5, -14});
}

TEST_CASE("Multiplying a tuple fraction", "")
{
	Tuple a{1, -2, 3, -4};
	REQUIRE(a * 0.5 == Tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("Dividing a tuple by a scalar", "")
{
	Tuple a{1, -2, 3, -4};
	REQUIRE((a / 2).y == -1);
	REQUIRE(a / 2 == Tuple{0.5, -1, 1.5, -2});
}

TEST_CASE("Vector magnitude", "")
{
	Vector a{1, 0, 0};
	REQUIRE(a.magnitude() == 1);
	Vector b{0, 1, 0};
	REQUIRE(b.magnitude() == 1);
	Vector c{0, 0, 1};
	REQUIRE(c.magnitude() == 1);
	Vector d{1, 2, 3};
	REQUIRE(d.magnitude() == sqrt(14));
	Vector e{-1, -2, -3};
	REQUIRE(e.magnitude() == sqrt(14));
}

TEST_CASE("Normalizing vector", "")
{
	Vector a{4, 0, 0};
	REQUIRE(a.normalize() == Vector(1, 0, 0));
	Vector b{1, 2, 3};
	Vector c = b.normalize();
	REQUIRE(c == Vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14)));
}

TEST_CASE("Magnitude of normalized vector", "")
{
	REQUIRE(Vector(1, 2, 3).normalize().magnitude() == 1);
}

TEST_CASE("Dot product", "")
{
	REQUIRE(Vector(1, 2, 3).dot(Vector(2, 3, 4)) == 20);
}

TEST_CASE("Cross products", "")
{
	Vector a{1, 2, 3};
	Vector b{2, 3, 4};
	REQUIRE(cross(a, b) == Vector{-1, 2, -1});
	REQUIRE(cross(b, a) == Vector{1, -2, 1});
}

// color 

/*

TEST_CASE("", "") 
{

}*/

// ray

TEST_CASE("Creating a ray", "") 
{
	Point origin = Point(1, 2, 3);
	Vector direction = Vector(4, 5, 6);
	Ray ray(origin, direction);
	REQUIRE(ray.origin == origin);
	REQUIRE(ray.direction == direction);
}

TEST_CASE("Computing points at various distances", "") 
{
	Ray ray{Point(2, 3, 4), Vector(1, 0, 0)};
	REQUIRE(ray.point_at(0) == Point(2, 3, 4));
	REQUIRE(ray.point_at(1) == Point(3, 3, 4));
	REQUIRE(ray.point_at(-1) == Point(1, 3, 4));
	REQUIRE(ray.point_at(2.5) == Point(4.5, 3, 4));
}

// sphere

TEST_CASE("Sphere intersection: 2 points", "") 
{
	Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
	Sphere s;
	auto xs = s.intersects_with(r);

	std::vector<double> target = {4, 6};

	REQUIRE(xs == target);
}

TEST_CASE("Sphere intersection: 1 point (tangent)", "") 
{
	Ray r{Point(0, 1, -5), Vector(0, 0, 1)};
	Sphere s;
	auto xs = s.intersects_with(r);

	std::vector<double> target = {5, 5};

	REQUIRE(xs == target);
}

TEST_CASE("Sphere intersection: No points", "") 
{
	Ray r{Point(0, 2, -5), Vector(0, 0, 1)};
	Sphere s;
	auto xs = s.intersects_with(r);

	std::vector<double> target = {};

	REQUIRE(xs == target);
}

TEST_CASE("Ray originates inside a sphere", "") 
{
	Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
	Sphere s;
	auto xs = s.intersects_with(r);

	std::vector<double> target = {-1, 1};

	REQUIRE(xs == target);
}

TEST_CASE("A sphere is behind a ray", "") 
{
	Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
	Sphere s;
	auto xs = s.intersects_with(r);

	std::vector<double> target = {-6, -4};

	REQUIRE(xs == target);
}



TEST_CASE("Creating a canvas", "") 
{
	Canvas c{10, 20};
	REQUIRE(c.width  == 10);
	REQUIRE(c.height == 20);
	for (size_t y = 0; y < c.height; ++y) {
		for (size_t x = 0; x < c.width; ++x) {
			REQUIRE(c.pixels[y][x] == Color(0, 0, 0));
		}
	}
}

TEST_CASE("Constructing the PPM header", "") 
{
	Canvas c{5, 3};
	c.write("headertest.ppm");
	REQUIRE(1 == 1);
}

TEST_CASE("Writing pixels to a canvas", "")
{
	Canvas c{10, 10};
	Color red{1, 0, 0};
	c.set(2, 3, red);
	REQUIRE(c.get(2, 3) == red);
}

TEST_CASE("Writing pixels to a canvas and saving it", "")
{
	Canvas c{5, 3};
	Color c1{1.5, 0, 0};
	Color c2{0, 0.5, 0};
	Color c3{-0.5, 0, 1};

	c.set(0, 0, c1);
	c.set(2, 1, c2);
	c.set(4, 2, c3);

	c.write("writetest.ppm");

	REQUIRE(1 == 1);
}

/*
Scenario: Constructing the PPM header

  Given c ← canvas(5, 3)

  When ppm ← canvas_to_ppm(c)

  Then lines 1-3 of ppm are

    """

    P3

    5 3

    255

    """

Scenario: Constructing the PPM pixel data

  Given c ← canvas(5, 3)

    And c1 ← color(1.5, 0, 0)

    And c2 ← color(0, 0.5, 0)

    And c3 ← color(-0.5, 0, 1)

  When write_pixel(c, 0, 0, c1)

    And write_pixel(c, 2, 1, c2)

    And write_pixel(c, 4, 2, c3)

    And ppm ← canvas_to_ppm(c)

  Then lines 4-6 of ppm are

    """

    255 0 0 0 0 0 0 0 0 0 0 0 0 0 0

    0 0 0 0 0 0 0 128 0 0 0 0 0 0 0

    0 0 0 0 0 0 0 0 0 0 0 0 0 0 255

    """

Scenario: PPM files are terminated by a newline character

  Given c ← canvas(5, 3)

  When ppm ← canvas_to_ppm(c)

  Then ppm ends with a newline character

*/