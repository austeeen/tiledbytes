#ifndef TB_TMX_HPP
#define TB_TMX_HPP

#include "common.hpp"
#include "typedefs.hpp"

void loadTmx(const char *filename, Tmx& usr_tmx);


void newTileset(rx::xml_node<>* node, TilesetMap& tilesets);

void newTileLayer(rx::xml_node<>* node, LayerList& layers);

void newObjectLayer(rx::xml_node<>* node, LayerList& layers);

void newGroupedLayer(rx::xml_node<>* node, LayerList& layers);

#endif // TB_TSX_HPP
