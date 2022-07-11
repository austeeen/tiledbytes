cmake_minimum_required(VERSION 3.16.3)

project(TestTiledBytes)

add_subdirectory(TiledBytes)

add_executable(tiledbytes_test.app tests/test.cpp)

target_link_libraries(tiledbytes_test.app PUBLIC TiledBytes)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(tiledbytes_test.app
    PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/TiledBytes")

install(TARGETS TestTiledBytes DESTINATION bin)
