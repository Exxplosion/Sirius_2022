#pragma once
#include <stdexcept>

// Structure implementing matrix as pointer of pointers
class MatrixPoP
{
    private:
        int m = 0, n = 0; // sizes of matrix
        double **data = nullptr; // pointer of pointer to store matrix
        void allocate(int M, int N);
        void deallocate();
    public:
        MatrixPoP() = default; // Enabling default constructor

        MatrixPoP(int m, int n); // Constructor for matrix of given sizes, fills matrix with random elements

        MatrixPoP(const MatrixPoP & o); // Constructor for matrix of given sizes, fills matrix with random elements
                                        
        const MatrixPoP& operator=(const MatrixPoP &);

        ~MatrixPoP(); // Destructor

        inline const int & get_m() const;

        inline const int & get_n() const;

        inline const double &operator()(int i, int j) const;

        inline double &operator()(int i, int j);
};

const int &MatrixPoP::get_m() const
{
    return m;
}

const int &MatrixPoP::get_n() const
{
    return n;
}

const double &MatrixPoP::operator()(int i, int j) const
{
#ifdef DEBUG
    if (i < 0 || i >= m || j < 0 || j >= n)
    {
        throw std::runtime_exception("Index out of range");
    }
#endif
    return data[i][j];
}

double &MatrixPoP::operator()(int i, int j)
{
#ifdef DEBUG
    if (i < 0 || i >= m || j < 0 || j >= n)
    {
        throw std::runtime_exception("Index out of range");
    }
#endif
    return data[i][j];
}


// Structure implementing matrix as single pointer
class MatrixP
{
    private:
        int m = 0, n = 0; // sizes of matrix
        double *data = nullptr; // pointer to store matrix

        void allocate(int M, int N);

        void deallocate();
    public:
        MatrixP() = default; // Enabling default constructor

        MatrixP(int m, int n); // Constructor for matrix of given sizes, fills matrix with random elements

        MatrixP(const MatrixP & o); // Constructor for matrix of given sizes, fills matrix with random elements
                                        
        const MatrixP& operator=(const MatrixP &);

        ~MatrixP(); // Destructor

        inline const int & get_m() const;

        inline const int & get_n() const;

        inline const double &operator()(int i, int j) const;

        inline double &operator()(int i, int j);
};

const int &MatrixP::get_m() const
{
    return m;
}

const int &MatrixP::get_n() const
{
    return n;
}

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

// Function to multiply 2 matrices in pointer of pointers format
int MatMul(const MatrixPoP& A, const MatrixPoP& B, MatrixPoP& C);

// Function to multiply 2 matrices in single pointer of pointers format
int MatMul(const MatrixP& A, const MatrixP& B, MatrixP& C);
