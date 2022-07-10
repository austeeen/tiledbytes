#ifndef TB_TMX_HPP
#define TB_TMX_HPP

#include "common.hpp"

struct Property {
    const char *name, *type, *value;
};

typedef std::map<const char*, Property> PropertyMap;

template <class T>
struct Rect {
    const int id, gid;
    const T x, y, width, height;
    const char *name, *type;
    PropertyMap properties;
};

template <class T>
struct Tile {
    const char* type;
    std::vector<Rect<T>> rects;
    PropertyMap properties;
};

struct ImageSource {
    const char* source;
    const int width, height;
};

struct Wangset {
    const char* name, type;
    std::map<const int, const int> wangtiles;
};

struct Tileset {
    const int id, firstgid, width, height, count, columns;
    const char* name;
    std::vector<Tile> tiles;
    std::vector<Wangset> wangsets;
    PropertyMap properties;
};

struct Layer {
    const int id;
    const char* name;
    PropertyMap properties;
};

struct TileLayer: Layer {
    int tiles*;
    const int width, height;
};

struct ObjectLayer: Layer {
    std::vector<Rect> layers;
};

struct LayerGroup: Layer {
    std::vector<Layer> layers;
};

struct Tmx {
    std::vector<Layer> layers;
    PropertyMap properties;
};

#endif // TB_TSX_HPP
