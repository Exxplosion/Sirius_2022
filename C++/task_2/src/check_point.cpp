#include "check_point.h"
#include <iostream>
#include <stdio.h>
#include <limits>
#include <cmath>

void check_point(double *pX, double *pY, int n, const double& x, const double& y)
{
    double t = -10;

    int count_intersect = 0;
    for (int i = 0; i < n; i++)
    {
#ifndef DEBUG
        printf("<<<<<<<<POINT: (%.2f, %.2f), (%.2f, %.2f)\n", pX[i], pY[i], pX[i + 1], pY[i + 1]);
#endif
        {
            double t_1 = (x - pX[i + 1]) / (pX[i + 1] - pX[i]);
            double t_2 = (y - pY[i + 1]) / (pY[i + 1] - pY[i]);

#ifndef DEBUG
            printf("t1, t2 -- (%.3f, %.3f)\n", t_1, t_2);
#endif

            if ((std::fabs(t_1 - t_2) < std::numeric_limits<double>::epsilon()) && (t_1 >= -1.) && ((t_1 <= 0.)))
            {
                std::cout << "lies on the side" << std::endl;
                return;
            }
        }

        t = ((x_s - x) * (pY[i + 1] - y_s) - (y_s - y) * (pX[i + 1] - x_s)) / ((pX[i + 1] - pX[i]) * (y_s - y) - (x_s - x) * (pY[i + 1] - pY[i]));

        if ((t >= -1.) && (t <= 0.)) //std::numeric_limits<double>::cps();
        {
            count_intersect++;
        }
#ifndef DEBUG
        std::cout << "  t: " << t << std::endl;
#endif
    }

    if (count_intersect % 2 == 0)
    {
        std::cout << "lies inside" << std::endl;
        return;
    }
    std::cout << "lies outside" << std::endl;
}