cmake_minimum_required(VERSION 4.0)
project(c++_simulation)

set(CMAKE_CXX_STANDARD 20)

link_libraries(raylib)

add_executable(c++_simulation simulation.cpp
        headers/global_enums.h
        headers/settings.h
        classes/RandomUtils.cpp
        headers/RandomUtils.h
        classes/FileUtils.cpp
        headers/FileUtils.h
        classes/Rabbit.cpp
        headers/Rabbit.h
        classes/Fox.cpp
        headers/Fox.h
        classes/Actor.cpp
        headers/Actor.h
        classes/Cell.cpp
        headers/Cell.h
        classes/TileMap.cpp
        headers/TileMap.h
        headers/Position.h
        classes/Grid.cpp
        headers/Grid.h)