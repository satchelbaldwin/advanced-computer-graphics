#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../math/vector.hpp"


TEST_CASE( "Vectors", "[vector]" ) {
	Vector v{1, 2, 3};
	REQUIRE(v.x == 1);
}
