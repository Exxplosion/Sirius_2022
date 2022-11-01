#pragma once

#include "Matrix.h"

class Submatrix  : public MatrixP
{
    private:
        int m = 0, n = 0;
        int *row_indexes = nullptr;
        int *column_indexes= nullptr;
    public:
        Submatrix() = default;
        Submatrix(const MatrixP& matrix, const int *i_s, const int *i_e );

        inline const int &get_m() const;

        inline const int &get_n() const;

        inline const double &operator()(int i, int j) const;

        inline double &operator()(int i, int j);
};

const double &MatrixP::operator()(int i, int j) const
{
#ifdef DEBUG
    if (i < 0 || i >= m || j < 0 || j >= n)
    {
        throw std::runtime_exception("Index out of range");
    }
#endif
    return data[size_t(i) * size_t(n) + j];
}

double &MatrixP::operator()(int i, int j)
{
#ifdef DEBUG
    if (i < 0 || i >= m || j < 0 || j >= n)
    {
        throw std::runtime_exception("Index out of range");
    }
#endif
    return data[size_t(i) * size_t(n) + j];
}

const double& Submatrix::operator()(int i, int j) const
{
    return MatrixP::operator()(row_indexes[i], column_indexes[j]);
}

double &Submatrix::operator()(int i, int j)
{
    return MatrixP::operator()(row_indexes[i], column_indexes[j]);
}
