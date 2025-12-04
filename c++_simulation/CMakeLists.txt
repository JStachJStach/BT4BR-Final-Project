cmake_minimum_required(VERSION 4.0)
project(c++_simulation)

set(CMAKE_CXX_STANDARD 20)

link_libraries(raylib)

add_executable(c++_simulation simulation.cpp)