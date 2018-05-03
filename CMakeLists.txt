cmake_minimum_required(VERSION 3.5)
project(test2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES algorithm/quicksort.c)
add_executable(test2 ${SOURCE_FILES})
add_executable(main main.cpp)
add_executable(testheapsort 16/cli.c 16/sysutil.c)
#MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}/lib")
