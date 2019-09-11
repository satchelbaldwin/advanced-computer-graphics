#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../math/math.hpp"

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
