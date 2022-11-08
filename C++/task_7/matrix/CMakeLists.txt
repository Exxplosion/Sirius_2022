cmake_minimum_required(VERSION 3.2)

project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} COO.hpp CSC.hpp CSR.hpp MatrixAbstract.hpp SparseMatrixAbstract.hpp DenseMatrix.hpp)

set_target_properties(matrix PROPERTIES LINKER_LANGUAGE CXX)