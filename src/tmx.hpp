#ifndef TB_TMX_HPP
#define TB_TMX_HPP

#include "tiled_util.hpp"
#include "tiled_core.hpp"

void loadTmx(const char *filename);


const Tileset newTileset(rx::xml_node<>* node);

const TileLayer newTileLayer(rx::xml_node<>* node);

const ObjectLayer newObjectLayer(rx::xml_node<>* node);

const GroupedLayer newGroupedLayer(rx::xml_node<>* node);

#endif // TB_TSX_HPP
