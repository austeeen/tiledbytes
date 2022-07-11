# My CMake Notes

## Apps

### create an app with a single .cpp file

create CMakeLists.txt:

    cmake_minimum_required(VERSION 3.16.3)
    project(app_project)
    add_executable(myapp main.c)
    install(TARGETS myapp DESTINATION bin)


`add_executable` defines our binary with all linked source files.

`install` tells cmake to install our binary into the bin directory of the install directory.

## Building + Installing

All compiled code can go into a separate build directory.

create build/

    cmake ..

    helpful options:
     -DCMAKE_BUILD_TYPE=Debug
     -DCMAKE_INSTALL_PREFIX=../install

then

    cmake --build .

and run like so:

    ../install/bin/myapp

## Libs

Things that can be addressed through Cmake:
 - what parts of the library should it install
   - where do those parts get installed to
 - how other apps can find the library
   - using in-tree sources
   - using as a pre-built and/or external dependency
 - will it be static or shared

### Static

CMakeLists.txt:

    cmake_minimum_required(VERSION 3.16.3)
    project(libtest_project)
    add_library(test STATIC test.c)
    install(TARGETS test DESTINATION lib)
    install(FILES test.h DESTINATION include)

`add_library` like `add_executable` but generates a `lib[name].a` file

`install(TARGETS ...` install the `.a` file into `[install dir]/lib/`

`install(FILES ...` install a public header into `[install dir]/include/`

### Shared

change the `add_library` line to:

    add_library(test SHARED test.c)

## Linking libs to apps

add the library as a subdir of the app project directory

in the app's CmakeLists.txt, add:

    cmake_minimum_required(VERSION 3.16.3)
    project(my_app)
    add_subdirectory(libtest_project)       # 1
    add_executable(my_app main.c)
    target_link_libraries(my_app test)       # 2
    install(TARGETS my_app DESTINATION bin)  # 3


`add_subdirectory` makes the lib defined in libtestproject available to this build

`target_link_libraries` links it to the app's executable. Cmake will first build the lib before linking it the app.

## External libs


`add_library` can import already built libraries as well - we just have to set its IMPORTED_LOCATION property.

`add_dependencies` makes the imported library dependent on the external project

`target_link_libraries` is used like usual to link dependencies
