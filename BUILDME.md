# Requirements

Tested on `Ubuntu 20.04` only... Should, in theory, be fine for any *nix platform. Not recommended for
Windows just yet.

    sudo apt-get install g++ cmake


# Build with 'run' script

`run` is a simple bash script that will build everything and run various tests. See its help page
for details.

    ./run b


# Build manually

    mkdir build
    cd build
    cmake ..
    cmake --build .
