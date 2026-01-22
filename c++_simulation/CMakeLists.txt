cmake_minimum_required(VERSION 4.0)
project(simulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/raylib)


add_executable(simulation simulation.cpp
        classes/Tile.cpp
        classes/RandomUtils.cpp
        classes/FileUtils.cpp
)


target_include_directories(simulation PRIVATE
        headers
        external/nlohmann
)

target_link_libraries(simulation PRIVATE
        raylib
)