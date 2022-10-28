#include "read_points.h"

//Doxygen


ReadErrors read_points(const std::string &filename, int n, double *x, double *y)
{
    std::ifstream file(filename); //where open?!?
    if (!file)
    {
        return ReadErrors::CAN_NOT_OPEN_FILE;
    }
    for (int i = 0; i < n; i++)
    {
        file >> x[i] >> y[i];
        if (file.fail())
        {
            return ReadErrors::PARSING_FILE_ERROR;
        }
    }
    if (double tmp = 0; (file >> tmp, !file.fail()))
    {
        return ReadErrors::PARSING_FILE_ERROR;
    }
    if (!file.eof())
    {
        return ReadErrors::PARSING_FILE_ERROR;
    }

    file.close();

    return ReadErrors::SUCCSES;
};

[[nodiscard]] ReadErrors check_file(const std::string &filename, int &n)
{
    FILE *fileptr = fopen(filename.c_str(), "r");
    if (fileptr == nullptr)
    {
        return ReadErrors::CAN_NOT_OPEN_FILE;
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
        return ReadErrors::PARSING_FILE_ERROR;
    }
    if (n % 2 != 0)
    {
        return ReadErrors::FILE_HAVE_ODD_COUNTS_POINTS;
    }
    n /= 2;
    if (n < 3)
    {
        return ReadErrors::FILE_HAVE_ODD_COUNTS_POINTS;
    }
    fclose(fileptr);

    return ReadErrors::SUCCSES;
};

std::string get_error_name(ReadErrors err_info)
{
    switch (err_info)
    {
    case ReadErrors::CAN_NOT_OPEN_FILE:
        return "Error in openening file";
    case ReadErrors::PARSING_FILE_ERROR:
        return "Can not parsing file successfully";
    case ReadErrors::FILE_HAVE_ODD_COUNTS_POINTS:
        return "File have odd counts points";
    case ReadErrors::SUCCSES:
        return "No error";
    default:
        return "Uknown error";
    }
}