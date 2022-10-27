#include "read_points.h"

//Doxygen<<<<<<<<<333333333333333333333
int read_points(const std::string &filename, int n, double *x, double *y)
{
    std::ifstream file(filename);
    if (!file)
    {
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        file >> x[i] >> y[i];
        if (file.fail())
        {
            return -1;
        }
    }
    if (double tmp = 0; (file >> tmp, !file.fail()))
    {
        return -1;
    }
    if (!file.eof())
    {
        return -1;
    }

    return 0;
};

int check_file(const std::string &filename, int &n)
{
    FILE *fileptr = fopen(filename.c_str(), "r");
    if (fileptr == nullptr)
    {
        return -1;
    }
    double x;
    n = 0;
    int read_err;
    while ((read_err = fscanf(fileptr, "%lf", &x)) == 1) //fscanf return EOF
    {
        n++;
    }
    if (read_err != EOF)
    {
        return -1;
    }
    if (n % 2 != 0)
    {
        return -1;
    }
    n /= 2;
    if (n < 3)
    {
        return -1;
    }

    return 0;
};