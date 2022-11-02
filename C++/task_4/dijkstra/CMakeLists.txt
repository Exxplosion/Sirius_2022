cmake_minimum_required(VERSION 3.2)

project(dijkstra)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} dijkstra.cpp dijkstra.h)