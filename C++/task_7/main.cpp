#include "COO.hpp"
#include "CSC.hpp"
#include "CSR.hpp"
#include "DenseMatrix.hpp"
#include "CGNE.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main()
{

    std::ifstream ifs("/home/explosion/Desktop/C++/Sirius_2022/Sirius_2022/C++/task_7/matrix.txt");

    int m = 2, n = 2;

    DenseMatrix<float, int> A(m, n, ifs);

    std::cout << "----------------------------------->  \n";

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << A(i, j) << std::endl;
        }
    }
    std::cout << "----------------------------------->  \n";

    std::ifstream ifss("/home/explosion/Desktop/C++/Sirius_2022/Sirius_2022/C++/task_7/matrix_b.txt");

    std::string line;
    std::getline(ifss, line);
    std::istringstream line_stream_first(std::move(line));

    std::vector<float> b(2);
    line_stream_first >> b[0];

    std::getline(ifss, line);
    std::istringstream line_stream_second(std::move(line));

    line_stream_second >> b[1];

    std::cout << "main----------------------------------->  \n";

    for (int i = 0; i < 2; i++)
    {
        std::cout << b[i] << " ";
    }

    std::cout << "\n main----------------------------------->  \n";

    auto x = CGNE(A, b, 0.1);

    for (auto x_el: x)
    {
        std::cout << "solution, x_i:" << x_el << ' ';
    }

    std::cout << "\n main----------------------------------->  \n";

    return 0;
}