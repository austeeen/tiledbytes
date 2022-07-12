cmake_minimum_required(VERSION 3.16.3)

project(TiledBytesExamples)

add_subdirectory(TiledBytes)


file(GLOB TEST_SOURCES
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS
        example/*.cpp)


foreach(src ${TEST_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name}.app ${src})
    target_link_libraries(${name}.app TiledBytesLib)
endforeach(src ${TEST_SOURCES})

file(GLOB RSRCS
    LIST_DIRECTORIES false
    CONFIGURE_DEPENDS
    example/res/*.*)

foreach(rsrc ${RSRCS})
    file(COPY ${rsrc}
        DESTINATION ${CMAKE_BINARY_DIR}/res/)
endforeach(rsrc ${RSRCS})
