#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>


void MatrixPoP::allocate(int M, int N)
{
    // Check matrix sizes
    if (M <= 0 || N <= 0)
    {
        std::cerr << "Warning: Matrix sizes are nonpositive, setting them nonpositive one to zero" << std::endl;
    }
    m = std::max(0, M); // set to zero if less then 0, otherwise to M
    n = std::max(0, N); // set to zero if less then 0, otherwise to N
    data = new double*[m]; // allocate array of pointers
    for (int i = 0; i < m; i++)
    {
        data[i] = new double[n]; // allocate array of double to store i-th row
        for (int j = 0; j < n; j++)
        {
            data[i][j] = (rand()); // fill with random values
        }
    }
}

void MatrixPoP::deallocate()
{
    for (int i = 0; i < m; i++)
    {
        delete[] data[i]; // deallocate memory used for row
        data[i] = nullptr;
    }
    delete[] data; // deallocate memory storing pointers to rows
    data = nullptr;
    m = 0;
    n = 0;
}

// Constructor
MatrixPoP::MatrixPoP(int M, int N)
{
    allocate(M, N);
}

// Destructor
MatrixPoP::~MatrixPoP()
{
    deallocate();
}

MatrixPoP::MatrixPoP(const MatrixPoP& o)
{
    allocate(o.m, o.n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i][j] = o.data[i][j];
        }
    }
}
const MatrixPoP & MatrixPoP::operator=(const MatrixPoP &o)
{
    if (m != o.m || n != o.n) // If sizes of do not correspond, free C and allocate with proper sizes
    {
        deallocate();
        allocate(o.m, o.n);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            data[i][j] = o.data[i][j];
        }
    }
    return *this;
}


// Multiplication
int MatMul(const MatrixPoP& A, const MatrixPoP& B, MatrixPoP& C)
{
    if (A.get_n() != B.get_m())
    {
        return -1; // If sizes do not correspond return with error
    }
    if (C.get_m() != A.get_m() || C.get_n() != B.get_n()) // If sizes of C do not correspond, free C and allocate with proper sizes
    {
        C = MatrixPoP(A.get_m(), B.get_n());
    }
    for (int i = 0; i < C.get_m(); i++)
    {
        for (int j = 0; j < C.get_n(); j++)
        {
            C(i, j) = 0; // fill with zero prior multiplication
        }
    }

    // Matrix maltiplication
    for (int i = 0; i < C.get_m(); i++)
    {
        for (int k = 0; k < A.get_n(); k++)
        {
            for (int j = 0; j < C.get_n(); j++)
            {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return 0;
}

void MatrixP::allocate(int M, int N)
{
    // Check matrix sizes
    if (M <= 0 || N <= 0)
    {
        std::cerr << "Warning: Matrix sizes are nonpositive, setting them nonpositive one to zero" << std::endl;
    }
    m = std::max(0, M); // set to zero if less then 0, otherwise to M
    n = std::max(0, N); // set to zero if less then 0, otherwise to N
    data = new double[size_t(m) * size_t(n)]; // allocate array of pointers
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*this)(i, j) = rand() % 255; // fill with random values
        }
    }
}

void MatrixP::deallocate()
{
    delete[] data; // deallocate memory storing pointers to rows
    data = nullptr;
    m = 0;
    n = 0;
}

// Constructor
MatrixP::MatrixP(int M, int N)
{
    allocate(M, N);
}

// Destructor
MatrixP::~MatrixP()
{
    deallocate();
}

MatrixP::MatrixP(const MatrixP& o)
{
    allocate(o.m, o.n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*this)(i, j) = o(i, j);
        }
    }
}
const MatrixP & MatrixP::operator=(const MatrixP &o)
{
    if (m != o.m || n != o.n) // If sizes of do not correspond, free C and allocate with proper sizes
    {
        deallocate();
        allocate(o.m, o.n);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*this)(i, j) = o(i, j);
        }
    }
    return *this;
}


// Multiplication
int MatMul(const MatrixP& A, const MatrixP& B, MatrixP& C)
{
    if (A.get_n() != B.get_m())
    {
        return -1; // If sizes do not correspond return with error
    }
    if (C.get_m() != A.get_m() || C.get_n() != B.get_n()) // If sizes of C do not correspond, free C and allocate with proper sizes
    {
        C = MatrixP(A.get_m(), B.get_n());
    }
    for (int i = 0; i < C.get_m(); i++)
    {
        for (int j = 0; j < C.get_n(); j++)
        {
            C(i, j) = 0; // fill with zero prior multiplication
        }
    }

    // Matrix maltiplication
    for (int i = 0; i < C.get_m(); i++)
    {
        for (int k = 0; k < A.get_n(); k++)
        {
            for (int j = 0; j < C.get_n(); j++)
            {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return 0;
}
