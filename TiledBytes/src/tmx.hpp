#ifndef TB_TMX_HPP
#define TB_TMX_HPP

#include "core.hpp"
#include "utils.hpp"
#include "extractors.hpp"
#include "wangsets.hpp"

namespace tb
{

void newTileset(rx::xml_node<>* node, TilesetMap& tilesets);

void newTileLayer(rx::xml_node<>* node, LayerList& layers);

void newObjectLayer(rx::xml_node<>* node, LayerList& layers);

void newGroupedLayer(rx::xml_node<>* node, LayerList& layers);

} // namespace tb

#endif // TB_TSX_HPP
