cmake_minimum_required(VERSION 3.16.3)

project(TestRunner)

set(CMAKE_CXX_STANDARD 17)

file(GLOB TEST_SOURCES *.test.hpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ../deps)
# target_include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/deps)
