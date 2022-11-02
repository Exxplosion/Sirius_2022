cmake_minimum_required(VERSION 3.2)

project(main)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# cmake -DCMAKE_BUILD_TYPE=Debug ..
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")                # common
#set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -DDEBUG")                   # debug only
#set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")  # release only
set(CMAKE_CXX_FLAGS "-O2")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/load_png ${PROJECT_SOURCE_DIR}/dijkstra ${PROJECT_SOURCE_DIR}/matrix)
add_subdirectory(load_png)
add_subdirectory(matrix)
add_subdirectory(dijkstra)

target_link_libraries(${PROJECT_NAME} load_png dijkstra matrix)