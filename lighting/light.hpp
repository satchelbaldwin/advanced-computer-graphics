#pragma once
#include "math/vector.hpp"
#include "point_light.hpp"

inline Vector reflect( const Vector& original, Vector& normal)
{
    return (-1 * original + 2*(normal.dot(original))*normal);
}

/*

reflection

    N
R\  |  / L
  \ | /
   \|/


R = -L + 2(L . N)N
 */