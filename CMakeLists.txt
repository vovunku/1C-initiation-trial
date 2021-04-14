cmake_minimum_required(VERSION 3.16)
project(my_diff)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/lib)
set(SOURCES main.cpp ${CMAKE_SOURCE_DIR}/lib/finder.h ${CMAKE_SOURCE_DIR}/lib/finder.cpp)
add_executable(my_diff ${SOURCES})
