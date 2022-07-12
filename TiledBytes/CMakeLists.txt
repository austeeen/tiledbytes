cmake_minimum_required(VERSION 3.16.3)

project(TiledBytesLib VERSION 0.1.1 DESCRIPTION "A lightweight API for Tiled Map Editor files in C++")

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/tiledbytes.cpp
        src/utils.cpp
        src/tmx.cpp
        src/tsx.cpp
        src/wangsets.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/deps
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()


set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/tiledbytes.hpp)

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
    PUBLIC_HEADER DESTINATION include)
