cmake_minimum_required(VERSION 3.16.3)


project(TiledBytesExamples)

add_subdirectory(TiledBytes)

add_executable(example0.app example/test.cpp)

target_link_libraries(example0.app TiledBytesLib)

# target_include_directories(tiledbytes_test.app PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/TiledBytes")

# install(TARGETS example0.app DESTINATION bin)
