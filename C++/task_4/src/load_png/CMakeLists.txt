cmake_minimum_required(VERSION 3.2)

project(load_png)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} lodepng.cpp lodepng.h)