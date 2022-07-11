#ifndef TILED_BYTES_HPP
#define TILED_BYTES_HPP

/*************************************************************
 *                       TiledBytes                          *
 *    A lightweight API for Tiled Map Editor files in C++    *
 *              github.com/austeeen/tiledbytes               *
 *-----------------------------------------------------------*
 *    Austin Herman                                          *
 *    austinherman868@gmail.com                              *
 *************************************************************/

 // todo - document all this

 #include <map>
 #include <vector>

namespace tb
{
extern const char *flag = "it works!";

// Forward declarations
struct Layer;
struct Property;
struct Rect;
struct Tile;
struct Tileset;
struct Wangset;
struct Wangtile;
struct Tmx;

// API Types
typedef std::map<const char*, const Property> PropertyMap;
typedef std::map<const int,   const Rect>     RectMap;
typedef std::map<const int,   const Tileset>  TilesetMap;
typedef std::map<const int,   const Wangtile> WangtileMap;
typedef std::vector<Layer>   LayerList;
typedef std::vector<Rect>    RectList;
typedef std::vector<Tile>    Tilelist;
typedef std::vector<Wangset> WangsetList;

// API objects
struct Property { const char *name, *type, *value; };

struct PositionRect { const int x, y, width, height; };

struct TextureRect { const int gid, x, y, width, height; };

struct Rect {
    const int id, gid, x, y, width, height;
    const char *name, *type;
    PropertyMap properties;
};

struct Tile {
    const int id;
    const PositionRect position;
    const TextureRect texture;
    const char* type;
    RectList rects;
    PropertyMap properties;
};

struct Image {
    const char* source;
    const int width, height;
};

struct Tileset {
    const int firstgid, tilewidth, tileheight, tilecount, columns;
    const char* name;
    const Image image;
    Tilelist tiles;
    WangsetList wangsets;
    PropertyMap properties;
};

struct Layer {
    Layer(const int id, const char* name);
    const int id;
    const char* name;
    PropertyMap properties;
};

struct TileLayer: Layer {
    TileLayer(const int id, const char* name, const int w, const int h);
    const int width, height;
    Tilelist tiles;
};

struct ObjectLayer: Layer {
    ObjectLayer(const int id, const char* name);
    RectMap rects;
};

struct GroupedLayer: Layer {
    GroupedLayer(const int id, const char* name, const LayerList sublayers);
    LayerList sublayers;
};

struct Tmx {
    const char* name;
    int width, height, tilewidth, tileheight;
    TilesetMap tilesets;
    LayerList layers;
    PropertyMap properties;
};

/*
 Some of this can be esoteric as I have to work with various dictions/definitions of the
 'wang tile' concept(s)
 I recommend reading through the 'Wangsets' entry in the README for more info/details
*/

struct WangsetMeta {
    const char *type; const int total, offset, comma_skip;
};

struct Wangtile {
    // tile set id
    const int tileid;

    // wang set id
    const int wangid;

    // encoded wang string
    const char* wangid_str;
};

struct Wangset {
  const char *name, *type;
  WangtileMap map;
};


/**************************************************************************************************/


void loadTmx(const char *filename, Tmx& usr_tmx);


} // namespace tb

#endif // TILED_BYTES_HPP
