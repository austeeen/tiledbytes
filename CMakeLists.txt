cmake_minimum_required(VERSION 3.16.3)

project(tiledbytes VERSION 0.1.1 DESCRIPTION "A lightweight API for Tiled Map Editor files in C++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -ggdb3")
set(CMAKE_BUILD_TYPE Debug)

add_library(${PROJECT_NAME} SHARED
    src/tiled_util.cpp
    src/tmx.cpp
    src/wangsets.cpp
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER include/tiledbytes.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

install(TARGETS ${PROJECT_NAME}
    LIBRARY       DESTINATION lib/${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION lib/include/${PROJECT_NAME}
)
