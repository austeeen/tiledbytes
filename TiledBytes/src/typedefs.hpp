#ifndef TB_TYPEDEFS_HPP
#define TB_TYPEDEFS_HPP

#include <map>
#include <vector>


// Forward declarations
class Layer;
class Property;
class Rect;
class Tile;
class Tileset;
class Wangset;
class Wangtile;
class Tmx;

// Type definitions
typedef std::map<const char*, const Property> PropertyMap;
typedef std::map<const int,   const Rect>     RectMap;
typedef std::map<const int,   const Tileset>  TilesetMap;
typedef std::map<const int,   const Wangtile> WangtileMap;
typedef std::vector<Layer>   LayerList;
typedef std::vector<Rect>    RectList;
typedef std::vector<Tile>    Tilelist;
typedef std::vector<Wangset> WangsetList;

#endif // TB_TYPEDEFS_HPP
