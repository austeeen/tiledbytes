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
    namespace ERR
    {
        enum CODE : uint8_t {
            NONE = 0x0,
            UNDEFINED,
            FILE_LOAD_ERROR,
            FILE_NOT_FOUND
        };
    } // namespace ERR

extern uint8_t ERRCODE;

// Forward declarations
struct Frame;
struct Layer;
struct Property;
struct Rect;
struct Tile;
struct Tileset;
struct Tmx;
struct Tsx;
struct Wangset;
struct Wangtile;

// API Types
typedef std::vector<Layer>   LayerList;
typedef std::vector<Rect>    RectList;
typedef std::vector<Tile>    TileList;
typedef std::vector<Wangset> WangsetList;
typedef std::vector<Frame>   FrameList;
typedef std::map<const char*, const Property> PropertyMap;
typedef std::map<const int,   const Rect>     RectMap;
typedef std::map<const int,   const Tileset>  TilesetMap;
typedef std::map<const int,   const Wangtile> WangtileMap;
typedef std::map<const int,   const FrameList>     AnimationMap;

// API objects

struct Property {
    const char *name, *type, *value;
};

struct PositionRect {
    const int x, y, width, height;
};

struct TextureRect {
    const int gid, x, y, width, height;
};

struct Frame {
    const int tiled_id, duration;
};

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
    int width, height;
};

struct Tileset {
    const int firstgid, tilewidth, tileheight, tilecount, columns;
    const char* name;
    const Image image;
    TileList tiles;
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
    TileLayer(const int id, const char* name, const int w, const int h, const RectList& tilerects);
    const int width, height;
    RectList tilerects;
};

struct ObjectLayer: Layer {
    ObjectLayer(const int id, const char* name, const RectMap& rects);
    RectMap rects;
};

struct GroupedLayer: Layer {
    GroupedLayer(const int id, const char* name, const LayerList& sublayers);
    LayerList sublayers;
};

struct Tmx {
    const char* name;
    int width, height, tilewidth, tileheight;
    TilesetMap tilesets;
    LayerList layers;
    PropertyMap properties;
};

struct Tsx {
    int tilewidth, tileheight, tilecount, columns;
    const char* name;
    Image image;
    TileList tiles;
    AnimationMap animations;
    PropertyMap properties;
};


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


void loadTmx(const char *filepath, Tmx& usr_tmx);

void loadTsx(const char *filepath, Tsx& usr_tsx);


} // namespace tb

#endif // TILED_BYTES_HPP
