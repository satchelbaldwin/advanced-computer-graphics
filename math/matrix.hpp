/*
scaling: identity with diagonal changed for x, y, z
transforms and shifting: 4th column is multiplied by w (always 1) to translate
the bottom row is always [0, 0, 0, 1] -> w should never change

[
    x, 0, 0, 0
    0, y, 0, 0
    0, 0, z, 0
    0, 0, 0, 1
] -> scale by xyz

[
    1, 0, 0, x
    0, 1, 0, y
    0, 0, 1, z
    0, 0, 0, 1
] -> translate by xyz

order of operations matters!
scale(2) -> translate(1, 0, 0) != translate(1, 0, 0) -> scale(2)
 */

#pragma once
#include <memory>
#include "v3.hpp"

class Matrix {
public:
    double **data;
    int size;
    std::shared_ptr<Matrix> inverse;
    int determinant;

    Matrix();
    Matrix(int);
    ~Matrix();

    void store_inverse();
    std::shared_ptr<Matrix> get_inverse();
    bool invertable();

    double determinant();
    Matrix submatrix(int, int);
    double minor(int, int);
    double cofactor(int, int);
    Matrix transpose();

    Matrix scale(Tuple);
    Matrix translate(Tuple);
}