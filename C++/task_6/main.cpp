#include "DenseMatrix.hpp"
#include "MatrixAbstract.hpp"
#include "CSR.hpp"
#include "CSC.hpp"
#include "COO.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


int main() 
{
    {
        std::ifstream ifs("/home/explosion/Desktop/C++/Sirius_2022/Sparce_and_Dense_Matrix/matrix.txt");

        int m = 2, n = 2;

        DenseMatrix<int, int> A(m, n, ifs);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << A(i, j) << std::endl;
            }
        }

        std::vector<int> x(2, -3);
        std::vector<int> y(2, 0);

        A.matvec(x.data(), y.data(), true);

        for (int i = 0; i < 2; i++)
        {
            std::cout << y[i] << std::endl;
        }
    }

    std::cout << "----------------------------------->  \n";

    {
        std::ifstream ifs("/home/explosion/Desktop/C++/Sirius_2022/Sparce_and_Dense_Matrix/matrix1.txt");
        std::string line;
        std::getline(ifs, line);
        int m, n;
        std::istringstream iss(line);
        iss >> m >> n;
        std::getline(ifs, line);

        typedef float my_float;
        std::cout << m << ' ' << n << ' ' << line << std::endl;
        CSRMatrix<my_float, int, int> B(m, n, ifs);

        auto A = B + B;
        {
            std::vector<my_float> x(A.column_number(), 1);
            std::vector<my_float> y(A.row_number(), 0);
            A.matvec(x.data(), y.data(), false);
            for (auto v : y)
            {
                std::cout << v << ' ';
            }
            std::cout << std::endl;
        }
        {
            std::vector<my_float> x(A.row_number(), 1);
            std::vector<my_float> y(A.column_number(), 0);
            A.matvec(x.data(), y.data(), false);
            for (auto v : y)
            {
                std::cout << v << ' ';
            }
            std::cout << std::endl;
        }
    }

    std::cout << "----------------------------------->  \n";

    {
        std::ifstream ifs("/home/explosion/Desktop/C++/Sirius_2022/Sparce_and_Dense_Matrix/matrix1.txt");
        std::string line;
        std::getline(ifs, line);
        int m, n;
        std::istringstream iss(line);
        iss >> m >> n;
        std::getline(ifs, line);

        typedef float my_float;
        std::cout << m << ' ' << n << ' ' << line << std::endl;
        CSCMatrix<my_float, int, int> B(m, n, ifs);

        auto A = B + B;
        {
            std::vector<my_float> x(A.column_number(), 1);
            std::vector<my_float> y(A.row_number(), 0);
            A.matvec(x.data(), y.data(), false);
            for (auto v : y)
            {
                std::cout << v << ' ';
            }
            std::cout << std::endl;
        }
        {
            std::vector<my_float> x(A.row_number(), 1);
            std::vector<my_float> y(A.column_number(), 0);
            A.matvec(x.data(), y.data(), false);
            for (auto v : y)
            {
                std::cout << v << ' ';
            }
            std::cout << std::endl;
        }
    }

    {
        std::ifstream ifs("/home/explosion/Desktop/C++/Sirius_2022/Sparce_and_Dense_Matrix/matrix2.txt");
        std::string line;
        std::getline(ifs, line);
        int m, n;
        std::istringstream iss(line);
        iss >> m >> n;

        std::cout << m << ' ' << n << ' ' << line << std::endl;
        COOMatrix<int, int, int> B(m, n, ifs);

        B.print_matrix();
    }

    return 0;
}