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
set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -O -g")

add_executable(${PROJECT_NAME} main.cpp CGNE.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/matrix)
add_subdirectory(matrix)

target_link_libraries(${PROJECT_NAME} matrix)