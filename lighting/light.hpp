#pragma once
#include "math/vector.hpp"
#include "point_light.hpp"

Vector reflect( const Vector& original, Vector& normal)
{
    auto reflected =  -1 * original + 2*(normal.dot(original))*normal;
    return reflected;
}

/*

reflection

    N
R\  |  / L
  \ | /
   \|/


R = -L + 2(L . N)N
 */