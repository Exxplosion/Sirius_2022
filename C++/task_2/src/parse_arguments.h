#pragma once
#include <sstream>
#include <cstdio> // <stdio.h>

enum class ParseErrors
{
    INSUFFICIENT_ARGMENTS = -3,
    TO_MUCH_ARGUMENTS = -200,
    NOT_A_NUMBER = -100,
    SUCCESS = 0
};

ParseErrors parse_arguments(int argc, char **argv, std::string & filename, double &x, double &y);

std::string get_error_name(ParseErrors err_info);