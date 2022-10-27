#include "parse_arguments.h"

ParseErrors parse_arguments(int argc, char **argv, std::string &filename, double &x, double &y)
{
    if (argc < 4)
    {
        return ParseErrors::INSUFFICIENT_ARGMENTS;
    }
    if (argc > 4)
    {
        return ParseErrors::TO_MUCH_ARGUMENTS;
    }
    filename = argv[1]; //конвертиовать явно

    std::istringstream iss(argv[2]); //??????
    iss >> x;

    if (iss.fail() || (sscanf(argv[3], "%lf", &y) != 1))
    {
        return ParseErrors ::NOT_A_NUMBER;
    }

    return ParseErrors::SUCCESS;
}

std::string get_error_name(ParseErrors err_info)
{
    switch (err_info)
    {
    case ParseErrors::INSUFFICIENT_ARGMENTS:
        return "Not enough arguments";
    case ParseErrors::TO_MUCH_ARGUMENTS:
        return "To much arguments";
    case ParseErrors::NOT_A_NUMBER:
        return "Can not convert input argument to double";
    case ParseErrors::SUCCESS:
        return "No error";
    default:
        return "Uknown error";
    }
}