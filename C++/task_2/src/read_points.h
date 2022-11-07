#pragma once
#include <cstdio>
#include <fstream>
#include <string>


/* double* read_points(const std::string &filename)
{
    FILE *fileptr = fopen(filename.c_str(), "r");
} */

//-1 - fail, 1 - ok, can be upgrade optional
enum class ReadErrors
{
    CAN_NOT_OPEN_FILE = -101,
    PARSING_FILE_ERROR = -102,
    FILE_HAVE_ODD_COUNTS_POINTS = -103,
    SUCCSES = 0
};

ReadErrors check_file(const std::string &filename, int &n);
ReadErrors read_points(const std::string &filename, int n, double *x, double *y);
std::string get_error_name(ReadErrors err_info);