cmake_minimum_required(VERSION 3.16.3)

project(TiledBytesLib VERSION 0.1.1 DESCRIPTION "A lightweight API for Tiled Map Editor files in C++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -ggdb3")
set(CMAKE_BUILD_TYPE Debug)

add_library(TiledBytesLib
    src/tiled_util.cpp
    src/tmx.cpp
    src/wangsets.cpp)

target_include_directories(TiledBytesLib PRIVATE src deps)

install(TARGETS TiledBytesLib DESTINATION lib)
install(FILES TiledBytesLib.hpp DESTINATION include)
