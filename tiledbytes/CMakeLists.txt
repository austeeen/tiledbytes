cmake_minimum_required(VERSION 3.16.3)

project(TiledBytes VERSION 0.1.1 DESCRIPTION "A lightweight API for Tiled Map Editor files in C++")

set(STATIC_LIB_NAME ${PROJECT_NAME})
set(SHARED_LIB_NAME ${PROJECT_NAME}Shared)

add_library(${STATIC_LIB_NAME} STATIC)
add_library(${SHARED_LIB_NAME} SHARED)

set(TARGET_SRCS src/tiledbytes.cpp)
set(HEADER include/tiledbytes.hpp)
set(PYLIB tiledbytes.py)

target_sources(${STATIC_LIB_NAME} PRIVATE ${TARGET_SRCS})
target_sources(${SHARED_LIB_NAME} PRIVATE ${TARGET_SRCS})

target_include_directories(${STATIC_LIB_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/deps
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(${SHARED_LIB_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/deps
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "CMAKE_INSTALL_PREFIX is not set, using ${CMAKE_SOURCE_DIR}/install")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
endif()

set_target_properties(${STATIC_LIB_NAME} PROPERTIES PUBLIC_HEADER ${HEADER})
set_target_properties(${SHARED_LIB_NAME} PROPERTIES PUBLIC_HEADER ${HEADER})

install(TARGETS ${STATIC_LIB_NAME} ${SHARED_LIB_NAME}
    DESTINATION ${CMAKE_SOURCE_DIR}/install
    PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/install)

file(COPY ${PYLIB} DESTINATION ${CMAKE_SOURCE_DIR}/install/)