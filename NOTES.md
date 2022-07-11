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

## Building

All compiled code can go into a separate build directory.

create build/

    cmake ..

Generates build scripts using the default generator — on Linux/OSX this should be Makefiles.

    make
    make install


## Installing

Cmake can install the build into the system directories (default).

Change this with:

    cmake .. -DCMAKE_INSTALL_PREFIX=../install

Run the installed binary:

    ../install/bin/myapp

## Libs

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
