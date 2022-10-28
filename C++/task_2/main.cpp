#include "src/parse_arguments.h"
#include "src/read_points.h"
#include "src/check_point.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::string filename = "./points.txt";
    double x, y;

    {
        auto err_info = parse_arguments(argc, argv, filename, x, y);
        if(int(err_info) < 0)
        {
            std::cout << "Error parsing cmd line arg: " << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }

    int n = 0;
    {
        auto err_info = check_file(filename, n);
        if (int(err_info) != 0)
        {
            std::cout << "Error checking file" << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }

    double *pX = new double[n + 1];
    double *pY = new double[n + 1];

    {
        auto err_info = read_points(filename, n, pX, pY);
        if (int(err_info) != 0)
        {
            std::cout << "Error checking file" << get_error_name(err_info) << std::endl;
            return int(err_info);
        }
    }
    pX[n] = pX[0];
    pY[n] = pY[0];

    check_point(pX, pY, n, x, y);
    return 0;
}