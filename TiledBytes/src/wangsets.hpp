#ifndef TB_WANGSETS_HPP
#define TB_WANGSETS_HPP

#include "core.hpp"
#include "utils.hpp"

namespace tb
{

// Iterate over the wangset entry to populate the WangtileMap by determining each entry's wang set
// tile number.
void asSet(XmlNode* node, WangtileMap& map, WangsetMeta& setmeta);

inline void asEdgeSet(XmlNode* node, WangtileMap& map);

inline void asCornerSet(XmlNode* node, WangtileMap& map);

inline void asFullSet(XmlNode* node, WangtileMap& map);

const Wangset newWangset(XmlNode* node);

} // namespace tb

#endif // TB_WANGSETS_HPP
