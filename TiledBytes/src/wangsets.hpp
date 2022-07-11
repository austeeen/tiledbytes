#ifndef TB_WANGSETS_HPP
#define TB_WANGSETS_HPP

#include "core.hpp"
#include "utils.hpp"

// Iterate over the wangset entry to populate the WangtileMap by determining each entry's wang set
// tile number.
void asSet(rx::xml_node<>* node, WangtileMap& map, WangsetMeta& setmeta);

inline void asEdgeSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, EdgeSet); };

inline void asCornerSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, CornerSet); };

inline void asFullSet(rx::xml_node<>* node, WangtileMap& map) { asSet(node, map, FullSet); };

const Wangset newWangset(rx::xml_node<>* node);


#endif // TB_WANGSETS_HPP
