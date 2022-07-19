# Caution

This project is in development! All code herein is considered experimental until I can get an
official release done. However, feel free to clone/fork/copy/etc and give feedback.

# TiledBytes can...

 - Read in Tiled Map Editor project files and produce very primitive corresponding C++ objects
 - Get you started using Tiled Map Editor project files in your C++ project.
 - Serve as a jumping board for more robust and advanced usage of the Tiled Map Editor and 2D game
   design.
 - Be used in your own C++ project very quickly and easily.
 - Be intuitive and easily understood by all Tiled Map Editor users.
 - Be informative or used to learn more about Tiled Map Editor and 2D game dev.

# TiledBytes cannot...

 - Create or write to Tiled Map Editor project files.
 - Teach a user absolutely everything they need to know to begin their journey with either Tiled Map
   Editor or 2D game design.
 - Perform any graphical processing or rendering.
 - Serve alone as a fully featured game dev library.
 - Be considered useful for 3D or isometric game development. (although this could be done!)


---


# Requirements

Tested on `Ubuntu 20.04` only... Should, in theory, be fine for any *nix platform. Not recommended
for Windows just yet.

    sudo apt-get install g++ cmake


### Run scripts...

Are for user convenience and my own personal convenience. I recommend checking out the help docs for
`{tiledbytes}/run` and `{tiledbytes}/test/run` to get started.


# Build library...

Using `./run`:

    ./run b

Manually:

    mkdir build
    cd build
    cmake ..
    cmake --build .


# Install library...

Using `./run`:

    ./run i

Manually:
    mkdir install
    cmake --install ./build

** default install path is `./install/`


# Using in other projects

Projects using tiledbytes should only require the `libTiledBytes.a` package and its public header
'tiledbytes.hpp'

For regular install paths simply copy the two files from `install/*` into your project.


---


# Useful Links:

Get Tiled: https://www.mapeditor.org/

Checkout RapidXml: http://rapidxml.sourceforge.net/

### RapidXml...

is not my own project or code. I do not claim ownership or copyrights to the rapidxml library.
RapidXml is used by TiledBytes within its permissions stated in deps/rapidxml/license.txt.

### Cxxtest...

is not my own project or code. I do not claim ownership or copyrights to the cxxtest library.
cxxtest is used by TiledBytes within its permissions stated in deps/cxxtest/COPYING.

# The road to release...

I'm currently still building out this API. Core functionality is working, but largely untested.

### What to expect in due time...

My plans for an official `tiledbytes-1.0' release:
 - Tmx/tsx API implemented
 - Build/install options and configurations
 - Basic cross-platform support (*nix/windows/OSX)
 - Comprehensive test cases
 - Code documented and cleaned up
 - API/Build/Usage docs


---


# Author

Austin Herman

austinherman868@gmail.com

Feel free to contact me through email anytime!
