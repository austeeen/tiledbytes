# Requirements

A build of TiledBytes library located in `./build/`

See `BUILDME.md` for instructions


# Install

This library will, by default, be installed into a local directory called `./install` so:

    mkdir ./install

if need be, then:

    cmake --install ./build


# Using in other projects

Simply copy the `install/` directory into your project.

Of course, be sure to include the header in `install/include` and link the static library in 
`install/lib/libTiledBytes.a` when building your project.
