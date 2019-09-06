#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../math/math.hpp"

typedef V3<double> Tuple;

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


