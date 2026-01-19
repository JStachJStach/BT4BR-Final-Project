cmake_minimum_required(VERSION 4.0)
project(c++_simulation)

set(CMAKE_CXX_STANDARD 20)

add_executable(c++_simulation simulation.cpp
        headers/global_enums.h
        classes/Tile.cpp
        headers/Tile.h
        headers/settings.h
        classes/RandomUtils.cpp
        headers/RandomUtils.h
        classes/FileUtils.cpp
        headers/FileUtils.h
)

target_include_directories(c++_simulation PRIVATE
        headers
        include/raylib/header
)

target_link_directories(c++_simulation PRIVATE
        include/raylib/lib
)

target_link_libraries(c++_simulation PRIVATE
        raylib
)

target_link_libraries(c++_simulation PRIVATE
        GL m pthread dl rt X11
)


# --- RPATH: make the binary find libraylib.so relative to itself ---
set_target_properties(c++_simulation PROPERTIES
        BUILD_RPATH "$ORIGIN/include/raylib/lib"
        INSTALL_RPATH "$ORIGIN/include/raylib/lib"
)