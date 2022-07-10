#ifndef TB_CORE_HPP
#define TB_CORE_HPP

#include "wangsets.hpp"
#include "typedefs.hpp"

struct Property {
    const char *name, *type, *value;
};

struct PositionRect {
    const int x, y, width, height;
};

struct TextureRect {
    const int gid, x, y, width, height;
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
    Layer(const int id, const char* name): id(id), name(name) {};
    const int id;
    const char* name;
    PropertyMap properties;
};

struct TileLayer: Layer {
    TileLayer(const int id, const char* name, const int w, const int h):
        Layer(id, name),
        width(w), height(h)
    {};
    const int width, height;
    Tilelist tiles;
};

struct ObjectLayer: Layer {
    ObjectLayer(const int id, const char* name):
        Layer(id, name)
    {};
    RectMap rects;
};

struct GroupedLayer: Layer {
    GroupedLayer(const int id, const char* name, std::vector<const Layer> sublayers):
        Layer(id, name), sublayers(sublayers)
    {};
    std::vector<const Layer> sublayers;
};

struct Tmx {
    std::string name;
    int width, height, tilewidth, tileheight;
    TilesetMap tilesets;
    std::vector<Layer> layers;
    PropertyMap properties;
};

#endif // TB_CORE_HPP
