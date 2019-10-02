#include "matrix.hpp"
#include <iostream>

Matrix::Matrix() : Matrix(4)
{}

Matrix::Matrix(int n) : 
    size(n), 
    inverse(nullptr),
    stored_determinant(nullptr)
{
    data = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; ++i) {
        data[i] = (double *)malloc(sizeof(double) * n);
        for (int j = 0; j < n; ++j) {
            data[i][j] = 0;
        }
    } 
}

Matrix::~Matrix()
{
    for (int i = 0; i < size; ++i) {
        free(data[i]);
    }
    free(data);
}

Matrix::Matrix(const Matrix& m) : Matrix(m.size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& m) noexcept :
    data(std::exchange(m.data, nullptr)),
    size(std::exchange(m.size, 0)),
    inverse(std::exchange(m.inverse, nullptr)),
    stored_determinant(std::exchange(m.stored_determinant, nullptr))
{}

Matrix& Matrix::operator=(const Matrix& m)
{
    return *this = Matrix(m);
}

Matrix& Matrix::operator=(Matrix&& m) noexcept
{
    std::swap(size, m.size);
    std::swap(inverse, m.inverse);
    std::swap(stored_determinant, m.stored_determinant);
    std::swap(data, m.data);
    return *this;
}

void Matrix::from_array(double *d)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            data[i][j] = d[i * size + j % size];
        }
    }
}

void Matrix::store_inverse()
{
    inverse = std::shared_ptr<Matrix>(new Matrix());
    if (!invertable())
        throw std::runtime_error("Matrix isn't invertable (det is 0)");
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; y++) {
            (*inverse)[x][y] = cofactor(x, y);
        }
    }
    inverse->transpose();
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; y++) {
            (*inverse)[x][y] /= determinant();
        }
    }
}

bool Matrix::invertable()
{
    return (determinant() != 0);
}

std::shared_ptr<Matrix> Matrix::get_inverse()
{
    if (inverse == nullptr) {
        store_inverse();
    }
    return inverse; 
}

Matrix Matrix::scale(Tuple t)
{
    Matrix result{4};
    result.data[0][0] = t.x;
    result.data[1][1] = t.y;
    result.data[2][2] = t.z;
    return result;
}

Matrix Matrix::translate(Tuple t)
{
    Matrix result{4};
    result.data[0][3] = t.x;
    result.data[1][3] = t.y;
    result.data[2][3] = t.z;
    return result;
}

Matrix Matrix::identity(int n)
{
    Matrix result{n};
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }
    return result;
}

void Matrix::store_determinant()
{
    double result = 0;
    if (size == 4) {
        // assume that the fourth row is always 0, 0, 0, 1
        // which means take submatrix of 3, 3! 
        result = cofactor(3, 3);
    } else if (size == 3) {
        result = 
            data[0][0] * cofactor(0, 0) +
            data[1][0] * cofactor(1, 0) +
            data[2][0] * cofactor(2, 0);
    } else if (size == 2) {
        result = data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    stored_determinant = std::make_shared<double>(result);
}

double Matrix::determinant()
{
    if (stored_determinant == nullptr)
        store_determinant();
    return *stored_determinant;
}

Matrix Matrix::submatrix(int i, int j) 
{
    Matrix submatrix{size-1};
    
    int x = 0;
    int y = 0;
    for (int si = 0; si < size - 1; ++si) {
        if (x == i) {
            x++;
            si--;
            continue;
        }
        for (int sj = 0; sj < size - 1; ++sj) {
            if (y == j) {
                y++; 
                sj--;
                continue;
            } else {
                submatrix[si][sj] = data[x][y++];
            }
        }
        x++;
    }

    return submatrix;
}

double Matrix::minor(int i, int j)
{
    return submatrix(i, j).determinant();
}

double Matrix::cofactor(int i, int j)
{
    return ((i + 2) % 2 == 0) ? minor(i, j) : -minor(i, j);
}

Matrix Matrix::transpose()
{
    Matrix result{4};
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

Tuple operator*(const Matrix& m, const Tuple& t)
{
    // horrible hack to access the tuple like an array
    // need assignable lvalue for result and const for argument 
    // so make it mutable and const_cast t because we aren't changing t
    auto access = [](Tuple& t, int i) -> double& {
        if (i == 0) return t.x;
        if (i == 1) return t.y;
        if (i == 2) return t.z;
        if (i == 3) return t.w;
        return t.x;
    };
    Tuple result;
    for (int n = 0; n < m.size; ++n) {
        access(result, n) = 0;
        for (int i = 0; i < m.size; ++i) {
            access(result, n) += m.data[n][i] * access(const_cast<Tuple&>(t), i);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& m)
{
    if (size != m.size)
        throw std::runtime_error("Can't multiply matrices of different sizes");
    Matrix result{size};
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            double total = 0;
            // for each position in the matrix, 
            // traverse the row of the left and column of the right...
            for (int index_x = 0, index_y = 0; index_x < size; ++index_x, ++index_y){
                total += data[row][index_x] * m.data[index_y][col];
            }
            result.data[row][col] = total;
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix& m) const 
{
    if (size != m.size) 
        return false;
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            if (data[x][y] != m.data[x][y])
                return false;
    return true;
}

double *Matrix::operator[] (int i) const
{
    return data[i];
}

double *&Matrix::operator[] (int i)
{
    return data[i];
}
