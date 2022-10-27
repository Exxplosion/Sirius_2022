#include "parse_arguments.h"
#include "read_points.h"

#include <iostream>


//#define x


int main(int argc, char** argv)
{
    std::string filename = "./points.txt";
    double x, y;

    auto err_info = parse_arguments(argc, argv, filename, x, y);
    if(int(err_info) < 0)
    {
        std::cout << "Error parsing cmd line arg: " << get_error_name(err_info) << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Successfully parsed cmd line";
    }

    int n = 0;
    if (check_file(filename, n) != 0)
    {
        std::cout << "error in check_file!\n";
        return 1;
    }

    double *pX = new double[n];
    double *pY = new double[n];

    if (read_points(filename, n, pX, pY) != 0)
    {
        std::cout << "error in read_points!\n";
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << pX[i] << ' ' << pY[i] << std::endl;
    }

    double t = -1;
    double x_s = 1000;
    double y_s = 1000;

    int count_intersect = 0;
    for (int i = 0; i < n; i++)
    {
        t = ((x_s - x) * (pY[i + 1] - y_s) - (y_s - y) * (pX[i+1] - x_s)) 
            / ((pX[i+1] - pX[i]) * (y_s - y) - (x_s - x) * (pY[i+1] - pY[i]));
        if ( (t >= -1) && (t <= 0))
        {
            count_intersect++;
        }
        std::cout << pX[i] << ' ' << pX[i + 1] << ' ' << pY[i] << ' ' << pY[i + 1] << std::endl;
        std::cout << t << std::endl;
    }

    if (count_intersect % 2 == 0)
    {
        std::cout << "NE PERESEKAET" << std::endl;
        return 0;
    }
    std::cout << "PERESEKAET" << std::endl;
    return 0;
}