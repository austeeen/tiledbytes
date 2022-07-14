[![pr-build](https://github.com/austeeen/tiledbytes/actions/workflows/pr-build.yml/badge.svg)](https://github.com/austeeen/tiledbytes/actions/workflows/pr-build.yml)

# Caution

This project is in development! All code herein is experimental and not recommended for production!
However, feel free to clone/fork/copy/etc and give feedback.

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

# Useful Links:

Get Tiled: https://www.mapeditor.org/

Checkout RapidXml: http://rapidxml.sourceforge.net/

### RapidXml...

is not my own project or code. I do not claim ownership or copyrights to the rapidxml library.
RapidXml is used by TiledBytes within its permissions stated in rapidxml/license.txt, 

# The road to release

I'm currently still building out this API. `.tmx` files seem to be working and `.tsx` files are on the
way. I am also working to put together a much more robust testing framework which I'll use to pump
out comprehensive tests. Might even get freaky and add some git workflows to the mess.

### What to expect in due time...

I'm thinking once the following are implemented/tested/complete I will tag an official `TiledBytes.1.0' release:
 - Tmx/tsx API implemented
 - Build/install options and configurations
 - Cross-platform support
 - Comprehensive test cases
 - Code documented and cleaned up
 - API/Build/Usage docs

### Author

Austin Herman

austinherman868@gmail.com

Feel free to contact me through email anytime!
