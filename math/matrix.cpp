#include "matrix.hpp"

Matrix::Matrix() 
{
    Matrix(4);
}

Matrix::Matrix(int n)
{
    data = (double **)malloc(sizeof(double *) * n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = (double *)malloc(sizeof(double) * n);
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = 0;
        }
    } 
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < n; ++i) {
        free(data[i]);
    }
    free(data);
}

void Matrix::store_inverse()
{
    inverse = std::shared_ptr<Matrix>(new Matrix());
    // find inverse lol
    // cofactors of all elements * 1 / det
    // det == 0 -> not invertable
    if (!invertable())
        throw std::runtime_error("Matrix isn't invertable (det is 0)");
}

void Matrix::invertable()
{
    return (determinant() != 0);
}

std::shared_ptr<Matrix> Matrix::get_inverse()
{
    if (inverse == nullptr) {
        inverse = store_inverse();
    }
    return inverse; 
}

Matrix Matrix::scale(Tuple t)
{

}

Matrix Matrix::translate(Tuple t)
{
    
}

double Matrix::determinant()
{
    if (size == 4) {
    // assume that the fourth row is always 0, 0, 0, 1
    // which means take submatrix of 3, 3! 

    } else if (size == 3) {

    } else if (size == 2) {
        return (data[0][0] * data[1][1] - data[0][1] * data[1][0]);
    }
}

Matrix Matrix::submatrix(int i, int j) 
{
    Matrix submatrix{size-1};
    for (size_t x = 0; x < size; ++x) {
        for (size_t y = 0; y < size; ++y) {
            
        }
    }
}

Tuple operator*(const Tuple& t, const Matrix& m)
{

}

Matrix Matrix::operator*(const Matrix& m)
{
    if (size != m.size)
        throw std::runtime_error("Can't multiply matrices of different sizes");
    Matrix result{size};
    for (size_t x = 0; x < size; ++x) {
        for (size_t y = 0; y < size; ++y) {
            double total = 0;
            for (size_t index_x = 0; index_x < size; ++index_x){
                
            }
            result[x][y] = 
        }
    }
}