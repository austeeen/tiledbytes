#ifndef TB_TMX_HPP
#define TB_TMX_HPP

#include "core.hpp"
#include "utils.hpp"
#include "extractors.hpp"
#include "wangsets.hpp"

namespace tb
{

void newTileset(XmlNode* node, TilesetMap& tilesets);

void newTileLayer(XmlNode* node, LayerList& layers, const int width, const int height);

void newObjectLayer(XmlNode* node, LayerList& layers);

void newGroupedLayer(XmlNode* node, LayerList& layers, const int width, const int height);

} // namespace tb

#endif // TB_TSX_HPP
