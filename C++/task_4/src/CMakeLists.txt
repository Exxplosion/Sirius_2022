cmake_minimum_required(VERSION 3.2)

project(main)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/load_png ${PROJECT_SOURCE_DIR}/dijkstra ${PROJECT_SOURCE_DIR}/matrix)
add_subdirectory(load_png matrix dijkstra)

target_link_libraries(${PROJECT_NAME} load_png dijkstra matrix)