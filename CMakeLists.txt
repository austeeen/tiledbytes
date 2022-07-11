cmake_minimum_required(VERSION 3.16.3)

project(TiledBytesExamples)

add_subdirectory(TiledBytes)


file(GLOB TEST_SOURCES
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS
        example/*.cpp)


foreach(src ${TEST_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} TiledBytesLib)
endforeach(src ${TEST_SOURCES})
