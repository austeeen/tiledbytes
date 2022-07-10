#ifndef TB_WANGSETS_HPP
#define TB_WANGSETS_HPP

#include "common.hpp"
#include "tiled_util.hpp"
#include "typedefs.hpp"

/*
 Some of this can be esoteric as I have to work with various dictions/definitions of the
 'wang tile' concept(s)
 I recommend reading through the 'Wangsets' entry in the README for more info/details
*/

struct WangsetMeta {
    const char *type; const int total, offset, comma_skip;
} EdgeSet   {"edge",   4, 0, 4},
  CornerSet {"corner", 4, 1, 4},
  FullSet   {"full",   8, 0, 2};

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

// Iterate over the wangset entry to populate the WangtileMap by determining each entry's wang set
// tile number.
void asSet(rx::xml_node<>* node, WangtileMap& map, WangsetMeta& setmeta);

inline void asEdgeSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, EdgeSet); };

inline void asCornerSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, CornerSet); };

inline void asFullSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, FullSet); };

const Wangset newWangset(rx::xml_node<>* node);


#endif // TB_WANGSETS_HPP
