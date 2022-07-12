#ifndef TB_WANGSETS_HPP
#define TB_WANGSETS_HPP

#include "core.hpp"
#include "utils.hpp"

namespace tb
{

// Iterate over the wangset entry to populate the WangtileMap by determining each entry's wang set
// tile number.
void asSet(rx::xml_node<>* node, WangtileMap& map, WangsetMeta& setmeta);

inline void asEdgeSet(rx::xml_node<>* node, WangtileMap& map);

inline void asCornerSet(rx::xml_node<>* node, WangtileMap& map);

inline void asFullSet(rx::xml_node<>* node, WangtileMap& map);

const Wangset newWangset(rx::xml_node<>* node);

} // namespace tb

#endif // TB_WANGSETS_HPP
