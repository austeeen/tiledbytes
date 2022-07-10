#ifndef TB_TYPEDEFS_HPP
#define TB_TYPEDEFS_HPP

#include <map>
#include <vector>


// Forward declarations
class Property;
class Rect;
class Tile;
class Tileset;
class Wangset;
class Wangtile;


// Type definitions
typedef std::map<const char*, const Property> PropertyMap;
typedef std::map<const int,   const Rect>     RectMap;
typedef std::map<const int,   const Tileset>  TilesetMap;
typedef std::map<const int,   const Wangtile> WangtileMap;
typedef std::vector<const Rect>    RectList;
typedef std::vector<const Tile>    Tilelist;
typedef std::vector<const Wangset> WangsetList;

#endif // TB_TYPEDEFS_HPP
