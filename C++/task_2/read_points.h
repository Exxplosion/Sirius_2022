#pragma once
#include <cstdio>
#include <fstream>
#include <string>

/* double* read_points(const std::string &filename)
{
    FILE *fileptr = fopen(filename.c_str(), "r");
} */

//-1 - fail, 1 - ok, can be upgrade optional
int check_file(const std::string &filename, int &n);
int read_points(const std::string &filename, int n, double *x, double *y);